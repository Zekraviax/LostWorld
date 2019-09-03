// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"

#include "BaseClass_EntityInWorld.h"
#include "BaseClass_EntityInBattle.h"
#include "BaseClass_PlayerController.h"

#include "LostWorld_422GameStateBase.generated.h"

// Foward Declarations

UCLASS()
class LOSTWORLD_422_API ALostWorld_422GameStateBase : public AGameStateBase
{
	GENERATED_BODY()
	
public:
// Base Variables
// --------------------------------------------------

// ------------------------- Technical Variables
	UPROPERTY()
	TArray<ABaseClass_EntityInBattle*> SortedTurnOrderList;

	UPROPERTY()
	TArray<ABaseClass_EntityInBattle*> CurrentTurnOrderList;

	UPROPERTY()
	TArray<FStackEntry> TheStack;

// ------------------------- Technical Variables
	UPROPERTY()
	ABaseClass_PlayerController* PlayerControllerRef;

// ------------------------- Timers	
	UPROPERTY()
	FTimerHandle BeginTurnTimerHandle;

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
};