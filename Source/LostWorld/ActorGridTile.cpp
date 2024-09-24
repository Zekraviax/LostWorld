#include "ActorGridTile.h"


// Sets default values
AActorGridTile::AActorGridTile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

}

// Called when the game starts or when spawned
void AActorGridTile::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AActorGridTile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

