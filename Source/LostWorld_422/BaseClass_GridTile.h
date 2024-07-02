#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "LostWorld_422GameModeBase.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"

#include "BaseClass_GridTile.generated.h"

// Forward Declarations
class UWidgetComponent_MinimapRoom;


// Unique Enums
UENUM(BlueprintType)
enum class E_GridTile_OnPlayerEnterTileFunctions_Enum: uint8
{
	E_None,
	E_PlayerSpawn,
	E_TriggerBattle,
	E_Stairs
};


UCLASS()
class LOSTWORLD_422_API ABaseClass_GridTile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABaseClass_GridTile();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

// Base Variables
// --------------------------------------------------

// ------------------------- Components
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USceneComponent* PlayerRestPointReference;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* Tile;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	UMaterialInstanceDynamic* DynamicMaterial;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	FLinearColor BaseColour;

// ------------------------- Widget
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UWidgetComponent_MinimapRoom* MinimapRoomReference;

// ------------------------- Data
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	int X_Coordinate;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	int Y_Coordinate;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	ABaseClass_LevelRoom* RoomReference;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<F_LevelRoom_Encounter> EncountersList;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	E_GridTile_OnPlayerEnterTileFunctions_Enum OnPlayerEnterTileFunction;

// ------------------------- Widget
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	ABaseClass_EntityInBattle* OccupyingEntity;

// ------------------------- Timers	
	UPROPERTY()
	FTimerHandle TileFunctionsTimerHandle;

// Functions
// --------------------------------------------------

// ------------------------- Grid Tile
	UFUNCTION()
	void OnPlayerEnterTile(ABaseClass_PlayerController* PlayerControllerReference);

	UFUNCTION()
	void RunTileFunctions();
};
