#pragma once


#include "CoreMinimal.h"
#include "LostWorldGameModeBase.h"
#include "Variables.h"
#include "LostWorldGameModeBattle.generated.h"


// Forward declarations
class AActorEntityBase;
class AActorEntityPlayer;
class AActorGridTile;
class AFunctionLibraryCards;
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

	// TSharedPtrs can't have UPROPERTYs.
	TSharedPtr<FJsonObject> LevelDataAsJson;
	
	// This is the temporary copy of the level data JSON.
	// Variables rolled during level generated will be stored in this copy of the JSON-as-Struct variable.
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	FLevelDataAsStruct LevelDataCopy;

	// We're adding all the entites in a battle into an array, just in case there
	// are other entities on the floor that aren't in the battle.
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TArray<AActorEntityBase*> EntitiesInBattleArray;

	// Each entity in turn queue. (CTB style)
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TArray<AActorEntityBase*> TurnQueue;

	// Counts every spell cast by every entity.
	// Resets at the start of every entity's turn.
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	int CardsCastThisTurn;

	// Temporary stack entry used only for getting the targets
	// before being added to the stack properly.
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	FStackEntry TempStackEntry;

	// Cards with multiple functions should add each function to the stack
	// as a separate item in the array.
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TArray<FStackEntry> TheStack;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	AFunctionLibraryCards* FunctionLibraryCardsInstance;
	
	// Must be assigned in the editor first.
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<AActorGridTile> ActorGridTileBlueprintClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<AActorEntityPlayer> ActorEntityPlayerBlueprintClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<AActorEntityBase> ActorEntityEnemyBlueprintClass;


// ---------------------------------------- Functions ---------------------------------------- //
	// The GameModeBattle will handle battle functionality, such as dealing damage and spending mana.
		// It will also handle as much input as possible:
			// For example, the player tells the game mode when they want to play a card,
			// and the game mode will handle the rest.
		// The GameModeBattle will also handle level generation since the game will transition seamlessly,
		// between level exploration and battles.

	// This transition will handle the technical things.
	void TransitionToBattle(const FEncounter& EnemyEncounter);
	// Check if either the player, or all enemies, have been wiped out.
	void EndOfBattleCheck() const;
	void PlayerVictory() const;

	// The SpawnEntity function can serve the dual purposes of initializing a battle,
	// and spawning Summons mid-battle.
	// To-Do: Finish testing this function, and incorporate it into the TransitionToBattle function.
	void SpawnEntity(FEntity InEntity);
	
	// Structure of a Battle:
		// Pre-Battle functions:
			// Shuffle each Entity's decks.
			// Each entity draws a starting hand of cards (defaults to 7 cards.)
			// Calculate the turn order based on all Entity's speed stats.
			// Whichever Entity is first in the turn order starts their turn.
		// Post-Battle functions:
			// Clean up all Actors that were spawned.
			// Reward the player with the spoils of their battle.

	// This function will handle all of the functions that occur at the start of the battle
	// that can also happen during battle e.g. drawing cards.
	void PreBattleTurnZero(const FEncounter& EnemyEncounter);
	void AddMaxNumberOfEntitiesToTurnQueue(bool OverrideReadiness);

	
	// Structure of a Turn:
		// Starting phase:
			// Effects that trigger at the start of a turn trigger here, first.
			// Effects that last until the start of the turn are cleaned up here, second.
	void StartOfTurn();
		// Draw phase:
			// Entity draws a card.
	void DrawPhaseDrawCard();
		// Main phase:
			// Entity can play cards and take special actions like consuming items.
	void GetTargetsForCard(int CardIndexInHandArray);
	void FinishedGettingTargetsForCard();
	void CastCard();
		// Ending phase:
			// Effects that trigger at the end of a turn trigger here, first.
			// Effects that last until the end of the turn are cleaned up here, second.
	void EndOfTurn();

	
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
	void GenerateLevelAndSpawnEverything();

	// From Step One, each level Layout will have their own function.
	void GenerateLevelLayoutFourSquares();

	
// -------------------------------- Other functions
	void GetPlayerLocationAndRoom(FVector& PlayerLocation, int& RoomIndex) const;
};
