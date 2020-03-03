// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"

#include "LostWorld_422GameInstanceBase.generated.h"

// Forward Declarations
class ABaseClass_LevelRoom;

UCLASS()
class LOSTWORLD_422_API ULostWorld_422GameInstanceBase : public UGameInstance
{
	GENERATED_BODY()

public:
// Initializer
// --------------------------------------------------
	//ULostWorld_422GameInstanceBase(const FObjectInitializer& ObjectInitializer);

// Base Variables
// --------------------------------------------------

// ------------------------- Constructors
	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Constructors")
	//TSubclassOf<ABaseClass_LevelRoom> StartingRoom_Class;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Constructors")
	TSubclassOf<ABaseClass_LevelRoom> TestOne_Room_Class;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Constructors")
	ABaseClass_LevelRoom* Room_Reference;

// ------------------------- Rooms
	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Constructors")
	//TArray<TSubclassOf<ABaseClass_LevelRoom>> RoomClassesArray;

// Functions
// --------------------------------------------------
	UFUNCTION()
	void SpawnNewRoom(TSubclassOf<ABaseClass_LevelRoom> RoomToSpawnClass, FVector WorldLocation, FRotator WorldRotation);
};
