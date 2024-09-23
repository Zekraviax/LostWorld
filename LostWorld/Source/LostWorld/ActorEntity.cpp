#include "ActorEntity.h"


// Sets default values
AActorEntity::AActorEntity()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AActorEntity::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AActorEntity::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

