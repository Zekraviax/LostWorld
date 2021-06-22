#include "StatusFunctions_BaseClass.h"


// Sets default values
AStatusFunctions_BaseClass::AStatusFunctions_BaseClass()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

}

// Called when the game starts or when spawned
void AStatusFunctions_BaseClass::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AStatusFunctions_BaseClass::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


// ------------------------- Passive Functions
void AStatusFunctions_BaseClass::PassiveFunction_OnStatusEffectBegin(ABaseClass_EntityInBattle* AffectedEntity)
{

}


void AStatusFunctions_BaseClass::PassiveFunction_OnStatusEffectEnd(ABaseClass_EntityInBattle* AffectedEntity)
{

}


// ------------------------- Triggered Functions
void AStatusFunctions_BaseClass::TriggeredFunction_StartOfEntityTurn(ABaseClass_EntityInBattle* AffectedEntity)
{

}


int AStatusFunctions_BaseClass::TriggeredFunction_EntityAboutToTakeDamage(ABaseClass_EntityInBattle* AffectedEntity, int IncomingDamage)
{
	return 0;
}