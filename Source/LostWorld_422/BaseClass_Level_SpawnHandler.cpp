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
ABaseClass_LevelRoom* ABaseClass_Level_SpawnHandler::SpawnNewRoom(TSubclassOf<ABaseClass_LevelRoom> RoomToSpawnClass, FVector WorldLocation, FRotator WorldRotation, E_Room_ExitDirections ExitDirection)
{
	FActorSpawnParameters SpawnParameters;
	SpawnParameters.bNoFail = true;
	SpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	if (GetWorld()) {
		Room_Reference = GetWorld()->SpawnActor<ABaseClass_LevelRoom>(RoomToSpawnClass, WorldLocation, WorldRotation, SpawnParameters);

		// Repeat the room spawn process
		Room_Reference->SpawnAdjacentRoom();
	}

	if (Room_Reference)
		return Room_Reference;
	else
		return NULL;
}