#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "BaseComponent_Room_SpawnPoint.generated.h"

// Forward Declarations
class ABaseClass_LevelRoom;


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class LOSTWORLD_422_API UBaseComponent_Room_SpawnPoint : public USceneComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UBaseComponent_Room_SpawnPoint();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

// Base Variables
// --------------------------------------------------

// ------------------------- Rooms
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Rooms")
	TArray<TSubclassOf<ABaseClass_LevelRoom>> ValidRoomTypes;
};
