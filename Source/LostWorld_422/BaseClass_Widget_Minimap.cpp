#include "BaseClass_Widget_Minimap.h"

#include "WidgetComponent_MinimapRoom.h"
#include "Components/SceneComponent.h"
#include "Components/UniformGridSlot.h"
#include "Components/GridSlot.h"
#include "BaseClass_GridTile.h"
#include "BaseClass_PlayerController.h"


void UBaseClass_Widget_Minimap::GenerateLevel()
{
	FActorSpawnParameters SpawnParameters;
	TArray<USceneComponent*> GridTileSceneComponents;

	// Generate Base Level
	if (MinimapRoom_Class) {
		for (int x = 0; x <= 15; x++) {
			for (int y = 0; y <= 15; y++) {
				MinimapRoom_Widget = CreateWidget<UWidgetComponent_MinimapRoom>(GetWorld(), MinimapRoom_Class);
				MinimapRoom_Widget->MinimapReference = this;

				UUniformGridSlot* MinimapRoom_Slot = LevelGrid->AddChildToUniformGrid(Cast<UWidget>(MinimapRoom_Widget));

				MinimapRoom_Slot->SetRow(y);
				MinimapRoom_Slot->SetColumn(x);

				MinimapRoom_Widget->X_Coordinate = x;
				MinimapRoom_Widget->Y_Coordinate = y;

				MinimapRoom_Slot->SetHorizontalAlignment(EHorizontalAlignment::HAlign_Fill);
				MinimapRoom_Slot->SetVerticalAlignment(EVerticalAlignment::VAlign_Fill);
			}
		}
	}

	if (GridTile_Class) {
		for (TObjectIterator<UWidgetComponent_MinimapRoom> Itr; Itr; ++Itr) {
			UWidgetComponent_MinimapRoom* FoundWidget = *Itr;
			FVector SpawnLocation = FVector((200 * FoundWidget->X_Coordinate) - 200, (200 * FoundWidget->Y_Coordinate) - 200, 0);

			GridTile_Actor = GetWorld()->SpawnActor<ABaseClass_GridTile>(GridTile_Class, SpawnLocation, FRotator::ZeroRotator, SpawnParameters);
			GridTile_Actor->X_Coordinate = FoundWidget->X_Coordinate;
			GridTile_Actor->Y_Coordinate = FoundWidget->Y_Coordinate;

			FoundWidget->GridTileReference = GridTile_Actor;
			GridTile_Actor->MinimapRoomReference = FoundWidget;

			// Set PlayerRestPoint reference
			if (GridTile_Actor) {
				GridTile_Actor->GetComponents(GridTileSceneComponents);
				for (USceneComponent* Component : GridTileSceneComponents) {
					if (Component->GetName() == "PlayerRestPoint") {
						GridTile_Actor->PlayerRestPointReference = Component;
						break;
					}
				}
			}

			GridTilesArray.Add(GridTile_Actor);
		}
	}

	// Generate Encounters
	// Get X Random Tiles to add Enemy Encounters to
	FDataTableRowHandle EnemyFormationsTableRow;

	for (int i = 0; i < 10; i++) {
		//EnemyFormationsTable->Table = EnemyFormationsTable;
		EnemyFormationsTableRow.DataTable = EnemyFormationsTable;
		EnemyFormationsTableRow.RowName = "Test";

		F_LevelRoom_Encounter NewEncounter("Test", false, EnemyFormationsTableRow);

		GridTilesArray[FMath::RandRange(0, GridTilesArray.Num() - 1)]->EncountersList.Add(NewEncounter);
	}

	//for (TObjectIterator<ABaseClass_GridTile> Itr; Itr; ++Itr) {
	//	ABaseClass_GridTile* FoundTile = *Itr;
	//}

	ABaseClass_PlayerController* LocalPlayerControllerRef = Cast<ABaseClass_PlayerController>(GetWorld()->GetFirstPlayerController());
	LocalPlayerControllerRef->ManualBeginPlay();
}


void UBaseClass_Widget_Minimap::GetPlayerNeighbouringTiles(UWidgetComponent_MinimapRoom* CurrentRoomWidget)
{
	PlayerNeighbouringRoomWidgets.Empty();

	for (TObjectIterator<UWidgetComponent_MinimapRoom> Itr; Itr; ++Itr) {
		UWidgetComponent_MinimapRoom* FoundWidget = *Itr;

		// Get immediate neighbours, not including diagonals
		if (FoundWidget->X_Coordinate == CurrentRoomWidget->X_Coordinate + 1 && FoundWidget->Y_Coordinate == CurrentRoomWidget->Y_Coordinate ||
			FoundWidget->X_Coordinate == CurrentRoomWidget->X_Coordinate - 1 && FoundWidget->Y_Coordinate == CurrentRoomWidget->Y_Coordinate ||
			FoundWidget->X_Coordinate == CurrentRoomWidget->X_Coordinate && FoundWidget->Y_Coordinate == CurrentRoomWidget->Y_Coordinate + 1 ||
			FoundWidget->X_Coordinate == CurrentRoomWidget->X_Coordinate && FoundWidget->Y_Coordinate == CurrentRoomWidget->Y_Coordinate - 1) {
			PlayerNeighbouringRoomWidgets.Add(FoundWidget);
			FoundWidget->BackgroundImage->SetColorAndOpacity(FLinearColor(0.f, 1.f, 0.f, 1.f));
		} else if (FoundWidget->X_Coordinate == CurrentRoomWidget->X_Coordinate && FoundWidget->Y_Coordinate == CurrentRoomWidget->Y_Coordinate) {
			FoundWidget->BackgroundImage->SetColorAndOpacity(FLinearColor(1.f, 1.f, 1.f, 1.f));
		} else {
			FoundWidget->BackgroundImage->SetColorAndOpacity(FLinearColor(1.f, 0.f, 0.f, 1.f));
		}
	}
}