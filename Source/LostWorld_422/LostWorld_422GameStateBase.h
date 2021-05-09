#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"

#include "CardAbilityActor_BaseClass.h"
#include "CardAbilityActor_DrawCards.h"

#include "LostWorld_422GameStateBase.generated.h"

// Forward Declarations
class ABaseClass_EntityInBattle;
class ABaseClass_PlayerController;
class ALevel_SpawnTypeBase;


UCLASS()
class LOSTWORLD_422_API ALostWorld_422GameStateBase : public AGameStateBase
{
	GENERATED_BODY()
	
public:
// Base Variables
// --------------------------------------------------

// ------------------------- Technical Variables
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TArray<ABaseClass_EntityInBattle*> SortedTurnOrderList;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TArray<ABaseClass_EntityInBattle*> CurrentTurnOrderList;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TArray<FStackEntry> TheStack;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	float StackTimer;

	UPROPERTY()
	ABaseClass_PlayerController* PlayerControllerRef;

// ------------------------- Timers	
	UPROPERTY()
	FTimerHandle BeginTurnTimerHandle;

	UPROPERTY()
	FTimerHandle StackTimerHandle;

// ------------------------- Constructors
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<ABaseClass_EntityInBattle> EntityInBattle_Class;

	//UPROPERTY(EditAnywhere, BlueprintReadWrite)
	//TSubclassOf<ACardAbilityActor_DrawCards> DrawCards_Class;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	ACardAbilityActor_BaseClass* CardAbilityActor_Reference;

// ------------------------- Levels
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<TSubclassOf<ALevel_SpawnTypeBase>> LevelGenerators;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int CurrentFloorNumber;

// Functions
// --------------------------------------------------
	
// ------------------------- Level
	UFUNCTION()
	void RegenerateLevel();

// ------------------------- Battle
	UFUNCTION(BlueprintCallable)
	void DebugBattleStart(F_LevelRoom_Encounter Battle);

	UFUNCTION()
	void EntityEndOfTurn();

	UFUNCTION()
	void EntityBeginTurn_Delay();

	UFUNCTION()
	void NewCombatRound();

// ------------------------- Combat Functions
	UFUNCTION()
	void AddCardFunctionsToTheStack(FStackEntry StackEntry);

	UFUNCTION()
	void ExecuteCardFunctions();

// ------------------------- Events
	UFUNCTION()
	void Event_EntityDied(ABaseClass_EntityInBattle* DeadEntity);
};