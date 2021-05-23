#include "BattleTracker_BaseClass.h"


// Sets default values for this component's properties
UBattleTracker_BaseClass::UBattleTracker_BaseClass()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;
}


// Called when the game starts
void UBattleTracker_BaseClass::BeginPlay()
{
	Super::BeginPlay();
}


// Called every frame
void UBattleTracker_BaseClass::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}