#pragma once


#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Variables.h"
#include "ActorGridTile.generated.h"


class AActorEntityBase;


UCLASS()
class LOSTWORLD_API AActorGridTile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AActorGridTile();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	
// ---------------------------------------- Variables ---------------------------------------- //

// -------------------------------- Actor components
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* TileStaticMesh;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	UMaterialInstanceDynamic* DynamicMaterial;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	FLinearColor TileColour;

	
// -------------------------------- Variables
	// Keep track of what room or corridor this tile is in.
	// Use -1 for the CorridorIndex if the tile is in a room, and vice versa.
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	int RoomIndex = -1;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	int CorridorIndex = -1;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	FEncounter Encounter;


// ---------------------------------------- Functions ---------------------------------------- //
	void SetTileColour(FLinearColor NewColour);
	void MoveEntityToTile(AActorEntityBase* MovingEntity) const;

	// To-Do: Write a function that figures out whether or not an entity can be spawned on this tile.
	// Entities can not be spawned on a tile under the following conditions:
	// 1. There is already another entity on the tile (in-battle.)
	// 2. The tile has an encounter (out-of-battle, and encounter type doesn't matter.)
};
