#include "CardAbilityActor_BaseClass.h"


//-------------------- Base Functions --------------------//
// Sets default values
ACardAbilityActor_BaseClass::ACardAbilityActor_BaseClass()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

}

// Called when the game starts or when spawned
void ACardAbilityActor_BaseClass::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACardAbilityActor_BaseClass::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}


// ------------------------- Base Class Functions ------------------------- //
void ACardAbilityActor_BaseClass::RunCardAbilityFunction(FStackEntry StackEntry)
{
}


// ------------------------- Widget Functions ------------------------- //
void ACardAbilityActor_BaseClass::WidgetFunction_SpendMana(int ManaSpent, FStackEntry StackEntry)
{
}


// ------------------------- Technical Functions
AActor* ACardAbilityActor_BaseClass::TechnicalFunction_SimpleGetTarget()
{
	return nullptr;
}