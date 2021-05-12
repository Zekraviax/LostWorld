#include "ItemFunctions_BaseClass.h"


#include "BaseClass_EntityInBattle.h"


// Sets default values
AItemFunctions_BaseClass::AItemFunctions_BaseClass()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

}

// Called when the game starts or when spawned
void AItemFunctions_BaseClass::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AItemFunctions_BaseClass::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


// ------------------------- Base Class Functions ------------------------- //
void AItemFunctions_BaseClass::RunItemAbilityFunction()
{

}


// ------------------------- Widget Functions ------------------------- //


// ------------------------- Triggered Functions ------------------------- //
void AItemFunctions_BaseClass::TriggeredFunction_OnItemEquipped(ABaseClass_EntityInBattle* EquippedEntity)
{

}


void AItemFunctions_BaseClass::TriggeredFunction_StarterOfWearerTurn(ABaseClass_EntityInBattle* EquippedEntity)
{

}