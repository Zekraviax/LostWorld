#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "BaseComponent_Room_Tile.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class LOSTWORLD_422_API UBaseComponent_Room_Tile : public USceneComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UBaseComponent_Room_Tile();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

// Base Variables
// --------------------------------------------------

// ------------------------- Tile Grid
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector2D GridCoordinates;
};
