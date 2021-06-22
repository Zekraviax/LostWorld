#include "TraitsFunctions_BaseClass.h"


// Sets default values
ATraitsFunctions_BaseClass::ATraitsFunctions_BaseClass()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

}

// Called when the game starts or when spawned
void ATraitsFunctions_BaseClass::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATraitsFunctions_BaseClass::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


// ------------------------- Triggered Functions
void ATraitsFunctions_BaseClass::TriggeredFunction_StartOfBattle(ABaseClass_EntityInBattle* Entity)
{

}