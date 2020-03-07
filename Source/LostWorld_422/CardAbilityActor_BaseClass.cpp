#include "CardAbilityActor_BaseClass.h"


//-------------------- Base Functions --------------------//
// Sets default values
ACardAbilityActor_BaseClass::ACardAbilityActor_BaseClass()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

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

//-------------------- The Stack --------------------//
void ACardAbilityActor_BaseClass::CastCard(FCardBase Card)
{
	StackArray.Add(Card);
}

//-------------------- Ability Functions --------------------//
void ACardAbilityActor_BaseClass::SpawnCardAbilityActor(TSubclassOf<ACardAbilityActor_BaseClass> CardAbilityActor_Class)
{
	FActorSpawnParameters SpawnParameters;
	FVector WorldLocation = FVector(0, 0, 0);
	FRotator WorldRotation = FRotator(0, 0, 0);
	SpawnParameters.bNoFail = true;
	SpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	if (GetWorld()) {
		CardAbilityActor_Reference = GetWorld()->SpawnActor<ACardAbilityActor_BaseClass>(CardAbilityActor_Class, WorldLocation, WorldRotation, SpawnParameters);
	}
}

void ACardAbilityActor_BaseClass::RunCardAbilityFunction()
{

}