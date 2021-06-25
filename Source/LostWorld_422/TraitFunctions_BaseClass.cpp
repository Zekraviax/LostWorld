#include "TraitFunctions_BaseClass.h"


// Sets default values
ATraitFunctions_BaseClass::ATraitFunctions_BaseClass()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

}

// Called when the game starts or when spawned
void ATraitFunctions_BaseClass::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATraitFunctions_BaseClass::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


// ------------------------- Triggered Functions
void ATraitFunctions_BaseClass::TriggeredFunction_StartOfBattle(ABaseClass_EntityInBattle* Entity)
{

}