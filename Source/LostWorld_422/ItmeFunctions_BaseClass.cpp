#include "ItmeFunctions_BaseClass.h"


// Sets default values
AItmeFunctions_BaseClass::AItmeFunctions_BaseClass()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

}

// Called when the game starts or when spawned
void AItmeFunctions_BaseClass::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AItmeFunctions_BaseClass::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}



// ------------------------- Base Class Functions ------------------------- //
void AItmeFunctions_BaseClass::RunItemAbilityFunction()
{

}


// ------------------------- Widget Functions ------------------------- //


// ------------------------- Triggered Functions ------------------------- //
void AItmeFunctions_BaseClass::TriggeredFunction_OnItemEquipped()
{

}


void AItmeFunctions_BaseClass::TriggeredFunction_StarterOfWearerTurn()
{

}