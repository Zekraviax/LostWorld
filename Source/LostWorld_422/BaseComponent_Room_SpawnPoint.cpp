#include "BaseComponent_Room_SpawnPoint.h"


// Sets default values for this component's properties
UBaseComponent_Room_SpawnPoint::UBaseComponent_Room_SpawnPoint()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}


// Called when the game starts
void UBaseComponent_Room_SpawnPoint::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UBaseComponent_Room_SpawnPoint::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

