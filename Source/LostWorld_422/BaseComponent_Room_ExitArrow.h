#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "BaseComponent_Room_ExitArrow.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class LOSTWORLD_422_API UBaseComponent_Room_ExitArrow : public USceneComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UBaseComponent_Room_ExitArrow();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

// Base Variables
// --------------------------------------------------

// ------------------------- Arrow
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	bool IsExitLocked;
};
