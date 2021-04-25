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
enum class E_GridTile_OnPlayerEnterFunctions: uint8
{
	E_None,
	E_TriggerBattle
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

// ------------------------- Widget
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UWidgetComponent_MinimapRoom* MinimapRoomReference;

// ------------------------- Data
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	int X_Coordinate;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	int Y_Coordinate;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<F_LevelRoom_Encounter> EncountersList;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	E_GridTile_OnPlayerEnterFunctions OnPlayerEnterTileFunction;

// Functions
// --------------------------------------------------

// ------------------------- Mouse
	UFUNCTION(BlueprintCallable)
	void OnMouseBeginHover();

// ------------------------- Tile
	UFUNCTION()
	void OnPlayerEnterTile();
};
