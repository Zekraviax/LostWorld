#include "BaseComponent_Room_ExitArrow.h"


// Sets default values for this component's properties
UBaseComponent_Room_ExitArrow::UBaseComponent_Room_ExitArrow()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
	IsExitLocked = false;

	
}


// Called when the game starts
void UBaseComponent_Room_ExitArrow::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UBaseComponent_Room_ExitArrow::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

