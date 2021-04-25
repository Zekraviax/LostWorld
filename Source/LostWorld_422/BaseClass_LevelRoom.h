#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "LostWorld_422GameModeBase.h"
#include "BaseClass_GridTile.h"
#include "BaseComponent_Room_Tile.h"
#include "BaseComponent_Room_SpawnPoint.h"
#include "WidgetComponent_RoomEncounter.h"
#include "WidgetComponent_RoomExit.h"
#include "Lostworld_422GameInstanceBase.h"

#include "BaseClass_LevelRoom.generated.h"

// Forward Declarations
class ABaseClass_Level_SpawnHandler;


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
	//UPROPERTY(EditAnywhere, BlueprintReadWrite)
	//F_LevelRoom_Encounter CurrentEncounterData;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<F_LevelRoom_Encounter> EncountersList;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<F_LevelRoom_Exit> ExitsList;

	// Previous room exit
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	F_LevelRoom_Exit PreviousRoomExit;


// ------------------------- Components
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TArray<UBaseComponent_Room_Tile*> SceneCoordinateComponents;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TArray<UBaseComponent_Room_SpawnPoint*> RoomSpawnSceneComponents;

// ------------------------- Constructor Classes (?)
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<ABaseClass_EntityInBattle> EntityInBattle_Class;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	ABaseClass_EntityInBattle* EntityInBattle_Reference;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<UWidgetComponent_RoomEncounter> RoomEncounter_Class;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UWidgetComponent_RoomEncounter* RoomEncounter_Widget;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<UWidgetComponent_RoomExit> RoomExit_Class;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UWidgetComponent_RoomExit* RoomExit_Widget;


// Functions
// --------------------------------------------------

// ------------------------- Setup
	UFUNCTION(BlueprintCallable)
	void SpawnAdjacentRoom();

	UFUNCTION()
	void SpawnEnemyFormation(F_LevelRoom_EnemyFormation EnemyFormation);

	UFUNCTION(BlueprintCallable)
	void PlayerEnterRoom();
};