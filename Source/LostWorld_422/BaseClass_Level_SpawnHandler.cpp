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

	//if (GetWorld() && LevelData.CurrentRoomCount < LevelData.MaximumRoomCount) {
		Room_Reference = GetWorld()->SpawnActor<ABaseClass_LevelRoom>(RoomToSpawnClass, WorldLocation, WorldRotation, SpawnParameters);
		LevelData.CurrentRoomCount++;
	//}

	if (Room_Reference)
		return Room_Reference;
	else
		return NULL;
}


void ABaseClass_Level_SpawnHandler::ProcessQueue()
{
	if (RoomSpawnQueue.Num() > 0 && LevelData.CurrentRoomCount < LevelData.MaximumRoomCount) {
		//int LastIndex = RoomSpawnQueue.Num() - 1;
		ABaseClass_LevelRoom* LocalRoomRef;

		//LevelData.CurrentRoomCount++;
		LocalRoomRef = RoomSpawnQueue[0];

		RoomSpawnQueue.RemoveAt(0);
		LocalRoomRef->SpawnAdjacentRoom();
	}
	// If the maximum room count has been reached, find a place for an exit.
	else if (LevelData.CurrentRoomCount >= LevelData.MaximumRoomCount && !HasExitSpawned) {
		TArray<ABaseClass_LevelRoom*> NoAdjacentRoomsArray;
		ABaseClass_LevelRoom* ChosenExitSpawnRoom;
		TArray<UBaseComponent_Room_SpawnPoint*> ExitSpawnPointsArray;
		UBaseComponent_Room_SpawnPoint* ChosenExitSpawnPoint;

		if (RoomSpawnQueue.Num() > 0)
			RoomSpawnQueue.Empty();

		HasExitSpawned = true;
		//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::White, FString::Printf(TEXT("Spawn Exit Room.")));

		// Find all possible places for the exit.
		for (TActorIterator<ABaseClass_LevelRoom> ActorItr(GetWorld()); ActorItr; ++ActorItr) {
			ABaseClass_LevelRoom* FoundRoom = *ActorItr;

			if (FoundRoom->ExitsList.Num() <= 0) {
				NoAdjacentRoomsArray.Add(FoundRoom);
			}
		}

		// Get all the room's possible exit location spawn components
		ChosenExitSpawnRoom = NoAdjacentRoomsArray[FMath::RandRange(0, NoAdjacentRoomsArray.Num() - 1)];
		ChosenExitSpawnRoom->GetComponents<UBaseComponent_Room_SpawnPoint>(ExitSpawnPointsArray);
		ChosenExitSpawnPoint = ExitSpawnPointsArray[FMath::RandRange(0, ExitSpawnPointsArray.Num() - 1)];

		ChosenExitSpawnPoint->ValidRoomTypes.Empty();
		ChosenExitSpawnPoint->ValidRoomTypes.Add(Exit_Room_Classes[FMath::RandRange(0, Exit_Room_Classes.Num() - 1)]);
		GEngine->AddOnScreenDebugMessage(-1, 15.f, FColor::Purple, FString::Printf(TEXT("Spawn Exit Room")));
		ChosenExitSpawnRoom->SpawnAdjacentRoom();
	}
}