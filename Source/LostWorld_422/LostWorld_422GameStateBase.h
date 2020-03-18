#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"

#include "CardAbilityActor_BaseClass.h"
#include "CardAbilityActor_DrawCards.h"

#include "LostWorld_422GameStateBase.generated.h"

// Forward Declarations
class ABaseClass_EntityInBattle;
class ABaseClass_PlayerController;


UCLASS()
class LOSTWORLD_422_API ALostWorld_422GameStateBase : public AGameStateBase
{
	GENERATED_BODY()
	
public:
// Initializers
// --------------------------------------------------
	//ALostWorld_422GameStateBase();


// Base Variables
// --------------------------------------------------

// ------------------------- Technical Variables
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Technical")
	TArray<ABaseClass_EntityInBattle*> SortedTurnOrderList;

	UPROPERTY()
	TArray<ABaseClass_EntityInBattle*> CurrentTurnOrderList;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Technical")
	TArray<FCardBase> TheStack;

	UPROPERTY()
	ABaseClass_PlayerController* PlayerControllerRef;

// ------------------------- Timers	
	UPROPERTY()
	FTimerHandle BeginTurnTimerHandle;

	UPROPERTY()
	FTimerHandle StackTimerHandle;

// ------------------------- Constructors
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Constructors")
	TSubclassOf<ACardAbilityActor_DrawCards> DrawCards_Class;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Constructors")
	ACardAbilityActor_BaseClass* CardAbilityActor_Reference;

// Functions
// --------------------------------------------------

// ------------------------- Battle
	UFUNCTION(BlueprintCallable)
	void DebugBattleStart();

	UFUNCTION()
	void EntityEndOfTurn();

	UFUNCTION()
	void EntityBeginTurn_Delay();

	UFUNCTION()
	void NewCombatRound();

// ------------------------- Combat Functions
	UFUNCTION()
	void AddCardFunctionsToTheStack(FCardBase Card);

	UFUNCTION()
	void ExecuteCardFunctions();

// ------------------------- Events
	UFUNCTION()
	void Event_EntityDied(ABaseClass_EntityInBattle* DeadEntity);
};