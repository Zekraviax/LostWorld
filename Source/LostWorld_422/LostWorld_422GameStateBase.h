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
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Technical")
	TArray<ABaseClass_EntityInBattle*> SortedTurnOrderList;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Technical")
	TArray<ABaseClass_EntityInBattle*> CurrentTurnOrderList;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Technical")
	ABaseClass_PlayerController* PlayerControllerRef;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Technical")
	TArray<FStackEntry> TheStack;

	UFUNCTION(BlueprintCallable)
	void DebugBattleStart();

	UFUNCTION()
	void EntityEndOfTurn();

	UFUNCTION()
	void NewCombatRound();
};