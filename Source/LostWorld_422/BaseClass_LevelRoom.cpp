#include "BaseClass_LevelRoom.h"

#include "BaseClass_PlayerController.h"
#include "BaseClass_Level_SpawnHandler.h"


// ------------------------- Initializer
// Sets default values
ABaseClass_LevelRoom::ABaseClass_LevelRoom()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	// Construct EntityInBattle
	static ConstructorHelpers::FObjectFinder<UBlueprint> EntityInBattle_BlueprintConstruct(TEXT("Blueprint'/Game/Blueprint_EntityInBattle.Blueprint_EntityInBattle'"));

	if (EntityInBattle_BlueprintConstruct.Object) {
		EntityInBattle_Class = (UClass*)EntityInBattle_BlueprintConstruct.Object->GeneratedClass;
	}

	// Set Default Room Exit Direction
	//PreviousRoomExitDirection = E_Room_ExitDirections::E_None;
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

// ------------------------- Setup
void ABaseClass_LevelRoom::SpawnAdjacentRoom()
{
	FName Name;
	FVector Location;
	FRotator Rotation;
	ABaseClass_Level_SpawnHandler* RoomSpawner = nullptr;

	this->GetComponents<UBaseComponent_Room_SpawnPoint>(RoomSpawnSceneComponents);

	// Find the level's Room SpawnHandler
	for (TActorIterator<ABaseClass_Level_SpawnHandler> Itr(GetWorld()); Itr; ++Itr) {
		RoomSpawner = *Itr;
	}

	if (RoomSpawner && RoomSpawnSceneComponents.Num() > 0) {
		F_LevelRoom_Exit NewExit;
		ABaseClass_PlayerController* PlayerControllerRef = Cast<ABaseClass_PlayerController>(GetWorld()->GetFirstPlayerController());

		for (int i = 0; i < RoomSpawnSceneComponents.Num(); i++) {
			if (RoomSpawnSceneComponents[i]->ValidRoomTypes.Num() > 0) {

				// Choose a valid Room to spawn at random
				TSubclassOf<ABaseClass_LevelRoom> ChosenRoomType = RoomSpawnSceneComponents[i]->ValidRoomTypes[FMath::RandRange(0, RoomSpawnSceneComponents[i]->ValidRoomTypes.Num() - 1)];
				RoomSpawnSceneComponents[i]->GetSocketWorldLocationAndRotation(Name, Location, Rotation);

				// Add the spawned room to the exits list
				NewExit.RoomReference = RoomSpawner->SpawnNewRoom(ChosenRoomType, Location, Rotation, RoomSpawnSceneComponents[i]->ExitDirection);
				NewExit.DisplayName = RoomSpawnSceneComponents[i]->ExitLabel;
				ExitsList.Add(NewExit);

				// Set the spawned room's previous room to be this one
				NewExit.RoomReference->PreviousRoomExit.RoomReference = this;
				//NewExit.RoomReference->PreviousRoomExit.

			} else {
				GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Error: No valid room types"));
			}

		}
	}
}

void ABaseClass_LevelRoom::SpawnEnemyFormation(F_LevelRoom_EnemyFormation EnemyFormation)
{
	FString ContextString;

	// Get all the components first
	GetComponents<UBaseComponent_Room_Tile>(SceneCoordinateComponents);

	// For each enemy in the formation, find the tile it should spawn on and spawn it
	for (const TPair<FVector2D, FDataTableRowHandle>& Map : EnemyFormation.EnemiesMap) {
		for (int j = 0; j < SceneCoordinateComponents.Num(); j++) {
			if (SceneCoordinateComponents[j]->GridCoordinates.X == Map.Key.X && SceneCoordinateComponents[j]->GridCoordinates.Y == Map.Key.Y) {
				EntityInBattle_Reference = GetWorld()->SpawnActor<ABaseClass_EntityInBattle>(EntityInBattle_Class, (FVector(SceneCoordinateComponents[j]->GetComponentLocation().X, SceneCoordinateComponents[j]->GetComponentLocation().Y, (SceneCoordinateComponents[j]->GetComponentLocation().Z + 10))), (this->GetActorRotation()));
				EntityInBattle_Reference->ResetStatsWidget();
				break;
			}
		}
	}
}


void ABaseClass_LevelRoom::PlayerEnterRoom()
{
	ABaseClass_PlayerController* PlayerControllerRef = Cast<ABaseClass_PlayerController>(GetWorld()->GetFirstPlayerController());
	
	if (PlayerControllerRef) {
		if (PlayerControllerRef->Level_HUD_Widget->IsValidLowLevel() && RoomEncounter_Class) {

			// Add Encounters to the List
			for (int i = 0; i < EncountersList.Num(); i++) {
				RoomEncounter_Widget = CreateWidget<UWidgetComponent_RoomEncounter>(GetWorld(), RoomEncounter_Class);
				RoomEncounter_Widget->EncounterData = EncountersList[i];
				RoomEncounter_Widget->EncounterLabel->SetText(FText::FromString(EncountersList[i].DisplayName));
				PlayerControllerRef->Level_HUD_Widget->EncounterList_ScrollBox->AddChild(RoomEncounter_Widget);
			}
		}

		if (PlayerControllerRef->CurrentRoom != this)
			PlayerControllerRef->CurrentRoom = this;

		// Get all exits and add to HUD
		if (RoomExit_Class) {
			for (int i = 0; i < ExitsList.Num(); i++) {
				RoomExit_Widget = CreateWidget<UWidgetComponent_RoomExit>(GetWorld(), RoomExit_Class);
				RoomExit_Widget->EncounterLabel->SetText(FText::FromString("E"));

				PlayerControllerRef->Level_HUD_Widget->ExitList_ScrollBox->AddChild(RoomExit_Widget);
			}
		}
	}
}