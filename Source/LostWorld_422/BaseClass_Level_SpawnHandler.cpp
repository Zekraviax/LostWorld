#include "BaseClass_Level_SpawnHandler.h"

#include "EngineUtils.h"


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
ABaseClass_LevelRoom* ABaseClass_Level_SpawnHandler::SpawnNewRoom(TSubclassOf<ABaseClass_LevelRoom> RoomToSpawnClass, FVector WorldLocation, FRotator WorldRotation, ABaseClass_LevelRoom* PreviousRoomReference)
{
	FActorSpawnParameters SpawnParameters;
	SpawnParameters.bNoFail = true;
	SpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	if (GetWorld() && LevelData.CurrentRoomCount < LevelData.MaximumRoomCount) {
		Room_Reference = GetWorld()->SpawnActor<ABaseClass_LevelRoom>(RoomToSpawnClass, WorldLocation, WorldRotation, SpawnParameters);
		LevelData.CurrentRoomCount++;
	}

	if (Room_Reference)
		return Room_Reference;
	else
		return NULL;
}


void ABaseClass_Level_SpawnHandler::ProcessQueue()
{
	if (RoomSpawnQueue.Num() > 0 && LevelData.CurrentRoomCount <= LevelData.MaximumRoomCount) {
		//int LastIndex = RoomSpawnQueue.Num() - 1;
		ABaseClass_LevelRoom* LocalRoomRef;

		LevelData.CurrentRoomCount++;
		LocalRoomRef = RoomSpawnQueue[0];

		RoomSpawnQueue.RemoveAt(0);
		LocalRoomRef->SpawnAdjacentRoom();
	}
}