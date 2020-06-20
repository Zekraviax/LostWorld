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
		//ProcessQueue();
	}

	if (Room_Reference)
		return Room_Reference;
	else
		return NULL;
}


void ABaseClass_Level_SpawnHandler::ProcessQueue()
{
	if (RoomSpawnQueue.Num() > 0 && LevelData.CurrentRoomCount <= LevelData.MaximumRoomCount) {
		RoomSpawnQueue[0]->SpawnAdjacentRoom();
		LevelData.CurrentRoomCount++;
		RoomSpawnQueue.RemoveAt(0);

		//ProcessQueue();
	}
	else if (RoomSpawnQueue.Num() <= 0 && LevelData.CurrentRoomCount <= LevelData.MaximumRoomCount) {
		for (TActorIterator<ABaseClass_LevelRoom> ActorItr(GetWorld()); ActorItr; ++ActorItr) {
			ABaseClass_LevelRoom* FoundRoom = *ActorItr;

			if (FoundRoom->ExitsList.Num() <= 0) {
				RoomSpawnQueue.Add(FoundRoom);
			}
		}

		//ProcessQueue();
	}
	else {
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Error?"));
		//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::White, FString::Printf(TEXT("RoomSpawnQueue Count: %s"), RoomSpawnQueue.Num()));
		//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::White, FString::Printf(TEXT("Current Room Count: %s"), LevelData.CurrentRoomCount));
		//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::White, FString::Printf(TEXT("RoomSpawnQueue Count: %s  /  Current Room Count: %s"), RoomSpawnQueue.Num(), LevelData.CurrentRoomCount));
	}

	//LevelData.CurrentRoomCount++;

	//for (int i = 0; i < RoomSpawnQueue.Num(); i++) {
	//	RoomSpawnQueue[i]->SpawnAdjacentRoom();
	//	RoomSpawnQueue.RemoveAt(0);
	//}
}