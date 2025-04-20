#include "LostWorldGameModeBattle.h"


#include "ActorEntityEnemy.h"
#include "ActorEntityPlayer.h"
#include "ActorGridTile.h"
#include "AiBrainBase.h"
#include "CustomJsonDeserializer.h"
#include "FunctionLibraryCards.h"
#include "FunctionLibraryStatusEffects.h"
#include "JsonObjectConverter.h"
#include "Kismet/GameplayStatics.h"
#include "LostWorldGameInstanceBase.h"
#include "LostWorldPlayerControllerBase.h"
#include "LostWorldPlayerControllerBattle.h"
#include "SaveGameLevelData.h"
#include "WidgetEntityBillboard.h"
#include "WidgetHudBattle.h"


void ALostWorldGameModeBattle::TransitionToBattle(const FEncounter& EnemyEncounter)
{
	// List of things that need to happen before any pre-battle functions can be run:
	// Add the Battle UI to the players' HUD.
	// Spawn enemy entities in to the level.
	// Change the player's controls to Battle mode.
	// Disable player movement.
	// Manipulate the camera so that it encompasses the whole room and all entities within it.
	FString ContextString;
	TArray<EEntityTypes> EnemyTypes = EnemyEncounter.EntityTypes;
	TArray<AActorGridTile*> ValidEnemySpawnTiles;

	
	// Clear the entities in battle array
	EntitiesInBattleArray.Empty();
	
	FString OverrideEncountersSetting = Cast<ULostWorldGameInstanceBase>(GEngine->GameViewport->GetWorld()->GetGameInstance())->
		DeveloperSettingsSaveGame->DeveloperSettingsAsStruct.OverrideEncounters;
	if (OverrideEncountersSetting != "") {
		// Get all valid encounters.
		FString AllEncountersAsJson = Cast<ULostWorldGameInstanceBase>(GetWorld()->GetGameInstance())->
			LoadFileFromJson("EncountersData");

		if (OverrideEncountersSetting == "Random") {
			// To-Do: Test the random encounter dev setting override.
			TArray<FEncounter> AllEncounters;

			FJsonObjectConverter::JsonArrayStringToUStruct(AllEncountersAsJson, &AllEncounters, 0, 0);
			EnemyTypes = AllEncounters[FMath::RandRange(0, AllEncounters.Num() - 1)].EntityTypes;
		} else {
			// Get the encounter that overrides the original.
			CustomJsonDeserializer* JsonDeserializer = new CustomJsonDeserializer();
			EnemyTypes = JsonDeserializer->DeserializeEncounterJson(AllEncountersAsJson, OverrideEncountersSetting).EntityTypes;

			// Nulling the pointer should make the object get cleaned up.
			JsonDeserializer = nullptr;
		}
	}

	
	// Spawn enemies at random valid tiles.
	// ReSharper disable once CppTooWideScope
	//const FActorSpawnParameters SpawnParameters;
	for (int RowCount = 0; RowCount < EnemyTypes.Num(); RowCount++) {
		// To-Do: Fix the random tile selection to either:
		// a. always select a tile to spawn an enemy, or
		// b. handle the situation where there are no valid tiles.
		
		// Fetch the enemy's data then spawn them in.
		FEnemyEntity EnemyEntityData = Cast<ULostWorldGameInstanceBase>(GetWorld()->GetGameInstance())->
			GetEnemyFromJson(EnemyTypes[RowCount]);
		FEntity EntityData = Cast<ULostWorldGameInstanceBase>(GetWorld()->GetGameInstance())->
			GetEntityFromJson(EnemyTypes[RowCount]);
		
		SpawnEnemyEntity(EnemyEntityData, EntityData);
	}

	
	// Reset all of the players' card arrays, except their deck.
	Cast<ALostWorldPlayerControllerBattle>(GetWorld()->GetFirstPlayerController())->ControlledPlayerEntity->
		EntityData.Hand.Empty();
	Cast<ALostWorldPlayerControllerBattle>(GetWorld()->GetFirstPlayerController())->ControlledPlayerEntity->
		EntityData.DiscardPile.Empty();

	
	// Add the player's entity to the array last.
	EntitiesInBattleArray.Add(Cast<ALostWorldPlayerControllerBattle>(
		GetWorld()->GetFirstPlayerController())->ControlledPlayerEntity);

	
	// Don't need to change the players' control mode here, because it will be set at the start of each turn.
	// Swap out the level exploration UI for the battle UI.
	// Make sure it's a "clean slate".
	Cast<ALostWorldPlayerControllerBattle>(GetWorld()->GetFirstPlayerController())->AddBattleHudToViewport();

	
	// Player camera manipulation.
	// First, move the camera to the middle point of the room.
	FVector PlayerLocation = FVector::ZeroVector;
	UCameraComponent* Camera = Cast<ALostWorldPlayerControllerBattle>(GetWorld()->GetFirstPlayerController())->
		ControlledPlayerEntity->Camera;
	int Room = 0;
	GetPlayerLocationAndRoom(PlayerLocation, Room);
	
	Camera->SetWorldLocation(FVector(
		LevelDataCopy.FloorDataAsStruct.RoomDataAsStructsArray[Room].RoomMidpoint.X,
		LevelDataCopy.FloorDataAsStruct.RoomDataAsStructsArray[Room].RoomMidpoint.Y,
		Camera->GetComponentLocation().Z));

	// Then, zoom the camera out until the whole room is visible.
	Camera->SetOrthoWidth(Camera->OrthoWidth + 248);

	
	// Once everything is done, begin Turn Zero.
	PreBattleTurnZero(EnemyEncounter);
}


FCard ALostWorldGameModeBattle::ApplyCardModifiersWithTimingTrigger(FCard InCard, const ECardModifierTimingTriggers TimingTrigger)
{
	// To-Do: Before card mods can be applied, and depending on the context/timing, we need to reset the variables to their base values(?)
	// To-Do: Maybe ignore the timing trigger and just reset the card every time, then apply all mods?

	// As of March 22, 2025, we're just going to ignore the mods that are muddling the issue like the "StartOfTurn" mod.
	// For all the currently existing mods, they will be applied once, using the other function
	// (ApplyAllCardModifiersWithoutTimingTriggers).

	// When to reset variables:
	// OnModifierApplied,

	// When not to reset variables:
	// StartOfBattle,
	// StartOfTurn
	if (TimingTrigger == ECardModifierTimingTriggers::OnModifierApplied) {
		InCard.TotalCost = InCard.BaseCost;
		InCard.TotalDamage = InCard.BaseDamage;
		InCard.TotalHealing = InCard.BaseHealing;
	}
	
	for (auto& Mod : InCard.ModifiersWithTriggers) {
		if (Mod.Value == TimingTrigger) {
			switch (Mod.Key)
			{
			case (ECardModifiers::TotalCostMinusOne):
				InCard.TotalCost--;
				break;
			case (ECardModifiers::TotalDamagePlusOne):
				InCard.TotalDamage++;
				break;
			case (ECardModifiers::DamageSetToOne):
				InCard.TotalDamage = 1;
				break;
			case (ECardModifiers::CostUpDamageUpHealingUp):
				InCard.TotalCost++;
				InCard.TotalDamage++;
				InCard.TotalHealing++;
				break;
			case (ECardModifiers::Cantrip):
				InCard.TotalCost++;
				InCard.FunctionsAndTargets.Add(ECardFunctions::CasterDrawsOneCard, ECardTargets::Self);
			default:
				break;
			}
		}
	}
	
	return InCard;
}


FCard ALostWorldGameModeBattle::ApplyAllCardModifiersWithoutTimingTriggers(FCard InCard)
{
	InCard.TotalCost = InCard.BaseCost;
	InCard.TotalDamage = InCard.BaseDamage;
	InCard.TotalHealing = InCard.BaseHealing;
	
	for (auto& Mod : InCard.ModifiersWithTriggers) {
		switch (Mod.Key)
		{
		case (ECardModifiers::TotalCostMinusOne):
			InCard.TotalCost--;
			break;
		case (ECardModifiers::TotalDamagePlusOne):
			InCard.TotalDamage++;
			break;
		case (ECardModifiers::DamageSetToOne):
			InCard.TotalDamage = 1;
			break;
		case (ECardModifiers::CostUpDamageUpHealingUp):
			InCard.TotalCost++;
			InCard.TotalDamage++;
			InCard.TotalHealing++;
			break;
		case (ECardModifiers::Cantrip):
			InCard.TotalCost++;
			InCard.FunctionsAndTargets.Add(ECardFunctions::CasterDrawsOneCard, ECardTargets::Self);
		default:
			break;
		}
	}
	
	return InCard;
}


void ALostWorldGameModeBattle::EndOfBattleCheck() const
{
	TArray<AActor*> FoundAllies, FoundEnemies;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AActorEntityEnemy::StaticClass(), FoundEnemies);

	if (FoundEnemies.Num() < 1) {
		PlayerVictory();
	}
}


void ALostWorldGameModeBattle::PlayerVictory() const
{
	// Change the players' control mode so they can walk again.
	Cast<ALostWorldPlayerControllerBattle>(GetWorld()->GetFirstPlayerController())->SetControlMode(EPlayerControlModes::LevelExploration);

	// Swap out the battle UI for the level UI.
	Cast<ALostWorldPlayerControllerBattle>(GetWorld()->GetFirstPlayerController())->AddLevelHudToViewport();
}


AActorEntityBase* ALostWorldGameModeBattle::FinishSpawningEntity(AActorEntityBase* InEntity)
{
	// First, find a valid location for the entity.
	TArray<AActorGridTile*> ValidEntitySpawnTiles;
	FVector PlayerEntityLocation = FVector();
	int PlayerRoomIndex = -1;

	GetPlayerLocationAndRoom(PlayerEntityLocation, PlayerRoomIndex);
	TArray<FVector> EntityLocations;
	Cast<ULostWorldGameInstanceBase>(GetWorld()->GetGameInstance())->GetAllEntityLocations(EntityLocations);

	// To-Do: Find the locations for all entities in the room and exclude them from the valid tiles array.
	for (TObjectIterator<AActorGridTile> Itr; Itr; ++Itr) {
		AActorGridTile* FoundTile = *Itr;
		// First, check if the grid tile doesn't have any encounters or the encounter is an enemy encounter.
		if (FoundTile->Encounter.EncounterType == EEncounterTypes::Enemy ||
			FoundTile->Encounter.EncounterType == EEncounterTypes::None) {
			// Second, make sure the tile isn't in a corridor.
			if (FoundTile->CorridorIndex == -1) {
				// Third, make sure the player isn't occupying the tile.
				if (!EntityLocations.Contains(FoundTile->GetActorLocation())) {
					// Fourth, make sure the entity is spawned in the same room as all the other entities.
					if (PlayerRoomIndex < 0) {
						// If the player room index is less than zero, that means the player is currently being spawned,
						// and that the check should be skipped.
						ValidEntitySpawnTiles.Add(FoundTile);
					} else if (FoundTile->RoomIndex == PlayerRoomIndex) {
						ValidEntitySpawnTiles.Add(FoundTile);
					}
				}
			}
		}
	}

	AActorGridTile* RandomTile = ValidEntitySpawnTiles[FMath::RandRange(0, ValidEntitySpawnTiles.Num() -1)];
	InEntity->SetActorLocation(RandomTile->GetActorLocation());
		
	// Attach an AI brain component if the entity isn't to be controlled by the player.
	if (Cast<AActorEntityEnemy>(InEntity)) {
		Cast<AActorEntityEnemy>(InEntity)->CreateAiBrainComponent();
	}
	
	// Stat calculations.
	Cast<IInterfaceEntity>(InEntity)->CalculateTotalStats();

	// Set up the entity's draw pile.
	// Apply card modifiers that "trigger" when applied/when the entity is spawned.
	for (int CardCount = 0; CardCount < InEntity->EntityData.Deck.Num(); CardCount++) {
		FCard Copy = ApplyAllCardModifiersWithoutTimingTriggers(InEntity->EntityData.Deck[CardCount]);
		InEntity->EntityData.Deck[CardCount] = Copy;
	}

	// Initialize billboard.
	InEntity->ResetEntityBillboardPositionAndRotation();
	Cast<UWidgetEntityBillboard>(InEntity->EntityBillboard->GetUserWidgetObject())->
		UpdateBillboard(InEntity->EntityData);

	EntitiesInBattleArray.Add(InEntity);

	DualLog("Spawned entity: " + InEntity->EntityData.DisplayName, 3);

	// To-Do: When an entity is summoned mid-battle, the whole turn queue needs to be recalculated,
	// but the currently acting actor should always be the first in the turn queue.
	return InEntity;
}


AActorEntityEnemy* ALostWorldGameModeBattle::SpawnEnemyEntity(const FEnemyEntity& InEnemyEntityData, const FEntity& InEntityData)
{
	const FActorSpawnParameters SpawnParameters;

	AActorEntityEnemy* ReturnEnemy = GetWorld()->SpawnActor<AActorEntityEnemy>(ActorEntityEnemyBlueprintClass,
		FVector(-200, -200, -200),FRotator::ZeroRotator, SpawnParameters);

	ReturnEnemy->EnemyData = InEnemyEntityData;
	ReturnEnemy->EntityData = InEntityData;
	ReturnEnemy->EntityData.Team = ETeams::EnemyTeam1;

	AActorEntityBase* EnemyAsBaseClass = Cast<AActorEntityBase>(ReturnEnemy);
	EnemyAsBaseClass = FinishSpawningEntity(EnemyAsBaseClass);
	return Cast<AActorEntityEnemy>(EnemyAsBaseClass);
}


AActorEntityPlayer* ALostWorldGameModeBattle::SpawnPlayerEntity(const FEntity& InEntityData)
{
	const FActorSpawnParameters SpawnParameters;

	AActorEntityPlayer* ReturnEntity = GetWorld()->SpawnActor<AActorEntityPlayer>(ActorEntityPlayerBlueprintClass,
		FVector(0, 0, 0),FRotator::ZeroRotator, SpawnParameters);

	ReturnEntity->EntityData = InEntityData;
	ReturnEntity->EntityData.Team = ETeams::PlayerTeam;

	AActorEntityBase* EntityAsBaseClass = Cast<AActorEntityBase>(ReturnEntity);
	EntityAsBaseClass = FinishSpawningEntity(EntityAsBaseClass);
	return Cast<AActorEntityPlayer>(EntityAsBaseClass);
}


// -------------------------------- Pre-battle 
void ALostWorldGameModeBattle::PreBattleTurnZero(const FEncounter& EnemyEncounter)
{
	// List of things that need to happen during 'Turn Zero':
	// Calculate the turn order.
	// Apply card modifiers that trigger at the start of battles.
	// Shuffle everyone's decks.
	// Each entity draws a hand of cards.
	// Give each entity the status effects they should start the battle with,
	// Then trigger each status effect that triggers at the start of a battle.
	
	// Lazy turn order calculation:
	// The player goes first.
	// then the players' allies, in whatever order the game finds them.
	// then the enemies, in whatever order the game finds them.

	// Calculate turn order.
	AddMaxNumberOfEntitiesToTurnQueue(true);

	// Apply card modifiers that trigger at the start of battles.
	for (auto& Entity : EntitiesInBattleArray) {
		for (int Index = 0; Index < Entity->EntityData.Deck.Num(); Index++) {
			FCard Copy = ApplyAllCardModifiersWithoutTimingTriggers(Entity->EntityData.Deck[Index]);
			Entity->EntityData.DrawPile.Add(Copy);
		}
	}
	
	for (auto& Entity : EntitiesInBattleArray) {
		// Since this is the start of the battle, we can erase the current draw pile and make it a copy of the deck.
		Entity->EntityData.DrawPile.Empty();
		Entity->EntityData.DrawPile = Entity->EntityData.Deck;
		
		if (Cast<AActorEntityEnemy>(Entity)) {
			Entity->EntityData.DrawPile = Cast<AActorEntityEnemy>(Entity)->ShuffleDrawPile(Entity->EntityData.DrawPile);
		} else if (Cast<AActorEntityPlayer>(Entity)) {
			Entity->EntityData.DrawPile = Cast<AActorEntityPlayer>(Entity)->ShuffleDrawPile(Entity->EntityData.DrawPile);
		}
	}

	// Draw a full grip.
	for (auto& Entity : EntitiesInBattleArray) {
		if (Cast<AActorEntityEnemy>(Entity)) {
			for (int DrawCount = 0; DrawCount < Entity->EntityData.StartOfBattleHandSize; DrawCount++) {
				Cast<AActorEntityEnemy>(Entity)->DrawCard();
			}
		} else if (Cast<AActorEntityPlayer>(Entity)) {
			for (int DrawCount = 0; DrawCount < Entity->EntityData.StartOfBattleHandSize; DrawCount++) {
				Cast<AActorEntityPlayer>(Entity)->DrawCard();
			}
		}
	}

	// Initialize each entity's billboard.
	// To-Do: Figure out if this is redundant, considering it also happens when the entity is spawned.
	for (AActorEntityBase* Entity : EntitiesInBattleArray) {
		Entity->ResetEntityBillboardPositionAndRotation();
		Cast<UWidgetEntityBillboard>(Entity->EntityBillboard->GetUserWidgetObject())->UpdateBillboard(Entity->EntityData);
	}

	// Give each entity the status effects they should start the battle with,
	// And trigger all status effects that trigger at the start of battles.
	for (AActorEntityBase* Entity : EntitiesInBattleArray) {
		for (EStatusEffectFunctions StatusFunction : Entity->EntityData.StartBattleWithStatusEffectFunctions) {
			Cast<IInterfaceBattle>(Entity)->AddStatusEffect(
				Cast<ULostWorldGameInstanceBase>(GetWorld()->GetGameInstance())->GetStatusEffectFromJson(StatusFunction));

			if (Entity->EntityData.StatusEffects.Last().TimingTriggers.Contains(ETimingTriggers::StartOfBattle)) {
				AFunctionLibraryStatusEffects::ExecuteFunction(Entity->EntityData.StatusEffects.Last().StatusEffect, Entity);
			}
		}
	}

	// Begin the turn for the first entity in the turn array.
	if (Cast<AActorEntityEnemy>(TurnQueue[0])) {
		Cast<AActorEntityEnemy>(TurnQueue[0])->AiBrainComponent->StartTurn();
	} else if (Cast<AActorEntityPlayer>(TurnQueue[0])) {
		Cast<AActorEntityPlayer>(TurnQueue[0])->StartTurn();
	}
}


// -------------------------------- Battle: Starting Phase
void ALostWorldGameModeBattle::StartOfTurn()
{
	if (TurnQueue.Num() < 15) {
		AddMaxNumberOfEntitiesToTurnQueue(false);
	}


	Cast<IInterfaceBattle>(TurnQueue[0])->StartTurn();
}


void ALostWorldGameModeBattle::DrawPhaseDrawCard()
{
	Cast<IInterfaceBattle>(TurnQueue[0])->DrawCard();
}


void ALostWorldGameModeBattle::AddMaxNumberOfEntitiesToTurnQueue(bool OverrideReadiness)
{
	// Each entity in battle has a 'readiness' value.
	// When an entity's readiness value reaches 1000, add it to the turn queue,
	// and reset the value.
	
	TArray<AActor*> ActorsInBattle;
	TArray<AActorEntityBase*> Entities;
	int TurnQueueSize = TurnQueue.Num();

	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AActorEntityBase::StaticClass(), ActorsInBattle);
	
	for (AActor* Actor : ActorsInBattle) {
		if (Cast<AActorEntityEnemy>(Actor)) {
			if (OverrideReadiness) {
				Cast<AActorEntityEnemy>(Actor)->EntityData.TotalStats.Readiness = FMath::RandRange(0, Cast<AActorEntityEnemy>(Actor)->EntityData.TotalStats.Agility);
			}
			
			Entities.Add(Cast<AActorEntityEnemy>(Actor));
		} else if (Cast<AActorEntityPlayer>(Actor)) {
			if (OverrideReadiness) {
				Cast<AActorEntityPlayer>(Actor)->EntityData.TotalStats.Readiness = FMath::RandRange
				(0, Cast<AActorEntityPlayer>(Actor)->EntityData.TotalStats.Agility);
			}
			
			Entities.Add(Cast<AActorEntityPlayer>(Actor));
		}
	}

	for (int EntityCount = 0; EntityCount < 15 - TurnQueueSize; EntityCount++) {
		bool EntityHasReachedThreshold = false;

		while (!EntityHasReachedThreshold) {
			for (AActorEntityBase* Entity : Entities) {
				float EntityAgility = Entity->EntityData.TotalStats.Agility;
				// Declaring these floats here to avoid 'ambiguous call to overloaded function' errors.
				float IncrementMinimum = ((EntityAgility / 64) * 0.9) + 10;
				float IncrementMaximum = ((EntityAgility / 64) * 1.1) + 10;
				float ReadinessIncrement = FMath::RandRange(IncrementMinimum, IncrementMaximum);
				
				DualLog(FString::SanitizeFloat(IncrementMinimum) + " / " + FString::SanitizeFloat(IncrementMaximum), 4);
				DualLog(FString::SanitizeFloat(ReadinessIncrement) + + " - " + FString::SanitizeFloat(Entity->EntityData.TotalStats.Readiness), 4);
				
				Entity->EntityData.TotalStats.Readiness += ReadinessIncrement;
				if (Entity->EntityData.TotalStats.Readiness >= 1000) {
					Entity->EntityData.TotalStats.Readiness -= 1000;
					EntityHasReachedThreshold = true;
					TurnQueue.Add(Entity);
				}
			}
		}
	}
}


// -------------------------------- Battle: Main Phase
void ALostWorldGameModeBattle::CreateStackEntry(int CardIndexInHandArray)
{
	// This function should only add one stack entry at a time.
	// This allows for getting targets one at a time.
	// Card functions and mods that need to add multiple stack entries should have a way of tracking
	// how many stack entries are remaining; e.g.
	// X cost cards can reduce the temporary total cost by 1 per stack entry.
	
	// Get a reference to the card in the player's hand.
	// Don't pass a copy of the FCard struct.
	// The stack entry will keep track of the target(s).
	FCard CardToCast = TurnQueue[0]->EntityData.Hand[CardIndexInHandArray];
	TArray<ECardFunctions> CardFunctions;
	TArray<ECardModifiers> CardMods;
	CardToCast.FunctionsAndTargets.GetKeys(CardFunctions);
	CardToCast.ModifiersWithTriggers.GetKeys(CardMods);

	// Handle cards that want to create and add multiple stack entries here.
	if (CardFunctions.Contains(ECardFunctions::AddTotalCostStackEntries)) {
		while (CardToCast.TotalCost > 0) {
			TempStackEntry.Function = CardFunctions[0];
			TempStackEntry.TargetingMode = *CardToCast.FunctionsAndTargets.Find(CardFunctions[0]);
			TempStackEntry.Controller = TurnQueue[0];
			TempStackEntry.SelectedTargets.Empty();
			TempStackEntry.IndexInHandArray = CardIndexInHandArray;
			TempStackEntry.Card = CardToCast;
			
			TheStack.Add(TempStackEntry);

			// Only the last stack entry should continue stack execution beyond getting targets.
			if (CardToCast.TotalCost == 1) {
				GetTargetsForStackEntry(TheStack.Num() - 1, true);
			} else {
				GetTargetsForStackEntry(TheStack.Num() - 1, false);
			}
			
			CardToCast.TotalCost--;
		}
	} else if (CardFunctions.Num() > 1) {
		for (auto& Function : CardFunctions) {
			TempStackEntry.Function = Function;
			TempStackEntry.TargetingMode = *CardToCast.FunctionsAndTargets.Find(Function);
			TempStackEntry.Controller = TurnQueue[0];
			TempStackEntry.SelectedTargets.Empty();
			TempStackEntry.IndexInHandArray = CardIndexInHandArray;
			TempStackEntry.Card = CardToCast;

			TheStack.Add(TempStackEntry);

			// Only the last stack entry should continue stack execution beyond getting targets.
			if (CardFunctions.Last() == Function) {
				GetTargetsForStackEntry(TheStack.Num() - 1, true);
			} else {
				GetTargetsForStackEntry(TheStack.Num() - 1, false);
			}
		}
	} else {
		TempStackEntry.Function = CardFunctions[0];
		TempStackEntry.TargetingMode = *CardToCast.FunctionsAndTargets.Find(CardFunctions[0]);
		TempStackEntry.Controller = TurnQueue[0];
		TempStackEntry.SelectedTargets.Empty();
		TempStackEntry.IndexInHandArray = CardIndexInHandArray;
		TempStackEntry.Card = CardToCast;
		
		TheStack.Add(TempStackEntry);

		GetTargetsForStackEntry(TheStack.Num() - 1, true);
	}

	// Here, we can also create stack entries for functions that are appended onto the card.
	// E.g. the Cantrip effect can create another stack entry to draw the controller a card.
	if (CardMods.Contains(ECardModifiers::Cantrip)) {
		TempStackEntry.Function = ECardFunctions::CasterDrawsOneCard;
		TempStackEntry.TargetingMode = ECardTargets::Self;
		TempStackEntry.Controller = TurnQueue[0];
		TempStackEntry.SelectedTargets.Empty();
		TempStackEntry.IndexInHandArray = CardIndexInHandArray;
		TempStackEntry.Card = CardToCast;
		
		TheStack.Add(TempStackEntry);

		GetTargetsForStackEntry(TheStack.Num() - 1, true);
	}
}


void ALostWorldGameModeBattle::GetTargetsForStackEntry(const int Index, bool ContinueStackEntryExecution)
{
	//const int NullIndex = -1;
	//const TArray<AActorEntityBase*> NullArray;
	
	if (TheStack[Index].TargetingMode == ECardTargets::Self) {
		// Self target.
		TheStack[Index].SelectedTargets.Add(TheStack[Index].Controller);
		
		if (ContinueStackEntryExecution) {
			FinishedGettingTargetsForCard(Index, TheStack[Index].SelectedTargets);
		}
	} else if (TheStack[Index].TargetingMode == ECardTargets::OneEnemy ||
		TheStack[Index].TargetingMode == ECardTargets::AnyOneEntity) {
		// One entity.
		if (Cast<AActorEntityPlayer>(TurnQueue[0])) {
			Cast<ALostWorldPlayerControllerBattle>(UGameplayStatics::GetPlayerController(GetWorld(), 0))->
				SetControlMode(EPlayerControlModes::TargetSelectionSingleEntity);
	
			Cast<ALostWorldPlayerControllerBattle>(UGameplayStatics::GetPlayerController(GetWorld(), 0))->
				BattleHudWidget->PlayerStartCastingCard(TheStack[Index].Card, TheStack[Index].IndexInHandArray,
				TheStack[Index].TargetingMode, Index);
		} else {
			Cast<AActorEntityEnemy>(TurnQueue[0])->AiBrainComponent->GetTargetsForCard(Index);
		}
	} else if (TheStack[Index].TargetingMode == ECardTargets::AllEnemies) {
		// All entities on the same team.
		TArray<AActor*> FoundActors;
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), AActorEntityBase::StaticClass(), FoundActors);

		for (AActor* Actor : FoundActors) {
			if (Cast<AActorEntityBase>(Actor)->EntityData.Team != TheStack[Index].Controller->EntityData.Team) {
				TheStack[Index].SelectedTargets.Add(Cast<AActorEntityBase>(Actor));
			}
		}

		if (ContinueStackEntryExecution) {
			FinishedGettingTargetsForCard(Index, TheStack[Index].SelectedTargets);
		}
	} else {
		DualLog("Error! No valid targeting mode for stack entry!", 2);
	}
}


/** Before the execution of stack entries can continue,
we need to validate that all stack entries have valid targets.
If one doesn't, we might be waiting for the player to select a target.

This function will also handle manual target selection.
Whenever a player or NPC manually selects a target, they can pass it to this function alongside the
stack entry index that the targets are for.*/
void ALostWorldGameModeBattle::FinishedGettingTargetsForCard(const int Index, const TArray<AActorEntityBase*>& Targets)
{
	if (Index != -1 && Targets.Num() > 0 && TheStack[Index].SelectedTargets.Num() < 1) {
		TheStack[Index].SelectedTargets = Targets;
	}
	
	bool AllStackEntriesHaveTargets = true;
	for (auto& Entry : TheStack) {
		if (Entry.SelectedTargets.Num() < 1 && AllStackEntriesHaveTargets) {
			// If we find one stack entry that doesn't have targets, that's enough to pause execution.
			AllStackEntriesHaveTargets = false;
		}
	}
	
	// Once the card has created all of the stack entries it needs to, the entity
	// must discard the card from their hand.
	if (AllStackEntriesHaveTargets) {
		PayCostsForCard(Index);

		PayCostsAndDiscardCardEntity->DiscardCard(PayCostsAndDiscardCardHandIndex);

		CardsCastThisTurn++;

		GetWorld()->GetTimerManager().SetTimer(StackExecutionTimerHandle, this,
			&ALostWorldGameModeBattle::ExecuteFirstStackEntry,1.5f, false);
	}
}


/** This function should be able to handle the primary cost and all secondary costs.

If the cost of a card is X:\n
Players: Give Players a prompt to select the value of X.\n
AI: Use an AiBrain function to override the total cost.*/
void ALostWorldGameModeBattle::PayCostsForCard(int StackIndex) const
{
	if (TheStack[StackIndex].Controller->EntityData.Hand[PayCostsAndDiscardCardHandIndex].BaseCost != -1) {
		PayCostsAndDiscardCardEntity->PayCostsForCard(PayCostsAndDiscardCardHandIndex);
	} else {
		// Check if the entity has already overriden the total cost of the card.
		if (TheStack[StackIndex].Card.TotalCost == -1) {
			DualLog("The MP for this X-Cost spell " +
				TheStack[StackIndex].Controller->EntityData.Hand[PayCostsAndDiscardCardHandIndex].DisplayName +
				" needs to be paid!", 2);
		}
	}

	DualLog(PayCostsAndDiscardCardEntity->EntityData.DisplayName + " casts " +
		PayCostsAndDiscardCardEntity->EntityData.Hand[PayCostsAndDiscardCardHandIndex].DisplayName + "!", 2);
}


void ALostWorldGameModeBattle::ExecuteFirstStackEntry()
{
	if (!FunctionLibraryCardsInstance) {
		FunctionLibraryCardsInstance = GetWorld()->SpawnActor<AFunctionLibraryCards>();
	}
	
	FunctionLibraryCardsInstance->ExecuteFunction(TheStack[0].Function);

	TheStack.RemoveAt(0);

	// If there are more stack entries, keep executing them until there are none.
	// Then, if the currently acting entity is a player, give them full control again.
	// If they're a NPC, call a function that resumes their AI execution.
	if (TheStack.Num() > 0) {
		if (TheStack[0].Function == ECardFunctions::WaitForPreviousFunctionPlayerInput) {
			DualLog("Awaiting player input.", 2);
		} else {
			GetWorld()->GetTimerManager().SetTimer(StackExecutionTimerHandle, this,
				&ALostWorldGameModeBattle::ExecuteFirstStackEntry,1.5f, false);
		}
	} else {
		// To-Do: Make an AI that can cast multiple cards in a turn.
		if (Cast<AActorEntityEnemy>(TurnQueue[0])) {
			Cast<AActorEntityEnemy>(TurnQueue[0])->AiBrainComponent->EndTurn();
		}
	}
}


void ALostWorldGameModeBattle::RemoveEntityFromTurnQueue(const AActorEntityBase* Entity)
{
	for (int Index = TurnQueue.Num() - 1; Index >= 0; Index--) {
		if (TurnQueue[Index] == Entity) {
			TurnQueue.RemoveAt(Index);
		}
	}
}


// -------------------------------- Battle: Ending Phase
void ALostWorldGameModeBattle::EndOfTurn()
{
	if (Cast<AActorEntityEnemy>(TurnQueue[0])) {
		Cast<AActorEntityEnemy>(TurnQueue[0])->EndTurn();
	}

	// To-Do: Search for all Temporary cards and exile them.
	for (AActorEntityBase* Entity : EntitiesInBattleArray) {
		for (FCard CardInHand : Entity->EntityData.Hand) {
			if (CardInHand.Keywords.Contains(ECardKeywords::Ephemeral)) {
				Cast<IInterfaceBattle>(Entity)->ExileCardFromZone("Hand", CardInHand);
			}
		}
	}
	
	TurnQueue.RemoveAt(0);

	StartOfTurn();
}


// -------------------------------- Level Generation
void ALostWorldGameModeBattle::GenerateLevelAndSpawnEverything()
{
	// If the Level data doesn't exist, create it (with default values.)
	if (!LevelDataSaveGameReference) {
		LevelDataSaveGameReference = Cast<USaveGameLevelData>(UGameplayStatics::CreateSaveGameObject(USaveGameLevelData::StaticClass()));
	}

	// If the LevelData var is equal to the default, that means it hasn't been loaded.
	if (LevelDataSaveGameReference->LevelData == FLevelDataAsStruct()) {
		LevelDataSaveGameReference->LoadLevelDataFromJson();
	}

	// Create a copy of the LevelData variable for editing and assigning variables.
	LevelDataCopy = LevelDataSaveGameReference->LevelData;

	// Randomly generate the boundaries of the level.
	LevelDataCopy.FloorDataAsStruct.BottomLeftBoundary = FIntVector2D(1, 1);
	LevelDataCopy.FloorDataAsStruct.BottomRightBoundary = FIntVector2D(1,
		FMath::RandRange(LevelDataCopy.FloorDataAsStruct.MinimumWidth, LevelDataCopy.FloorDataAsStruct.MaximumWidth));
	LevelDataCopy.FloorDataAsStruct.TopLeftBoundary = FIntVector2D(
		FMath::RandRange(LevelDataCopy.FloorDataAsStruct.MinimumLength, LevelDataCopy.FloorDataAsStruct.MaximumLength), 1);
	LevelDataCopy.FloorDataAsStruct.TopRightBoundary = FIntVector2D(
		LevelDataCopy.FloorDataAsStruct.TopLeftBoundary.X, LevelDataCopy.FloorDataAsStruct.BottomRightBoundary.Y);

	DualLog("Level bottom left boundary: " + FString::FromInt(LevelDataCopy.FloorDataAsStruct.BottomLeftBoundary.X) +
		", " + FString::FromInt(LevelDataCopy.FloorDataAsStruct.BottomLeftBoundary.Y), 5);
	DualLog("Level top right boundary: " + FString::FromInt(LevelDataCopy.FloorDataAsStruct.TopRightBoundary.X) +
		", " + FString::FromInt(LevelDataCopy.FloorDataAsStruct.TopRightBoundary.Y), 5);

	// Generate the layout of the rooms and corridors.
	switch (LevelDataCopy.FloorDataAsStruct.Layout)
	{
	case EFloorLayouts::FourSquares:
		GenerateLevelLayoutFourSquares();
		break;
	default:
		// The FourSquares layout will be used as the default.
		GenerateLevelLayoutFourSquares();
		break;
	}
	
	// Once all of the GridTiles are spawned, we can spawn everything else, including but not limited to:
	// The player, enemies, the stairs, treasure chests.

	// Get all of the room GridTiles and add them to an array.
	// When something is spawned, remove that GridTile from the array,
	// so that everything can be spawned on a unique tile.
	TArray<AActorGridTile*> ValidSpawnTilesArray;
	// ReSharper disable once CppTooWideScope
	const FActorSpawnParameters SpawnParameters;
	
	for (int RoomCount = 0; RoomCount < LevelDataCopy.FloorDataAsStruct.RoomDataAsStructsArray.Num(); RoomCount++) {
		for (int TileCount = 0; TileCount < LevelDataCopy.FloorDataAsStruct.RoomDataAsStructsArray[RoomCount].GridTilesInRoom.Num(); TileCount++) {
			ValidSpawnTilesArray.Add(LevelDataCopy.FloorDataAsStruct.RoomDataAsStructsArray[RoomCount].GridTilesInRoom[TileCount]);
		}
	}
	
	// List of things to spawn and their indices;
	// (Use only one index for things that come in multiples (e.g. enemies))
	// 0 = The Player
	// 1 = The Stairs
	// 2 = Enemy encounters
	// 3 = Treasure chests
	for (int SpawnIndex = 0; SpawnIndex < 3; SpawnIndex++) {
		int RandomArrayIndex = FMath::RandRange(0, ValidSpawnTilesArray.Num() - 1);
		AActorGridTile* RandomGridTile = ValidSpawnTilesArray[RandomArrayIndex];

		switch (SpawnIndex)
		{
		case 0:
		{
			// Player data loading is handled in the GameInstanceBase.
			// Here, we just fetch it from the GameInstance.
				Cast<ULostWorldGameInstanceBase>(GetWorld()->GetGameInstance())->LoadPlayerSaveJson();
			FEntity PlayerData = Cast<ULostWorldGameInstanceBase>(GetWorld()->GetGameInstance())->CurrentPlayerSave.EntityData;
			AActorEntityPlayer* PlayerEntityReference = SpawnPlayerEntity(PlayerData);

			// Set Camera Target.
			FViewTargetTransitionParams Params;
			GetWorld()->GetFirstPlayerController()->SetViewTarget(PlayerEntityReference, Params); // This line isn't multiplayer safe
			PlayerEntityReference->Camera->SetActive(true);

			// Add the level HUD to the player's screen.
			Cast<ALostWorldPlayerControllerBase>(GetWorld()->GetFirstPlayerController())->AddLevelHudToViewport();

			// Player stat calculation.
			PlayerEntityReference->CalculateTotalStats();

			// Players' first time billboard setup.
			Cast<UWidgetEntityBillboard>(PlayerEntityReference->EntityBillboard->GetUserWidgetObject())->UpdateBillboard(PlayerEntityReference->EntityData);
			PlayerEntityReference->ResetEntityBillboardPositionAndRotation();

			// Take control of the entity	.
			Cast<ALostWorldPlayerControllerBase>(GetWorld()->GetFirstPlayerController())->ControlledPlayerEntity = PlayerEntityReference;	
			break;
		}
		case 2:
		{
			int NumberOfEncounters = 0;
			FRoomDataAsStruct RandomRoom;
			bool CoinFlip = true;
				
			// Use this Array to randomly generate encounters in randomly chosen rooms,
			// except for the first randomly chosen room, which will always have an encounter.
			TArray<int> RoomIndicesArray;	
			TArray<int> ShuffledRoomIndicesArray = {};
			
			// Get all of the room indices in order.
			for (int RoomCount = 0; RoomCount < LevelDataCopy.FloorDataAsStruct.RoomDataAsStructsArray.Num(); RoomCount++) {
				RoomIndicesArray.Add(RoomCount);
			}
				
			// Shuffle up the room integers array into a second array.
			for (int RandomRoomCount = 0; RandomRoomCount < LevelDataCopy.FloorDataAsStruct.RoomDataAsStructsArray.Num(); RandomRoomCount++) {
				int RandomIndex = RoomIndicesArray[FMath::RandRange(0, RoomIndicesArray.Num() - 1)];

				ShuffledRoomIndicesArray.Add(RandomIndex);
				RoomIndicesArray.Remove(RandomIndex);
			}

			// Guarantee at least one encounter in one room.
			// Use the shuffled room indices array to get the room that the encounter will be spawned in to.
			// For each other room, randomly decide whether or not to spawn an encounter.
			while (ShuffledRoomIndicesArray.Num() > 0) {
				if (NumberOfEncounters > 0) {
					//CoinFlip = FMath::RandBool();
					CoinFlip = true;
				}

				if (CoinFlip) {
					RandomRoom = LevelDataCopy.FloorDataAsStruct.RoomDataAsStructsArray[ShuffledRoomIndicesArray[0]];
					RandomArrayIndex = FMath::RandRange(0, RandomRoom.GridTilesInRoom.Num() - 1);
					RandomGridTile = RandomRoom.GridTilesInRoom[RandomArrayIndex];

					// To-Do: Choose an encounter from the levels' list of possible encounters,
					// factoring in the current floor and the encounters' minimum and maximum levels.
					int RandomEnemyEncounter = FMath::RandRange(0, LevelDataCopy.Encounters.Num() - 1);
					RandomGridTile->Encounter = LevelDataCopy.Encounters[RandomEnemyEncounter];
					RandomGridTile->SetTileColour(FLinearColor(0.25f, 0.f, 0.f));
				}

				// Cap the number of encounters generated to be equal to the number of rooms in the level.
				ShuffledRoomIndicesArray.RemoveAt(0);
			}
		
			break;
		}
		default:
			break;
		}

		ValidSpawnTilesArray.Remove(RandomGridTile);
	}
}


void ALostWorldGameModeBattle::GenerateLevelLayoutFourSquares()
{
	// Four Squares level layout:
	// Divide the level up into four roughly equal quadrants.
	// Generate one room for each quadrant.
	// Use the boundaries of the rooms to generate hallways that connect them.

	// ReSharper disable once CppTooWideScope
	const FActorSpawnParameters SpawnParameters;
	
	// Step One:
	for (int RoomCount = 0; RoomCount < LevelDataCopy.FloorDataAsStruct.RoomDataAsStructsArray.Num(); RoomCount++) {
		// In the level data copy, the minimum and maximum lengths and widths will become the boundaries of the rooms.
		int CalculatedLengthAndWidth = FMath::RandRange(
			LevelDataCopy.FloorDataAsStruct.RoomDataAsStructsArray[RoomCount].MinimumLength,
			LevelDataCopy.FloorDataAsStruct.RoomDataAsStructsArray[RoomCount].MaximumLength);

		// Since this Layout is 'Four Squares', each room will have one variable that determines the dimensions of the room.
		LevelDataCopy.FloorDataAsStruct.RoomDataAsStructsArray[RoomCount].MaximumLength = CalculatedLengthAndWidth;
		LevelDataCopy.FloorDataAsStruct.RoomDataAsStructsArray[RoomCount].MaximumWidth =
			LevelDataCopy.FloorDataAsStruct.RoomDataAsStructsArray[RoomCount].MaximumLength;
		LevelDataCopy.FloorDataAsStruct.RoomDataAsStructsArray[RoomCount].MinimumLength =
			LevelDataCopy.FloorDataAsStruct.RoomDataAsStructsArray[RoomCount].MaximumLength;
		LevelDataCopy.FloorDataAsStruct.RoomDataAsStructsArray[RoomCount].MinimumWidth =
			LevelDataCopy.FloorDataAsStruct.RoomDataAsStructsArray[RoomCount].MaximumLength;
		
		DualLog("Room " + FString::FromInt(RoomCount) + " calculated width and length: " + FString::FromInt(CalculatedLengthAndWidth), 5);

		// Calculate the boundaries of the room, then calculate their positions in the level.
		// When the boundaries of the level are odd numbers, we round up for quadrant 4 and round down for all other quadrants
		// Quadrant 1 is the bottom-left corner. The bottom-left corner of the bottom-left quadrant always equals 1,1.
		// Quadrant 4 is the top-right corner. The top-right corner of the top-right quadrant always equals the maximum length and width.
		// Quadrant 2 is the bottom-right corner. It runs along the Width / Y axis, and shares the same X value as quadrant 1.
		// Quadrant 3 is in the top-left corner. It runs along the Length / X axis, and shares the same Y value as quadrant 1.

		// 2024/09/28 Addendum: Calculating the boundaries of the rooms also needs to account for the boundaries of the quadrants.
		// Currently, there aren't any checks that the rooms are generated outside of the level boundaries.
		// We can 'assign' rooms to quadrants by putting the top-right corner into a quadrant
		// and calculating the other boundaries using the top-right corner.

		// Room 3 is the room in the top-right quadrant.
		// Room 2 is the room in the top-left quadrant.
		// Room 1 is the room in the bottom-right quadrant.
		// Room 0 is the room in the bottom-left quadrant.
		if (RoomCount == 3) {
			LevelDataCopy.FloorDataAsStruct.RoomDataAsStructsArray[RoomCount].TopRightBoundary.X =
				FMath::RandRange(FMath::CeilToInt(LevelDataCopy.FloorDataAsStruct.TopRightBoundary.X / 2) + 2 + CalculatedLengthAndWidth, LevelDataCopy.FloorDataAsStruct.TopRightBoundary.X);
			LevelDataCopy.FloorDataAsStruct.RoomDataAsStructsArray[RoomCount].TopRightBoundary.Y =
				FMath::RandRange(FMath::CeilToInt(LevelDataCopy.FloorDataAsStruct.TopRightBoundary.Y / 2) + 2 + CalculatedLengthAndWidth, LevelDataCopy.FloorDataAsStruct.TopRightBoundary.Y);
		} else if (RoomCount == 2) {
			LevelDataCopy.FloorDataAsStruct.RoomDataAsStructsArray[RoomCount].TopRightBoundary.X =
				FMath::RandRange(FMath::CeilToInt(LevelDataCopy.FloorDataAsStruct.TopRightBoundary.X / 2) + CalculatedLengthAndWidth, LevelDataCopy.FloorDataAsStruct.TopRightBoundary.X);
			LevelDataCopy.FloorDataAsStruct.RoomDataAsStructsArray[RoomCount].TopRightBoundary.Y =
				FMath::RandRange(CalculatedLengthAndWidth, FMath::FloorToInt(LevelDataCopy.FloorDataAsStruct.TopRightBoundary.Y / 2));
		} else if (RoomCount == 1) {
			LevelDataCopy.FloorDataAsStruct.RoomDataAsStructsArray[RoomCount].TopRightBoundary.X =
				FMath::RandRange(CalculatedLengthAndWidth, FMath::FloorToInt(LevelDataCopy.FloorDataAsStruct.TopRightBoundary.X / 2));
			LevelDataCopy.FloorDataAsStruct.RoomDataAsStructsArray[RoomCount].TopRightBoundary.Y =
				FMath::RandRange(FMath::CeilToInt(LevelDataCopy.FloorDataAsStruct.TopRightBoundary.Y / 2) + CalculatedLengthAndWidth, LevelDataCopy.FloorDataAsStruct.TopRightBoundary.Y);
		} else if (RoomCount == 0) {
			LevelDataCopy.FloorDataAsStruct.RoomDataAsStructsArray[RoomCount].TopRightBoundary.X =
				FMath::RandRange(CalculatedLengthAndWidth, FMath::FloorToInt(LevelDataCopy.FloorDataAsStruct.TopRightBoundary.X / 2) - 1);
			LevelDataCopy.FloorDataAsStruct.RoomDataAsStructsArray[RoomCount].TopRightBoundary.Y =
				FMath::RandRange(CalculatedLengthAndWidth, FMath::FloorToInt(LevelDataCopy.FloorDataAsStruct.TopRightBoundary.Y / 2) - 1);
		}

		// Use the top-right boundary coordinates to calculate the rest of the boundary coordinates.
		LevelDataCopy.FloorDataAsStruct.RoomDataAsStructsArray[RoomCount].TopLeftBoundary.X =
			LevelDataCopy.FloorDataAsStruct.RoomDataAsStructsArray[RoomCount].TopRightBoundary.X - CalculatedLengthAndWidth;
		LevelDataCopy.FloorDataAsStruct.RoomDataAsStructsArray[RoomCount].TopLeftBoundary.Y =
			LevelDataCopy.FloorDataAsStruct.RoomDataAsStructsArray[RoomCount].TopRightBoundary.Y;

		LevelDataCopy.FloorDataAsStruct.RoomDataAsStructsArray[RoomCount].BottomRightBoundary.X =
			LevelDataCopy.FloorDataAsStruct.RoomDataAsStructsArray[RoomCount].TopRightBoundary.X;
		LevelDataCopy.FloorDataAsStruct.RoomDataAsStructsArray[RoomCount].BottomRightBoundary.Y =
			LevelDataCopy.FloorDataAsStruct.RoomDataAsStructsArray[RoomCount].TopRightBoundary.Y - CalculatedLengthAndWidth;
		
		LevelDataCopy.FloorDataAsStruct.RoomDataAsStructsArray[RoomCount].BottomLeftBoundary.X =
			LevelDataCopy.FloorDataAsStruct.RoomDataAsStructsArray[RoomCount].TopRightBoundary.X - CalculatedLengthAndWidth;
		LevelDataCopy.FloorDataAsStruct.RoomDataAsStructsArray[RoomCount].BottomLeftBoundary.Y =
			LevelDataCopy.FloorDataAsStruct.RoomDataAsStructsArray[RoomCount].TopRightBoundary.Y - CalculatedLengthAndWidth;

		DualLog("Room " + FString::FromInt(RoomCount) + " bottom left boundary: " +
			FString::FromInt(LevelDataCopy.FloorDataAsStruct.RoomDataAsStructsArray[RoomCount].BottomLeftBoundary.X) + ", " +
			FString::FromInt(LevelDataCopy.FloorDataAsStruct.RoomDataAsStructsArray[RoomCount].BottomLeftBoundary.Y), 4);
		DualLog("Room " + FString::FromInt(RoomCount) + " bottom right boundary: " +
			FString::FromInt(LevelDataCopy.FloorDataAsStruct.RoomDataAsStructsArray[RoomCount].BottomRightBoundary.X) + ", " +
			FString::FromInt(LevelDataCopy.FloorDataAsStruct.RoomDataAsStructsArray[RoomCount].BottomRightBoundary.Y), 4);
		DualLog("Room " + FString::FromInt(RoomCount) + " top left boundary: " +
			FString::FromInt(LevelDataCopy.FloorDataAsStruct.RoomDataAsStructsArray[RoomCount].TopLeftBoundary.X) + ", " +
			FString::FromInt(LevelDataCopy.FloorDataAsStruct.RoomDataAsStructsArray[RoomCount].TopLeftBoundary.Y), 4);
		DualLog("Room " + FString::FromInt(RoomCount) + " top right boundary: " +
			FString::FromInt(LevelDataCopy.FloorDataAsStruct.RoomDataAsStructsArray[RoomCount].TopRightBoundary.X) + ", " +
			FString::FromInt(LevelDataCopy.FloorDataAsStruct.RoomDataAsStructsArray[RoomCount].TopRightBoundary.Y), 4);

		// For each valid coordinate in each room, spawn a GridTile actor at those coordinates.
		for (int LengthCount = LevelDataCopy.FloorDataAsStruct.RoomDataAsStructsArray[RoomCount].BottomLeftBoundary.X;
			LengthCount <= LevelDataCopy.FloorDataAsStruct.RoomDataAsStructsArray[RoomCount].TopRightBoundary.X;
			LengthCount++) {
			for (int WidthCount = LevelDataCopy.FloorDataAsStruct.RoomDataAsStructsArray[RoomCount].BottomLeftBoundary.Y;
				WidthCount <= LevelDataCopy.FloorDataAsStruct.RoomDataAsStructsArray[RoomCount].TopRightBoundary.Y;
				WidthCount++)
			{
				LevelDataCopy.FloorDataAsStruct.RoomDataAsStructsArray[RoomCount].GridTilesInRoom.Add(
					GetWorld()->SpawnActor<AActorGridTile>(ActorGridTileBlueprintClass,
					FVector(LengthCount * 200, WidthCount * 200, 0),
					FRotator::ZeroRotator,
					SpawnParameters));
				
				// Assign variables to the tile here.
				LevelDataCopy.FloorDataAsStruct.RoomDataAsStructsArray[RoomCount].GridTilesInRoom.Last()->
					RoomIndex = RoomCount;

				// Take note of which tiles are in the corners.
				if (LengthCount == LevelDataCopy.FloorDataAsStruct.RoomDataAsStructsArray[RoomCount].BottomLeftBoundary.X &&
					WidthCount == LevelDataCopy.FloorDataAsStruct.RoomDataAsStructsArray[RoomCount].BottomLeftBoundary.Y) {
					LevelDataCopy.FloorDataAsStruct.RoomDataAsStructsArray[RoomCount].BottomLeftCoordinate =
						FVector(LengthCount * 200, WidthCount * 200, 0);
				} else if (LengthCount == LevelDataCopy.FloorDataAsStruct.RoomDataAsStructsArray[RoomCount].TopRightBoundary.X &&
					WidthCount == LevelDataCopy.FloorDataAsStruct.RoomDataAsStructsArray[RoomCount].TopRightBoundary.Y) {
					LevelDataCopy.FloorDataAsStruct.RoomDataAsStructsArray[RoomCount].TopRightCoordinate =
						FVector(LengthCount * 200, WidthCount * 200, 0);
				}

				if (LengthCount == LevelDataCopy.FloorDataAsStruct.RoomDataAsStructsArray[RoomCount].TopRightBoundary.X &&
					WidthCount == LevelDataCopy.FloorDataAsStruct.RoomDataAsStructsArray[RoomCount].BottomLeftBoundary.Y) {
					LevelDataCopy.FloorDataAsStruct.RoomDataAsStructsArray[RoomCount].BottomRightCoordinate =
						FVector(LengthCount * 200, WidthCount * 200, 0);
				} else if (LengthCount == LevelDataCopy.FloorDataAsStruct.RoomDataAsStructsArray[RoomCount].BottomLeftBoundary.X &&
					WidthCount == LevelDataCopy.FloorDataAsStruct.RoomDataAsStructsArray[RoomCount].TopRightBoundary.Y) {
					LevelDataCopy.FloorDataAsStruct.RoomDataAsStructsArray[RoomCount].TopLeftCoordinate =
						FVector(LengthCount * 200, WidthCount * 200, 0);
				}
			}
		}

		// Calculate the middle point of the room.
		LevelDataCopy.FloorDataAsStruct.RoomDataAsStructsArray[RoomCount].RoomMidpoint =
			(LevelDataCopy.FloorDataAsStruct.RoomDataAsStructsArray[RoomCount].BottomLeftCoordinate +
			LevelDataCopy.FloorDataAsStruct.RoomDataAsStructsArray[RoomCount].TopRightCoordinate) / 2;
	}

	// Generate four corridors that connect the four rooms.
	for (int CorridorCount = 0; CorridorCount < LevelDataCopy.FloorDataAsStruct.CorridorDataAsStructsArray.Num(); CorridorCount++) {
		// Corridors will be listed and generated in clockwise order.
		// Corridor 0 = Bridge between the top two rooms.
		// Corridor 1 = Bridge between the right two rooms.
		// Corridor 2 = Bridge between the bottom two rooms.
		// Corridor 3 = Bridge between the left two rooms.

		// Corridors will be divided up in to two halves.
		// The first half will start in one room, and the second half will start in the opposite room.
		FIntVector2D CorridorFirstHalfStartingPoint;
		FIntVector2D CorridorSecondHalfStartingPoint;

		// The distance between rooms should not include room tiles.
		int YAxisDistanceBetweenRooms, XAxisDistanceBetweenRooms;
		
		if (CorridorCount == 0) {
			// Get the boundaries of the two rooms that the corridor should be spawned between in order to get the corridor starting points.
			// RoomDataAsStructsArray[2] = Top-left Quadrant Room
			// Get a random integer for the Right.X coordinate from between the Top-Right.X and Top-Right.X coordinates.
			// The Top-Right.Y and Bottom-Right.Y coordinates are the same.
			CorridorFirstHalfStartingPoint.X = FMath::RandRange(LevelDataCopy.FloorDataAsStruct.RoomDataAsStructsArray[2].TopLeftBoundary.X,
			LevelDataCopy.FloorDataAsStruct.RoomDataAsStructsArray[2].TopRightBoundary.X);
			CorridorFirstHalfStartingPoint.Y = FMath::RandRange(LevelDataCopy.FloorDataAsStruct.RoomDataAsStructsArray[2].TopLeftBoundary.Y,
			LevelDataCopy.FloorDataAsStruct.RoomDataAsStructsArray[2].TopRightBoundary.Y);

			// RoomDataAsStructsArray[3] = Top-right Quadrant Room
			// Get a random integer for the Left.X coordinate from between the Bottom-Left.X and Bottom-Right.X coordinates.
			// The Bottom-Left.Y and Bottom-Right.X coordinates are the same.
			CorridorSecondHalfStartingPoint.X = FMath::RandRange(LevelDataCopy.FloorDataAsStruct.RoomDataAsStructsArray[3].BottomLeftBoundary.X,
			LevelDataCopy.FloorDataAsStruct.RoomDataAsStructsArray[3].BottomRightBoundary.X);
			CorridorSecondHalfStartingPoint.Y = FMath::RandRange(LevelDataCopy.FloorDataAsStruct.RoomDataAsStructsArray[3].BottomLeftBoundary.Y,
			LevelDataCopy.FloorDataAsStruct.RoomDataAsStructsArray[3].BottomRightBoundary.Y);
		} else if (CorridorCount == 1) {
			// RoomDataAsStructsArray[1] = Bottom-right Quadrant Room
			CorridorFirstHalfStartingPoint.X = FMath::RandRange(LevelDataCopy.FloorDataAsStruct.RoomDataAsStructsArray[1].BottomRightBoundary.X,
			LevelDataCopy.FloorDataAsStruct.RoomDataAsStructsArray[1].TopRightBoundary.X);
			CorridorFirstHalfStartingPoint.Y = FMath::RandRange(LevelDataCopy.FloorDataAsStruct.RoomDataAsStructsArray[1].BottomRightBoundary.Y,
			LevelDataCopy.FloorDataAsStruct.RoomDataAsStructsArray[1].TopRightBoundary.Y);
			
			// RoomDataAsStructsArray[3] = Top-right Quadrant Room
			CorridorSecondHalfStartingPoint.X = FMath::RandRange(LevelDataCopy.FloorDataAsStruct.RoomDataAsStructsArray[3].BottomLeftBoundary.X,
			LevelDataCopy.FloorDataAsStruct.RoomDataAsStructsArray[3].TopLeftBoundary.X);
			CorridorSecondHalfStartingPoint.Y = FMath::RandRange(LevelDataCopy.FloorDataAsStruct.RoomDataAsStructsArray[3].BottomLeftBoundary.Y,
			LevelDataCopy.FloorDataAsStruct.RoomDataAsStructsArray[3].TopLeftBoundary.Y);
		} else if (CorridorCount == 2) {
			// RoomDataAsStructsArray[0] = Bottom-left Quadrant Room
			// Get a random integer for the Right.X coordinate from between the Top-Right.X and Top-Right.X coordinates.
			// The Top-Right.Y and Bottom-Right.Y coordinates are the same.
			CorridorFirstHalfStartingPoint.X = FMath::RandRange(LevelDataCopy.FloorDataAsStruct.RoomDataAsStructsArray[0].TopLeftBoundary.X,
			LevelDataCopy.FloorDataAsStruct.RoomDataAsStructsArray[0].TopRightBoundary.X);
			CorridorFirstHalfStartingPoint.Y = FMath::RandRange(LevelDataCopy.FloorDataAsStruct.RoomDataAsStructsArray[0].TopLeftBoundary.Y,
			LevelDataCopy.FloorDataAsStruct.RoomDataAsStructsArray[0].TopRightBoundary.Y);

			// RoomDataAsStructsArray[1] = Bottom-right Quadrant Room
			// Get a random integer for the Left.X coordinate from between the Bottom-Left.X and Bottom-Right.X coordinates.
			// The Bottom-Left.Y and Bottom-Right.X coordinates are the same.
			CorridorSecondHalfStartingPoint.X = FMath::RandRange(LevelDataCopy.FloorDataAsStruct.RoomDataAsStructsArray[1].BottomLeftBoundary.X,
			LevelDataCopy.FloorDataAsStruct.RoomDataAsStructsArray[1].BottomRightBoundary.X);
			CorridorSecondHalfStartingPoint.Y = FMath::RandRange(LevelDataCopy.FloorDataAsStruct.RoomDataAsStructsArray[1].BottomLeftBoundary.Y,
			LevelDataCopy.FloorDataAsStruct.RoomDataAsStructsArray[1].BottomRightBoundary.Y);
		} else if (CorridorCount == 3) {
			// RoomDataAsStructsArray[0] = Bottom-left Quadrant Room
			CorridorFirstHalfStartingPoint.X = FMath::RandRange(LevelDataCopy.FloorDataAsStruct.RoomDataAsStructsArray[0].BottomRightBoundary.X,
			LevelDataCopy.FloorDataAsStruct.RoomDataAsStructsArray[0].TopRightBoundary.X);
			CorridorFirstHalfStartingPoint.Y = FMath::RandRange(LevelDataCopy.FloorDataAsStruct.RoomDataAsStructsArray[0].BottomRightBoundary.Y,
			LevelDataCopy.FloorDataAsStruct.RoomDataAsStructsArray[0].TopRightBoundary.Y);
			
			// RoomDataAsStructsArray[2] = Top-left Quadrant Room
			CorridorSecondHalfStartingPoint.X = FMath::RandRange(LevelDataCopy.FloorDataAsStruct.RoomDataAsStructsArray[2].BottomLeftBoundary.X,
			LevelDataCopy.FloorDataAsStruct.RoomDataAsStructsArray[2].TopLeftBoundary.X);
			CorridorSecondHalfStartingPoint.Y = FMath::RandRange(LevelDataCopy.FloorDataAsStruct.RoomDataAsStructsArray[2].BottomLeftBoundary.Y,
			LevelDataCopy.FloorDataAsStruct.RoomDataAsStructsArray[2].TopLeftBoundary.Y);
		}

		DualLog("Corridor " + FString::FromInt(CorridorCount) + " first half starting point " +
			FString::FromInt(CorridorFirstHalfStartingPoint.X) + ", " +
			FString::FromInt(CorridorFirstHalfStartingPoint.Y), 4);

		DualLog("Corridor " + FString::FromInt(CorridorCount) + " second half starting point " +
			FString::FromInt(CorridorSecondHalfStartingPoint.X) + ", " +
			FString::FromInt(CorridorSecondHalfStartingPoint.Y), 4);

		// Calculate the distance between rooms.
		if (CorridorCount == 0 || CorridorCount == 2) {
			// Calculate the distance between rooms.
			// For the top and bottom corridors, use the Y axis first.
			
			// If the distance between rooms is zero, do nothing.
			// If the distance between rooms is one, just spawn a single tile in the corridor.
			// If the distance between rooms is two or more, spawn tiles alternatively between either side of the corridor
			// until they meet on one axis, then spawn tiles on the other axis until they meet properly and can be traversed.
			
			// Use absolute values when calculating distances to avoid adding complexity.
			YAxisDistanceBetweenRooms = abs(CorridorFirstHalfStartingPoint.Y - CorridorSecondHalfStartingPoint.Y) - 1;
			
			DualLog("Y-Axis distance between rooms: " + FString::FromInt(YAxisDistanceBetweenRooms), 4);

			// First half of the corridor generation:
			// Spawn two separate halves of the corridor that meet on one axis, but not both axes.
			if (YAxisDistanceBetweenRooms == 1) {
				// If the axis distance is 1, just add 1 set of coordinates to the corridor 
				// in order to spawn a single tile into the corridor.
				CorridorFirstHalfStartingPoint.Y++;
				LevelDataCopy.FloorDataAsStruct.CorridorDataAsStructsArray[CorridorCount].GridTileCoordinates.AddUnique(
					FIntVector2D(CorridorFirstHalfStartingPoint.X, CorridorFirstHalfStartingPoint.Y));
			} else if (YAxisDistanceBetweenRooms > 1) {
				// If the distance is greater than one, alternate between calculating the next set of coordinates starting
				// from the first half starting point and the second half starting point.
				while (YAxisDistanceBetweenRooms >= 0) {
					if (YAxisDistanceBetweenRooms % 2 == 0) {
						CorridorFirstHalfStartingPoint.Y++;
						LevelDataCopy.FloorDataAsStruct.CorridorDataAsStructsArray[CorridorCount].GridTileCoordinates.AddUnique(
							FIntVector2D(CorridorFirstHalfStartingPoint.X, CorridorFirstHalfStartingPoint.Y));
					} else {
						CorridorSecondHalfStartingPoint.Y--;
						LevelDataCopy.FloorDataAsStruct.CorridorDataAsStructsArray[CorridorCount].GridTileCoordinates.AddUnique(
							FIntVector2D(CorridorSecondHalfStartingPoint.X, CorridorSecondHalfStartingPoint.Y));
					}
					
					YAxisDistanceBetweenRooms--;
				}
			}

			// Second half of the corridor generation:
			// Spawn tiles along the other axis until the halves of the corridor fully meet.
			// Can't use the absolute value here because we need to know in which direction to spawn the tiles
			XAxisDistanceBetweenRooms = (CorridorFirstHalfStartingPoint.X - CorridorSecondHalfStartingPoint.X);

			// In order to get the true distance between corridors, we need to add 1 to the XAxisDistanceBetweenRooms
			// if the distance is a negative number. If its positive and non-zero, subtract 1.
			if (XAxisDistanceBetweenRooms < 0) {
				XAxisDistanceBetweenRooms++;
			} else if (XAxisDistanceBetweenRooms > 0) {
				XAxisDistanceBetweenRooms--;
			}

			// If the distance between rooms is 1 or -1, that means only one tile needs to spawned in the corridor.
			if (XAxisDistanceBetweenRooms == 1 || XAxisDistanceBetweenRooms == -1) {
				if (XAxisDistanceBetweenRooms == 1) {
					CorridorFirstHalfStartingPoint.X--;
				} else {
					CorridorFirstHalfStartingPoint.X++;
				}
				
				LevelDataCopy.FloorDataAsStruct.CorridorDataAsStructsArray[CorridorCount].GridTileCoordinates.AddUnique(
				FIntVector2D(CorridorFirstHalfStartingPoint.X, CorridorFirstHalfStartingPoint.Y));
			} else if (XAxisDistanceBetweenRooms > 1 || XAxisDistanceBetweenRooms < -1) {
				if (XAxisDistanceBetweenRooms > 1) {
					for (int XLoop = XAxisDistanceBetweenRooms; XLoop > 0; XLoop--) {
						CorridorFirstHalfStartingPoint.X--;
						
						LevelDataCopy.FloorDataAsStruct.CorridorDataAsStructsArray[CorridorCount].GridTileCoordinates.AddUnique(
						FIntVector2D(CorridorFirstHalfStartingPoint.X, CorridorFirstHalfStartingPoint.Y));
					}
				} else {
					for (int XLoop = XAxisDistanceBetweenRooms; XLoop < 0; XLoop++) {
						CorridorFirstHalfStartingPoint.X++;

						LevelDataCopy.FloorDataAsStruct.CorridorDataAsStructsArray[CorridorCount].GridTileCoordinates.AddUnique(
						FIntVector2D(CorridorFirstHalfStartingPoint.X, CorridorFirstHalfStartingPoint.Y));
					}
				}
			}
		} else if (CorridorCount == 1 || CorridorCount == 3) {
			// Calculate the distance between rooms.
			// For the left and right corridors, use the X axis first.
			
			// If the distance between rooms is zero, do nothing.
			// If the distance between rooms is one, just spawn a single tile in the corridor.
			// If the distance between rooms is two or more, spawn tiles alternatively between either side of the corridor
			// until they meet on one axis, then spawn tiles on the other axis until they meet properly and can be traversed.
			
			// Use absolute values when calculating distances to avoid adding complexity.
			XAxisDistanceBetweenRooms = abs(CorridorFirstHalfStartingPoint.X - CorridorSecondHalfStartingPoint.X) - 1;
			
			DualLog("X-Axis distance between rooms: " + FString::FromInt(XAxisDistanceBetweenRooms), 4);

			// First half of the corridor generation:
			// Spawn two separate halves of the corridor that meet on one axis, but not both axes.
			if (XAxisDistanceBetweenRooms == 1) {
				// If the axis distance is 1, just add 1 set of coordinates to the corridor 
				// in order to spawn a single tile into the corridor.
				CorridorFirstHalfStartingPoint.X++;
				LevelDataCopy.FloorDataAsStruct.CorridorDataAsStructsArray[CorridorCount].GridTileCoordinates.AddUnique(
					FIntVector2D(CorridorFirstHalfStartingPoint.X, CorridorFirstHalfStartingPoint.Y));
			} else if (XAxisDistanceBetweenRooms > 1) {
				// If the distance is greater than one, alternate between calculating the next set of coordinates starting
				// from the first half starting point and the second half starting point.
				while (XAxisDistanceBetweenRooms >= 0) {
					if (XAxisDistanceBetweenRooms % 2 == 0) {
						CorridorFirstHalfStartingPoint.X++;
						LevelDataCopy.FloorDataAsStruct.CorridorDataAsStructsArray[CorridorCount].GridTileCoordinates.AddUnique(
							FIntVector2D(CorridorFirstHalfStartingPoint.X, CorridorFirstHalfStartingPoint.Y));
					} else {
						CorridorSecondHalfStartingPoint.X--;
						LevelDataCopy.FloorDataAsStruct.CorridorDataAsStructsArray[CorridorCount].GridTileCoordinates.AddUnique(
							FIntVector2D(CorridorSecondHalfStartingPoint.X, CorridorSecondHalfStartingPoint.Y));
					}
					
					XAxisDistanceBetweenRooms--;
				}
			}

			// Second half of the corridor generation:
			// Spawn tiles along the other axis until the halves of the corridor fully meet.
			// Can't use the absolute value here because we need to know in which direction to spawn the tiles
			YAxisDistanceBetweenRooms = (CorridorFirstHalfStartingPoint.Y - CorridorSecondHalfStartingPoint.Y);

			// In order to get the true distance between corridors, we need to add 1 to the XAxisDistanceBetweenRooms
			// if the distance is a negative number. If its positive and non-zero, subtract 1.
			if (YAxisDistanceBetweenRooms < 0) {
				YAxisDistanceBetweenRooms++;
			} else if (YAxisDistanceBetweenRooms > 0) {
				YAxisDistanceBetweenRooms--;
			}

			// If the distance between rooms is 1 or -1, that means only one tile needs to spawned in the corridor.
			if (YAxisDistanceBetweenRooms == 1 || YAxisDistanceBetweenRooms == -1) {
				if (YAxisDistanceBetweenRooms == 1) {
					CorridorFirstHalfStartingPoint.Y--;
				} else {
					CorridorFirstHalfStartingPoint.Y++;
				}
				
				LevelDataCopy.FloorDataAsStruct.CorridorDataAsStructsArray[CorridorCount].GridTileCoordinates.AddUnique(
				FIntVector2D(CorridorFirstHalfStartingPoint.X, CorridorFirstHalfStartingPoint.Y));
			} else if (YAxisDistanceBetweenRooms > 1 || YAxisDistanceBetweenRooms < -1) {
				if (YAxisDistanceBetweenRooms > 1) {
					for (int YLoop = YAxisDistanceBetweenRooms; YLoop > 0; YLoop--) {
						CorridorFirstHalfStartingPoint.Y--;
						
						LevelDataCopy.FloorDataAsStruct.CorridorDataAsStructsArray[CorridorCount].GridTileCoordinates.AddUnique(
						FIntVector2D(CorridorFirstHalfStartingPoint.X, CorridorFirstHalfStartingPoint.Y));
					}
				} else {
					for (int YLoop = YAxisDistanceBetweenRooms; YLoop < 0; YLoop++) {
						CorridorFirstHalfStartingPoint.Y++;

						LevelDataCopy.FloorDataAsStruct.CorridorDataAsStructsArray[CorridorCount].GridTileCoordinates.AddUnique(
						FIntVector2D(CorridorFirstHalfStartingPoint.X, CorridorFirstHalfStartingPoint.Y));
					}
				}
			}
		}
			
		// For each set of coordinates in the corridor, spawn a GridTile actor there.
		for (FIntVector2D Coordinate : LevelDataCopy.FloorDataAsStruct.CorridorDataAsStructsArray[CorridorCount].GridTileCoordinates) {
			LevelDataCopy.FloorDataAsStruct.CorridorDataAsStructsArray[CorridorCount].GridTilesInCorridor.Add(GetWorld()->SpawnActor<AActorGridTile>(ActorGridTileBlueprintClass,
				FVector(Coordinate.X * 200, Coordinate.Y * 200, 0),
				FRotator::ZeroRotator,
				SpawnParameters));

			LevelDataCopy.FloorDataAsStruct.CorridorDataAsStructsArray[CorridorCount].GridTilesInCorridor.Last()->CorridorIndex = CorridorCount;
		}
	}
}


/** Long Road level layout:
Generates one long level that bends slightly. Either the the length should be the entire length of the level.
The width should be a few tiles. (4-5)

The stairs should always be spawned on the opposite side of the player.

Should occasionally have branching paths, with another stairs tile. But these paths should always lead to
something interesting in the next room.
*/
void ALostWorldGameModeBattle::GenerateLevelLayoutLongRoad()
{
}


void ALostWorldGameModeBattle::GetPlayerLocationAndRoom(FVector& PlayerLocation, int& RoomIndex) const
{
	TArray<AActor*> FoundGridTiles, FoundPlayers;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AActorGridTile::StaticClass(), FoundGridTiles);
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AActorEntityPlayer::StaticClass(), FoundPlayers);
	AActorEntityPlayer* Player = Cast<AActorEntityPlayer>(FoundPlayers[0]);

	PlayerLocation = Player->GetActorLocation();
	
	for (AActor* GridTile : FoundGridTiles) {
		if (GridTile->GetActorLocation().X == PlayerLocation.X && GridTile->GetActorLocation().Y == PlayerLocation.Y) {
			RoomIndex = Cast<AActorGridTile>(GridTile)->RoomIndex;
		}
	}
}
