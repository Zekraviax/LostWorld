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

	
// -------------------------------- Data
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
};
