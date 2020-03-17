#include "BaseClass_Level_SpawnHandler.h"


//-------------------- Base --------------------//
// Sets default values
ABaseClass_Level_SpawnHandler::ABaseClass_Level_SpawnHandler()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ABaseClass_Level_SpawnHandler::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABaseClass_Level_SpawnHandler::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

//-------------------- Spawn Rooms --------------------//
void ABaseClass_Level_SpawnHandler::SpawnNewRoom(TSubclassOf<ABaseClass_LevelRoom> RoomToSpawnClass, FVector WorldLocation, FRotator WorldRotation)
{
	FActorSpawnParameters SpawnParameters;
	SpawnParameters.bNoFail = true;
	SpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	if (GetWorld()) {
		Room_Reference = GetWorld()->SpawnActor<ABaseClass_LevelRoom>(TestOne_Room_Class, WorldLocation, WorldRotation, SpawnParameters);
	}
}