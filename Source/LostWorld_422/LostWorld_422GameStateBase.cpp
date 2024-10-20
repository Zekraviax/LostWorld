#include "LostWorld_422GameStateBase.h"

#include "EngineUtils.h"
#include "BaseClass_EntityInBattle.h"
#include "BaseClass_PlayerController.h"
#include "WidgetComponent_MinimapRoom.h"
#include "Widget_CustomConsole_Base.h"
#include "Level_SpawnTypeBase.h"


//-------------------- Level --------------------//
void ALostWorld_422GameStateBase::RegenerateLevel()
{
	if (!PlayerControllerRef)
		PlayerControllerRef = Cast<ABaseClass_PlayerController>(GetWorld()->GetFirstPlayerController());

	PlayerControllerRef->ControlMode = E_Player_ControlMode::E_Battle;
	ALevel_SpawnTypeBase* FoundGenerator = nullptr;

	// Find the level generator
	for (TActorIterator<ALevel_SpawnTypeBase> SpawnItr(GetWorld()); SpawnItr; ++SpawnItr) {
		FoundGenerator = *SpawnItr;
	}

	// Destroy all tiles
	for (TActorIterator<ABaseClass_GridTile> TileItr(GetWorld()); TileItr; ++TileItr) {
		ABaseClass_GridTile* FoundTile = *TileItr;
		FoundTile->Destroy();
		FoundTile->ConditionalBeginDestroy();
	}

	// Destroy all room actors
	for (TActorIterator<ABaseClass_LevelRoom> RoomItr(GetWorld()); RoomItr; ++RoomItr) {
		ABaseClass_LevelRoom* FoundRoom = *RoomItr;
		FoundRoom->Destroy();
		FoundRoom->ConditionalBeginDestroy();
	}

	// ?
	for (TObjectIterator<UWidgetComponent_MinimapRoom> Itr; Itr; ++Itr) {
		UWidgetComponent_MinimapRoom* FoundWidget = *Itr;
		FoundWidget->RemoveFromParent();
	}

	GEngine->ForceGarbageCollection();

	// Check for Boss Den thresholds
	FoundGenerator->CurrentFloor++;

	if (FoundGenerator->CurrentFloor >= FoundGenerator->FloorsRequiredForBoss) {
		for (TActorIterator<ALevel_SpawnTypeBase> SpawnItr(GetWorld()); SpawnItr; ++SpawnItr) {
			FoundGenerator = *SpawnItr;
			FoundGenerator->Destroy();
			FoundGenerator->ConditionalBeginDestroy();
		}

		GetWorld()->SpawnActor<ALevel_SpawnTypeBase>(BossDen_LevelGenerator_Class);
	} 

	PlayerControllerRef->Level_HUD_Widget->Minimap->GenerateLevel();

	// Send a message with the current floor number to the Custom Console
	//FString CustomConsoleMessage = "Current Floor: " + FString::FromInt(FoundGenerator->CurrentFloor) + "F";
	//Cast<ABaseClass_PlayerController>(GetWorld()->GetFirstPlayerController())->CustomConsole_Reference->AddEntry(CustomConsoleMessage);
}


//-------------------- Battle --------------------//
void ALostWorld_422GameStateBase::DebugBattleStart(F_LevelRoom_Encounter Battle)
{
	if (!PlayerControllerRef)
		PlayerControllerRef = Cast<ABaseClass_PlayerController>(GetWorld()->GetFirstPlayerController());

	if (PlayerControllerRef->CurrentEntityData.CurrentDeck.Num() < 10)
		GEngine->AddOnScreenDebugMessage(-1, 2.5f, FColor::Cyan, TEXT("Error: Not Enough Cards In Deck"));
	else
	{
		if (PlayerControllerRef->CustomConsole_Reference->IsValidLowLevel()) {
			PlayerControllerRef->CustomConsole_Reference->AddEntry("Battle begins!");
		}

		SortedTurnOrderList.Empty();

		// Stop the player from moving normally
		PlayerControllerRef->ControlMode = E_Player_ControlMode::E_Battle;

		// Swap between Level HUD and Battle HUD
		PlayerControllerRef->BeginBattle();

		// Add the player to the turn order first
		PlayerControllerRef->EntityInBattleRef->CardsInDeck = PlayerControllerRef->CurrentEntityData.CurrentDeck;
		SortedTurnOrderList.Add(PlayerControllerRef->EntityInBattleRef);

		// Make sure the player's coordinates are accurate
		PlayerControllerRef->EntityInBattleRef->X_Coordinate = PlayerControllerRef->EntityInBattleRef->GetActorLocation().X / 200;
		PlayerControllerRef->EntityInBattleRef->Y_Coordinate = PlayerControllerRef->EntityInBattleRef->GetActorLocation().Y / 200;

		// Spawn every other entity
		FString ContextString;
		F_LevelRoom_EnemyFormation* EnemyList = Battle.EncounterListEntry.DataTable->FindRow<F_LevelRoom_EnemyFormation>(Battle.EncounterListEntry.RowName, ContextString, true);

		if (EnemyList) {
			for (int j = 0; j < EnemyList->EnemiesMap.Num(); j++) {
				for (int i = 0; i < PlayerControllerRef->CurrentRoom->GridTilesInRoom.Num(); i++) {
					ABaseClass_GridTile* GridTileReference = PlayerControllerRef->CurrentRoom->GridTilesInRoom[i];

					// Spawn each enemy within 2 tiles of the player, but make sure that they don't spawn on an occupied tile
					if (GridTileReference->X_Coordinate <= PlayerControllerRef->EntityInBattleRef->X_Coordinate + 2 &&
						GridTileReference->X_Coordinate >= PlayerControllerRef->EntityInBattleRef->X_Coordinate - 2 &&
						GridTileReference->Y_Coordinate <= PlayerControllerRef->EntityInBattleRef->Y_Coordinate + 2 &&
						GridTileReference->Y_Coordinate >= PlayerControllerRef->EntityInBattleRef->Y_Coordinate - 2 &&
						GridTileReference->OccupyingEntity == nullptr &&
						(GridTileReference->X_Coordinate != PlayerControllerRef->EntityInBattleRef->X_Coordinate ||
							GridTileReference->Y_Coordinate != PlayerControllerRef->EntityInBattleRef->Y_Coordinate)) {
						UE_LOG(LogTemp, Warning, TEXT("DebugBattleStart / GridTileReference Coordinates: %d, %d"), GridTileReference->X_Coordinate, GridTileReference->Y_Coordinate);
						UE_LOG(LogTemp, Warning, TEXT("DebugBattleStart / Player Coordinates: %d, %d"), PlayerControllerRef->EntityInBattleRef->X_Coordinate, PlayerControllerRef->EntityInBattleRef->Y_Coordinate);

						// Spawn Enemy Here
						ABaseClass_EntityInBattle* NewEnemy = GetWorld()->SpawnActor<ABaseClass_EntityInBattle>(EntityInBattle_Class, FVector((GridTileReference->X_Coordinate * 200), (GridTileReference->Y_Coordinate * 200), 10), FRotator::ZeroRotator);
						NewEnemy->EntityBaseData.DisplayName = ("Test Enemy " + FString::FromInt(j + 1));
						NewEnemy->GameStateRef = this;

						NewEnemy->Event_EntitySpawnedInWorld();

						// Set occupied tile
						GridTileReference->OccupyingEntity = NewEnemy;

						break;
					}
				}
			}
		} else {
			UE_LOG(LogTemp, Warning, TEXT("ALostWorld_422GameStateBase / DebugBattleStart / Error: EnemyList is not valid."));
		}
		
		// For each entity, if they don't have any cards in their deck
		// create a default deck for them
		for (TActorIterator<ABaseClass_EntityInBattle> ActorItr(GetWorld()); ActorItr; ++ActorItr) {
			ABaseClass_EntityInBattle* FoundEntity = *ActorItr;

			if (FoundEntity != PlayerControllerRef->EntityInBattleRef) {
				// Give an entity a default deck if they have no cards
				if (FoundEntity->EntityBaseData.CurrentDeck.Num() <= 0) {
					FoundEntity->Debug_CreateDefaultDeck();
					FoundEntity->EntityBaseData.CurrentDeck = FoundEntity->CardsInDeck;
				}

				SortedTurnOrderList.Add(FoundEntity);
			}
		}

		// Tell each entity to shuffle their decks
		// Then, run all pre-battle functions:
		// Draw hands of 7 cards
		for (TActorIterator<ABaseClass_EntityInBattle> EntityItr(GetWorld()); EntityItr; ++EntityItr) {
			ABaseClass_EntityInBattle* BattleEntity = *EntityItr;

			BattleEntity->ShuffleCardsInDeck_BP();
			BattleEntity->Begin_Battle();
		}

		SortedTurnOrderList[0]->Begin_Turn();
	}
}


void ALostWorld_422GameStateBase::EntityBeginTurn_Delay()
{
	SortedTurnOrderList[0]->Begin_Turn();
}


void ALostWorld_422GameStateBase::EntityEndOfTurn()
{
	SortedTurnOrderList.RemoveAt(0);

	// Clean up CardAbilityActors
	for (TActorIterator<ACardAbilityActor_BaseClass> Itr(GetWorld()); Itr; ++Itr) {
		ACardAbilityActor_BaseClass* FoundActor = *Itr;
		FoundActor->Destroy();
	}

	if (SortedTurnOrderList.Num() <= 0) {
		GetWorldTimerManager().SetTimer(BeginTurnTimerHandle, this, &ALostWorld_422GameStateBase::NewCombatRound, 0.5f, false);
	} else {
		GetWorldTimerManager().SetTimer(BeginTurnTimerHandle, this, &ALostWorld_422GameStateBase::EntityBeginTurn_Delay, 1.f, false);
	}
}


void ALostWorld_422GameStateBase::NewCombatRound()
{
	// Player always goes first (at this time)
	// Player's Summons go second
	for (TActorIterator<ABaseClass_EntityInBattle> ActorItr(GetWorld()); ActorItr; ++ActorItr)
	{
		ABaseClass_EntityInBattle* FoundEntity = *ActorItr;
		if (FoundEntity->EntityBaseData.IsPlayerControllable) {
			SortedTurnOrderList.Add(FoundEntity);
		}
	}

	// Enemies move after the player (at this time)
	for (TActorIterator<ABaseClass_EntityInBattle> ActorItr(GetWorld()); ActorItr; ++ActorItr)
	{
		ABaseClass_EntityInBattle* FoundEntity = *ActorItr;
		if (!FoundEntity->EntityBaseData.IsPlayerControllable) {
			SortedTurnOrderList.Add(FoundEntity);
		}
	}

	GetWorldTimerManager().SetTimer(BeginTurnTimerHandle, this, &ALostWorld_422GameStateBase::EntityBeginTurn_Delay, 0.5f, false);
}


void ALostWorld_422GameStateBase::AddCardFunctionsToTheStack(FStackEntry StackEntry)
{
	int RepeatCount = 1;
	FCardBase NewStackEntryCard;

	NewStackEntryCard.Description = StackEntry.Card.AbilitiesAndConditions[0].AbilityDescription;
	NewStackEntryCard.CurrentTargets = StackEntry.Card.CurrentTargets;

	TheStack.Add(StackEntry);

	// Start timer for the stack
	GetWorldTimerManager().SetTimer(StackTimerHandle, this, &ALostWorld_422GameStateBase::ExecuteCardFunctions, StackEntry.Card.Delay);
}


void ALostWorld_422GameStateBase::ExecuteCardFunctions()
{
	// Spawn ability actor
	FActorSpawnParameters SpawnParameters;
	SpawnParameters.bNoFail = true;
	SpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	if (GetWorld()) {
		CardAbilityActor_Reference = GetWorld()->SpawnActor<ACardAbilityActor_BaseClass>(TheStack[0].Card.AbilitiesAndConditions[0].Ability, FVector::ZeroVector, FRotator::ZeroRotator, SpawnParameters);

		if (Cast<ABaseClass_PlayerController>(GetWorld()->GetFirstPlayerController())->CustomConsole_Reference->IsValidLowLevel()) {
			Cast<ABaseClass_PlayerController>(GetWorld()->GetFirstPlayerController())->CustomConsole_Reference->
				AddEntry(TheStack[0].Card.Controller->EntityBaseData.DisplayName + " casts " + TheStack[0].Card.DisplayName + ".");
		}

		CardAbilityActor_Reference->RunCardAbilityFunction(TheStack[0]);

		// Update all targets
		// Remove ability from the stack once done
		if (TheStack.Num() > 0) {
			for (int i = 0; i < TheStack[0].Card.CurrentTargets.Num(); i++) {
				if (Cast<ABaseClass_EntityInBattle>(TheStack[0].Card.CurrentTargets[i]) != nullptr) {
					if (Cast<ABaseClass_EntityInBattle>(TheStack[0].Card.CurrentTargets[i])->IsValidLowLevel()) {
						Cast<ABaseClass_EntityInBattle>(TheStack[0].Card.CurrentTargets[i])->Event_CardCastOnThis();
					}
				}

			}

			TheStack.RemoveAt(0);
		}
	}

	// If there are still Abilities to run, reset the timer for this function
	if (TheStack.Num() > 0) {
		GetWorldTimerManager().SetTimer(StackTimerHandle, this, &ALostWorld_422GameStateBase::ExecuteCardFunctions, TheStack[0].Card.Delay);
	}
}


void ALostWorld_422GameStateBase::Event_EntityDied(ABaseClass_EntityInBattle* DeadEntity)
{
	TArray<ABaseClass_EntityInBattle*> CurrentAliveEnemyEntities;
	ABaseClass_PlayerController* LocalPlayerControllerRef = Cast<ABaseClass_PlayerController>(GetWorld()->GetFirstPlayerController());

	// Check if entity that died is the player
	// If it isn't the player, check if all enemies are dead instead
	if (DeadEntity->PlayerControllerRef) {
		if (Cast<ABaseClass_PlayerController>(GetWorld()->GetFirstPlayerController())->CustomConsole_Reference->IsValidLowLevel()) {
			Cast<ABaseClass_PlayerController>(GetWorld()->GetFirstPlayerController())->CustomConsole_Reference->AddEntry("Game Over.");
		}
	} else {
		for (TActorIterator<ABaseClass_EntityInBattle> ActorItr(GetWorld()); ActorItr; ++ActorItr) {
			ABaseClass_EntityInBattle* FoundEntity = *ActorItr;

			if (!FoundEntity->EntityBaseData.IsPlayerControllable) {
				CurrentAliveEnemyEntities.Add(FoundEntity);
			}
		}

		// If all enemies are dead, end the battle
		if (CurrentAliveEnemyEntities.Num() <= 0) {
			if (Cast<ABaseClass_PlayerController>(GetWorld()->GetFirstPlayerController())->CustomConsole_Reference->IsValidLowLevel()) {
				Cast<ABaseClass_PlayerController>(GetWorld()->GetFirstPlayerController())->CustomConsole_Reference->AddEntry("All enemies defeated.");
			}

			// Remove the Encounter from the list
			if (LocalPlayerControllerRef->CurrentLocationInLevel->EncountersList.Num() > 0)
				LocalPlayerControllerRef->CurrentLocationInLevel->EncountersList.RemoveAt(0);

			LocalPlayerControllerRef->CurrentLocationInLevel->OnPlayerEnterTileFunction = E_GridTile_OnPlayerEnterTileFunctions_Enum::E_None;

			// Return the player to the Room
			LocalPlayerControllerRef->ExitBattle();
		}
	}
}