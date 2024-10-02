#pragma once


#include "CoreMinimal.h"
#include "LostWorldGameModeBase.h"
#include "Variables.h"
#include "LostWorldGameModeBattle.generated.h"


// Forward declarations
class AActorGridTile;
class USaveGameLevelData;


UCLASS()
class LOSTWORLD_API ALostWorldGameModeBattle : public ALostWorldGameModeBase
{
	GENERATED_BODY()

public:
	// ---------------------------------------- Variables ---------------------------------------- //
	// Keep a reference to the SaveGame so it only needs to be spawned once per level.
	// Shouldn't be kept alive for an entire play session because players might visit
	// multiple levels in a single session.
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	USaveGameLevelData* LevelDataSaveGameReference;

	// This is the temporary copy of the level data JSON.
	// Variables rolled during level generated will be stored in this copy of the JSON-as-Struct variable.
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	FLevelDataAsStruct LevelDataCopy;

	// Must be assigned in the editor first.
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<AActorGridTile> ActorGridTileBlueprintClass;

	// ---------------------------------------- Functions ---------------------------------------- //
	// The GameModeBattle will handle battle functionality, such as dealing damage and spending mana.
		// It will also handle as much input as possible:
			// For example, the player tells the game mode when they want to play a card,
			// and the game mode will handle the rest.
		// The GameModeBattle will also handle level generation since the game will transition seamlessly,
		// between level exploration and battles.

	
	// Structure of a Battle:
		// Pre-Battle functions:
			// Shuffle each Entity's decks.
			// Each entity draws a starting hand of cards (defaults to 7 cards.)
			// Calculate the turn order based on all Entity's speed stats.
			// Whichever Entity is first in the turn order starts their turn.
		// Post-Battle functions:
			// Clean up all Actors that were spawned.
			// Reward the player with the spoils of their battle.
	
	void PreBattleShuffleDecks();

	
	// Structure of a Turn:
		// Beginning phase:
			// Effects that trigger at the start of a turn trigger here, first.
			// Effects that last until the start of the turn are cleaned up here, second.
		// Draw phase:
			// Entity draws a card.
		// Main phase:
			// Entity can play cards and take special actions like consuming items.
		// Ending phase:
			// Effects that trigger at the end of a turn trigger here, first.
			// Effects that last until the end of the turn are cleaned up here, second.

	
	// Level Generation:
		// First, the game mode needs to know the dimensions of a level in Tiles.
		// The north-south dimension will be called 'Length' and 'X'.
		// The east-west dimension will be called 'Width' and 'Y'.

		// 2024/10/01 Addendum:
		// In Unreal Engine 4, the X axis runs top-bottom from a birds-eye view of the level
		// The Y axis runs left-right.
		// And the Z axis is up-down.

	// Step Zero: Get the level JSON.
	UFUNCTION(BlueprintCallable)
	void LoadLevelData();

	// From Step One, each level Layout will have their own function.
	void GenerateLevelLayoutFourSquares();
};
