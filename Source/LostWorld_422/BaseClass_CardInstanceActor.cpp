#include "BaseClass_CardInstanceActor.h"

//-------------------- Base Functions --------------------//
// Sets default values
ABaseClass_CardInstanceActor::ABaseClass_CardInstanceActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ABaseClass_CardInstanceActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABaseClass_CardInstanceActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

//-------------------- Card Instance --------------------//
void ABaseClass_CardInstanceActor::ExecuteCardAbility(FCardAbilitiesAndConditions AbilityAndConditions)
{

}

//-------------------- Card Functions --------------------//