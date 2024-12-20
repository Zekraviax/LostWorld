#include "LostWorldGameModeBattle.h"


#include "ActorEntityEnemy.h"
#include "ActorEntityPlayer.h"
#include "ActorGridTile.h"
#include "AiBrainBase.h"
#include "FunctionLibraryCards.h"
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
	// Add the Battle UI to the players' HUD
	// Spawn enemy entities in to the level
	// Change the player's controls to Battle mode
	// Disable player movement

	// Get the Enemy data table row names from the Encounter data table.
	if (EncounterDataTable && EnemyDataTable) {
		FString ContextString;
		TArray<FName> EnemyRowNames = EnemyEncounter.EnemiesRowNames;
		TArray<AActorGridTile*> ValidEnemySpawnTiles;
		FVector PlayerEntityLocation = Cast<ALostWorldPlayerControllerBattle>(GetWorld()->GetFirstPlayerController())->
			ControlledPlayerEntity->GetActorLocation();
		
		// Clear the entities in battle array
		EntitiesInBattleArray.Empty();

		// Get all tiles within 2 tiles of the player that are empty.
		for (TObjectIterator<AActorGridTile> Itr; Itr; ++Itr) {
			AActorGridTile* FoundTile = *Itr;
			// First, check if the grid tile doesn't have any encounters or the encounter is an enemy encounter.
			if (FoundTile->Encounter.EncounterType == EEncounterTypes::Enemy ||
				FoundTile->Encounter.EncounterType == EEncounterTypes::None) {
				// Second, check if the tile is within 1-2 tiles of the player, and isn't 'behind' the player
				// because the UI might obscure the enemy.
				if (FoundTile->GetActorLocation().X >= PlayerEntityLocation.X - 200 && FoundTile->GetActorLocation().X <= PlayerEntityLocation.X + 400 &&
					(FoundTile->GetActorLocation().Y >= PlayerEntityLocation.Y - 200 && FoundTile->GetActorLocation().Y <= PlayerEntityLocation.Y + 400)) {
					// Third, make sure the tile isn't in a corridor.
					if (FoundTile->CorridorIndex == -1) {
						// Fourth, make sure the player isn't occupying the tile.
						if (FoundTile->GetActorLocation().X != PlayerEntityLocation.X && FoundTile->GetActorLocation().Y != PlayerEntityLocation.Y) {
							ValidEnemySpawnTiles.Add(FoundTile);
						}
					}
				}
			}
		}

		// Spawn enemies at random valid tiles
		// ReSharper disable once CppTooWideScope
		const FActorSpawnParameters SpawnParameters;
		for (int RowCount = 0; RowCount < EnemyRowNames.Num(); RowCount++) {
			AActorGridTile* RandomTile = ValidEnemySpawnTiles[FMath::RandRange(0, ValidEnemySpawnTiles.Num() -1)];

			EntitiesInBattleArray.Add(GetWorld()->SpawnActor<AActorEntityEnemy>(ActorEntityEnemyBlueprintClass,
				FVector(RandomTile->GetActorLocation().X, RandomTile->GetActorLocation().Y, 0),
				FRotator::ZeroRotator,
				SpawnParameters));
			
			// Attach an AI brain component
			Cast<AActorEntityEnemy>(EntitiesInBattleArray.Last())->CreateAiBrainComponent();

			ValidEnemySpawnTiles.Remove(RandomTile);

			// Assign the enemy's data to their actor.
			// Then get the entity's cards from the cards json and add them to their deck.
			FEnemyEntity* EnemyEntityData = EnemyDataTable->FindRow<FEnemyEntity>(EnemyRowNames[RowCount], ContextString);
			Cast<AActorEntityEnemy>(EntitiesInBattleArray.Last())->EnemyData = *EnemyEntityData;
			
			for (int CardCount = 0; CardCount < EnemyEntityData->EntityData.CardsInDeckRowNames.Num(); CardCount++) {
				FCard* InCard = CardsDataTable->FindRow<FCard>(EnemyEntityData->EntityData.CardsInDeckRowNames[CardCount], ContextString);
				Cast<AActorEntityEnemy>(EntitiesInBattleArray.Last())->AddCardToDeck(*InCard);
			}
		}

		// Reset all of the players' card arrays.
		Cast<ALostWorldPlayerControllerBattle>(GetWorld()->GetFirstPlayerController())->ControlledPlayerEntity->Hand.Empty();
		Cast<ALostWorldPlayerControllerBattle>(GetWorld()->GetFirstPlayerController())->ControlledPlayerEntity->Deck.Empty();
		Cast<ALostWorldPlayerControllerBattle>(GetWorld()->GetFirstPlayerController())->ControlledPlayerEntity->Discard.Empty();
		
		// The players' deck can be fetched from the GameInstance.
		TArray<FName> PlayerCardsInDeckRowNames = Cast<ULostWorldGameInstanceBase>(GetWorld()->GetGameInstance())->CurrentPlayerSave.EntityData.CardsInDeckRowNames;
		for (int CardCount = 0; CardCount < PlayerCardsInDeckRowNames.Num(); CardCount++) {
			FCard* InCard = CardsDataTable->FindRow<FCard>(PlayerCardsInDeckRowNames[CardCount], ContextString);
			Cast<ALostWorldPlayerControllerBattle>(GetWorld()->GetFirstPlayerController())->ControlledPlayerEntity->AddCardToDeck(*InCard);
		}

		// Add the player's entity to the array last.
		EntitiesInBattleArray.Add(Cast<ALostWorldPlayerControllerBattle>(GetWorld()->GetFirstPlayerController())->ControlledPlayerEntity);

		// Don't need to change the players' control mode here, because it will be set at the start of each turn.
		// Swap out the level exploration UI for the battle UI.
		// Make sure it's a "clean slate".
		Cast<ALostWorldPlayerControllerBattle>(GetWorld()->GetFirstPlayerController())->AddBattleHudToViewport();
		
		// Once everything is done, begin Turn Zero.
		PreBattleTurnZero(EnemyEncounter);
	}
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


// -------------------------------- Pre-battle 
void ALostWorldGameModeBattle::PreBattleTurnZero(const FEncounter& EnemyEncounter)
{
	// List of things that need to happen during 'Turn Zero':
	// Calculate the turn order.
	// Shuffle everyone's decks.
	// Each entity draws a hand of cards.
	
	// Lazy turn order calculation:
	// The player goes first.
	// then their allies, in whatever order the game finds them.
	// then the enemies, in whatever order the game finds them.

	// Calculate turn order.
	AddMaxNumberOfEntitiesToTurnQueue(true);

	// Shuffle up.
	for (auto& Entity : EntitiesInBattleArray) {
		if (Cast<AActorEntityEnemy>(Entity)) {
			Entity->Deck = Cast<AActorEntityEnemy>(Entity)->ShuffleDeck(Entity->Deck);
		} else if (Cast<AActorEntityPlayer>(Entity)) {
			Entity->Deck = Cast<AActorEntityPlayer>(Entity)->ShuffleDeck(Entity->Deck);
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
	for (AActorEntityBase* Entity : EntitiesInBattleArray) {
		Entity->ResetEntityBillboardPositionAndRotation();
		Cast<UWidgetEntityBillboard>(Entity->EntityBillboard->GetUserWidgetObject())->UpdateBillboard(Entity->EntityData);
	}

	// Begin the turn for the first entity in the turn array.
	if (Cast<AActorEntityEnemy>(TurnQueue[0])) {
		TurnQueue[0]->FindComponentByClass<UAiBrainBase>()->StartTurn();
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
	
	if (Cast<AActorEntityEnemy>(TurnQueue[0])) {
		Cast<AActorEntityEnemy>(TurnQueue[0])->StartTurn();
	} else if (Cast<AActorEntityPlayer>(TurnQueue[0])) {
		Cast<AActorEntityPlayer>(TurnQueue[0])->StartTurn();
	}
}


void ALostWorldGameModeBattle::DrawPhaseDrawCard()
{
	if (Cast<AActorEntityEnemy>(TurnQueue[0])) {
		Cast<AActorEntityEnemy>(TurnQueue[0])->DrawCard();
	} else if (Cast<AActorEntityPlayer>(TurnQueue[0])) {
		Cast<AActorEntityPlayer>(TurnQueue[0])->DrawCard();
	}
}


void ALostWorldGameModeBattle::AddMaxNumberOfEntitiesToTurnQueue(bool OverrideReadiness)
{
	// Each entity in battle has a 'readiness' value.
	// When an entity's readiness value reaches 1000, add it to the turn queue,
	// and reset the value.

	// To-Do: Reset the readiness value to a random integer between 0 and the entity's Agility.
	TArray<AActor*> ActorsInBattle;
	TArray<AActorEntityBase*> Entities;

	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AActorEntityBase::StaticClass(), ActorsInBattle);

	if (OverrideReadiness) {
		for (AActor* Actor : ActorsInBattle) {
			if (Cast<AActorEntityEnemy>(Actor)) {
				Cast<AActorEntityEnemy>(Actor)->EntityData.Stats.Readiness = FMath::RandRange(0, Cast<AActorEntityEnemy>(Actor)->EntityData.Stats.Agility);
				Entities.Add(Cast<AActorEntityEnemy>(Actor));
			} else if (Cast<AActorEntityPlayer>(Actor)) {
				Cast<AActorEntityPlayer>(Actor)->EntityData.Stats.Readiness = FMath::RandRange(0, Cast<AActorEntityPlayer>(Actor)->EntityData.Stats.Agility);
				Entities.Add(Cast<AActorEntityPlayer>(Actor));
			}
		}
	}

	int TurnQueueSize = TurnQueue.Num();

	for (int EntityCount = 0; EntityCount < 15 - TurnQueueSize; EntityCount++) {
		bool EntityHasReachedThreshold = false;

		while (!EntityHasReachedThreshold) {
			for (AActorEntityBase* Entity : Entities) {
				float EntityAgility = Entity->EntityData.Stats.Agility;
				// Declaring these floats here to avoid 'ambiguous call to overloaded function' errors.
				float IncrementMinimum = ((EntityAgility / 64) * 0.9) + 10;
				float IncrementMaximum = ((EntityAgility / 64) * 1.1) + 10;
				float ReadinessIncrement = FMath::RandRange(IncrementMinimum, IncrementMaximum);

				// To-Do: Clean up DualLog statements.
				//DualLog(FString::SanitizeFloat(IncrementMinimum) + " / " + FString::SanitizeFloat(IncrementMaximum));
				//DualLog(FString::SanitizeFloat(ReadinessIncrement) + + " - " + FString::SanitizeFloat(Entity->EntityData.Stats.Readiness));
				
				Entity->EntityData.Stats.Readiness += ReadinessIncrement;
				if (Entity->EntityData.Stats.Readiness >= 1000) {
					Entity->EntityData.Stats.Readiness -= 1000;
					EntityHasReachedThreshold = true;
					TurnQueue.Add(Entity);
				}
			}
		}
	}
}


// -------------------------------- Battle: Main Phase
void ALostWorldGameModeBattle::GetTargetsForCard(int CardIndexInHandArray)
{
	// Get a reference to the card in the player's hand.
	// Don't pass a copy of the FCard struct.
	// The stack entry will keep track of the target(s).
	FCard CardToCast = TurnQueue[0]->Hand[CardIndexInHandArray - 1];
	TArray<ECardFunctions> CardFunctions;
	CardToCast.FunctionsAndTargets.GetKeys(CardFunctions);

	// Rest the temp stack entry.
	TempStackEntry.Function = CardFunctions[0];
	TempStackEntry.TargetingMode = *CardToCast.FunctionsAndTargets.Find(CardFunctions[0]);
	TempStackEntry.Controller = TurnQueue[0];
	TempStackEntry.SelectedTargets.Empty();
	TempStackEntry.IndexInHandArray = CardIndexInHandArray;

	if (*CardToCast.FunctionsAndTargets.Find(CardFunctions[0]) == ECardTargets::OneEnemy) {
		Cast<ALostWorldPlayerControllerBattle>(UGameplayStatics::GetPlayerController(GetWorld(), 0))->
			SetControlMode(EPlayerControlModes::TargetSelectionSingleEntity);
		Cast<ALostWorldPlayerControllerBattle>(UGameplayStatics::GetPlayerController(GetWorld(), 0))->
			BattleHudWidget->PlayerStartCastingCard(CardToCast, TempStackEntry.Function, TempStackEntry.SelectedTargets.Num());
	} else if (*CardToCast.FunctionsAndTargets.Find(CardFunctions[0]) == ECardTargets::AllEnemies) {
		TArray<AActor*> FoundActors;
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), AActorEntityBase::StaticClass(), FoundActors);

		for (AActor* Actor : FoundActors) {
			if (Cast<AActorEntityBase>(Actor)) {
				TempStackEntry.SelectedTargets.Add(Cast<AActorEntityBase>(Actor));
			}
		}

		FinishedGettingTargetsForCard();
	}
}


void ALostWorldGameModeBattle::FinishedGettingTargetsForCard()
{
	// Pay the cost for casting the card.
	Cast<IInterfaceBattle>(TempStackEntry.Controller)->PayCostsForCard(TempStackEntry.IndexInHandArray);

	// To-Do: Replace all of these redundant casts to the actor, with casts to the interface.
	Cast<IInterfaceBattle>(TempStackEntry.Controller)->DiscardCard(TempStackEntry.IndexInHandArray);
	
	TheStack.Add(TempStackEntry);

	CastCard();
}


void ALostWorldGameModeBattle::CastCard()
{
	if (!FunctionLibraryCardsInstance) {
		FunctionLibraryCardsInstance = GetWorld()->SpawnActor<AFunctionLibraryCards>();
	}
	
	FunctionLibraryCardsInstance->ExecuteFunction(TheStack[0].Function);

	TheStack.RemoveAt(0);
}


// -------------------------------- Battle: Ending Phase
void ALostWorldGameModeBattle::EndOfTurn()
{
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
				AActorEntityPlayer* PlayerEntityReference = GetWorld()->SpawnActor<AActorEntityPlayer>(ActorEntityPlayerBlueprintClass,
				FVector(RandomGridTile->GetActorLocation().X, RandomGridTile->GetActorLocation().Y, 0),
				FRotator::ZeroRotator,
				SpawnParameters);

				// Set Camera Target.
				FViewTargetTransitionParams Params;
				GetWorld()->GetFirstPlayerController()->SetViewTarget(PlayerEntityReference, Params); // This line isn't multiplayer safe
				PlayerEntityReference->Camera->SetActive(true);

				// Add the level HUD to the player's screen.
				Cast<ALostWorldPlayerControllerBase>(GetWorld()->GetFirstPlayerController())->AddLevelHudToViewport();

				// Player data loading is handled in the GameInstanceBase.
				// Here, we just fetch it from the game instance.
				PlayerEntityReference->EntityData = Cast<ULostWorldGameInstanceBase>(GetWorld()->GetGameInstance())->CurrentPlayerSave.EntityData;

				// Players' first time billboard setup.
				Cast<UWidgetEntityBillboard>(PlayerEntityReference->EntityBillboard->GetUserWidgetObject())->UpdateBillboard(PlayerEntityReference->EntityData);
				PlayerEntityReference->ResetEntityBillboardPositionAndRotation();

				// Take control of the entity	
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
						RandomGridTile->Encounter = LevelDataCopy.Encounters[0];
						RandomGridTile->SetTileColour(FLinearColor(0.25f, 0.f, 0.f));
					}

					// Cap the number of encounters generated to be equal to the number of rooms in the level.
					ShuffledRoomIndicesArray.RemoveAt(0);
				}
			
				break;
			}
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
			FString::FromInt(LevelDataCopy.FloorDataAsStruct.RoomDataAsStructsArray[RoomCount].BottomLeftBoundary.Y), 5);
		DualLog("Room " + FString::FromInt(RoomCount) + " bottom right boundary: " +
			FString::FromInt(LevelDataCopy.FloorDataAsStruct.RoomDataAsStructsArray[RoomCount].BottomRightBoundary.X) + ", " +
			FString::FromInt(LevelDataCopy.FloorDataAsStruct.RoomDataAsStructsArray[RoomCount].BottomRightBoundary.Y), 5);
		DualLog("Room " + FString::FromInt(RoomCount) + " top left boundary: " +
			FString::FromInt(LevelDataCopy.FloorDataAsStruct.RoomDataAsStructsArray[RoomCount].TopLeftBoundary.X) + ", " +
			FString::FromInt(LevelDataCopy.FloorDataAsStruct.RoomDataAsStructsArray[RoomCount].TopLeftBoundary.Y), 5);
		DualLog("Room " + FString::FromInt(RoomCount) + " top right boundary: " +
			FString::FromInt(LevelDataCopy.FloorDataAsStruct.RoomDataAsStructsArray[RoomCount].TopRightBoundary.X) + ", " +
			FString::FromInt(LevelDataCopy.FloorDataAsStruct.RoomDataAsStructsArray[RoomCount].TopRightBoundary.Y), 5);

		// For each valid coordinate in each room, spawn a GridTile actor at those coordinates.
		for (int LengthCount = LevelDataCopy.FloorDataAsStruct.RoomDataAsStructsArray[RoomCount].BottomLeftBoundary.X;
			LengthCount <= LevelDataCopy.FloorDataAsStruct.RoomDataAsStructsArray[RoomCount].TopRightBoundary.X;
			LengthCount++) {
			for (int WidthCount = LevelDataCopy.FloorDataAsStruct.RoomDataAsStructsArray[RoomCount].BottomLeftBoundary.Y;
				WidthCount <= LevelDataCopy.FloorDataAsStruct.RoomDataAsStructsArray[RoomCount].TopRightBoundary.Y;
				WidthCount++) {
				
				LevelDataCopy.FloorDataAsStruct.RoomDataAsStructsArray[RoomCount].GridTilesInRoom.Add(
					GetWorld()->SpawnActor<AActorGridTile>(ActorGridTileBlueprintClass,
					FVector(LengthCount * 200, WidthCount * 200, 0),
					FRotator::ZeroRotator,
					SpawnParameters));
				
				// Assign variables to the tile here.
				LevelDataCopy.FloorDataAsStruct.RoomDataAsStructsArray[RoomCount].GridTilesInRoom.Last()->RoomIndex = RoomCount;
				
			}
		}
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
			FString::FromInt(CorridorFirstHalfStartingPoint.Y), 5);

		DualLog("Corridor " + FString::FromInt(CorridorCount) + " second half starting point " +
			FString::FromInt(CorridorSecondHalfStartingPoint.X) + ", " +
			FString::FromInt(CorridorSecondHalfStartingPoint.Y), 5);

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
			
			// DualLog("Y-Axis distance between rooms: " + FString::FromInt(YAxisDistanceBetweenRooms));

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
			
			// DualLog("X-Axis distance between rooms: " + FString::FromInt(XAxisDistanceBetweenRooms));

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