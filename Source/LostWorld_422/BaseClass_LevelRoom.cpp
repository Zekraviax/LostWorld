#include "BaseClass_LevelRoom.h"

#include "BaseClass_PlayerController.h"


// ------------------------- Initializer
// Sets default values
ABaseClass_LevelRoom::ABaseClass_LevelRoom()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
}

// Called when the game starts or when spawned
void ABaseClass_LevelRoom::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ABaseClass_LevelRoom::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}