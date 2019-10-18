// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "LostWorld_422GameModeBase.h"
#include "BaseClass_GridTile.h"
#include "BaseClass_EntityInWorld.h"
#include "BaseComponent_Room_Tile.h"

#include "BaseClass_LevelRoom.generated.h"

UCLASS()
class LOSTWORLD_422_API ABaseClass_LevelRoom : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABaseClass_LevelRoom();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;


// Base Variables
// --------------------------------------------------

// ------------------------- Room
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Room")
	F_Level_Room RoomData;

// ------------------------- Tile Grid
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Tile Grid")
	TArray<UBaseComponent_Room_Tile*> SceneCoordinateComponents;

// ------------------------- Entity
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Entity")
	TSubclassOf<ABaseClass_EntityInBattle> EntityInBattle_Class;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Entity")
	ABaseClass_EntityInBattle* EntityInBattle_Reference;


// Functions
// --------------------------------------------------

// ------------------------- Setup
	UFUNCTION()
	void SpawnEnemyFormation();
};