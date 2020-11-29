#include "BaseClass_LevelController.h"


// Sets default values
ABaseClass_LevelController::ABaseClass_LevelController()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ABaseClass_LevelController::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABaseClass_LevelController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

