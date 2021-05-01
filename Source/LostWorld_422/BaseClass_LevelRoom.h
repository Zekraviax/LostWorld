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
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<F_LevelRoom_Encounter> EncountersList;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TArray<ABaseClass_GridTile*> GridTilesInRoom;

// ------------------------- Components
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TArray<UBaseComponent_Room_Tile*> SceneCoordinateComponents;

// ------------------------- Constructors
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<ABaseClass_EntityInBattle> EntityInBattle_Class;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	ABaseClass_EntityInBattle* EntityInBattle_Reference;


// Functions
// --------------------------------------------------

};