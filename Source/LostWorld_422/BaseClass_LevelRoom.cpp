#include "BaseClass_LevelRoom.h"

#include "BaseClass_PlayerController.h"


// Sets default values
ABaseClass_LevelRoom::ABaseClass_LevelRoom()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Construct EntityInWorld
	static ConstructorHelpers::FObjectFinder<UBlueprint> EntityInBattle_BlueprintConstruct(TEXT("Blueprint'/Game/Blueprint_EntityInBattle.Blueprint_EntityInBattle'"));

	if (EntityInBattle_BlueprintConstruct.Object) {
		EntityInBattle_Class = (UClass*)EntityInBattle_BlueprintConstruct.Object->GeneratedClass;
	}

}

// Called when the game starts or when spawned
void ABaseClass_LevelRoom::BeginPlay()
{
	Super::BeginPlay();
	
	// Spawn enemies test
	//SpawnEnemyFormation();

	// Add a test encounter to the room
	//EncountersList.
}

// Called every frame
void ABaseClass_LevelRoom::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// ------------------------- Setup
void ABaseClass_LevelRoom::SpawnEnemyFormation()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Cyan, TEXT("Attempting to spawn enemy formation."));

	FName RowName = RoomData.EncounterListEntry.RowName;
	FString ContextString;
	TMap<FVector2D, FDataTableRowHandle> LocalEnemiesMapRef = RoomData.EncounterListEntry.DataTable->FindRow<F_LevelRoom_EnemyFormation>(RowName, ContextString)->EnemiesMap;

	// Get all the components first
	GetComponents<UBaseComponent_Room_Tile>(SceneCoordinateComponents);

	// For each enemy in the formation, find the tile it should spawn on and spawn it
	for (const TPair<FVector2D, FDataTableRowHandle>& Map : LocalEnemiesMapRef) {
		for (int j = 0; j < SceneCoordinateComponents.Num(); j++) {
			if (SceneCoordinateComponents[j]->GridCoordinates.X == Map.Key.X && SceneCoordinateComponents[j]->GridCoordinates.Y == Map.Key.Y) {
				//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Cyan, TEXT("Found a tile to spawn an enemy."));
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
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Cyan, TEXT("PlayerControllerRef Valid."));
		if (PlayerControllerRef->Level_HUD_Widget->IsValidLowLevel() && RoomEncounter_Class) {
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Cyan, TEXT("Player Level HUD Valid"));
			for (int i = 0; i < EncountersList.Num(); i++) {
				RoomEncounter_Widget = CreateWidget<UWidgetComponent_RoomEncounter>(GetWorld(), RoomEncounter_Class);
				RoomEncounter_Widget->EncounterData = EncountersList[i];
				RoomEncounter_Widget->EncounterLabel->SetText(FText::FromString(EncountersList[i].DisplayName));
				PlayerControllerRef->Level_HUD_Widget->EncounterList_ScrollBox->AddChild(RoomEncounter_Widget);
			}
		}
	}
}