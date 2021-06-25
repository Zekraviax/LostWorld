#include "Level_SpawnType_BossDen.h"

#include "BaseClass_LevelRoom.h"
#include "BaseClass_GridTile.h"
#include "BaseClass_PlayerController.h"
#include "BaseClass_Widget_Minimap.h"
#include "WidgetComponent_MinimapRoom.h"
#include "Components/UniformGridSlot.h"


// ------------------------- Base Class Functions
void ALevel_SpawnType_BossDen::RunLevelGeneratorFunction()
{
	FActorSpawnParameters SpawnParameters;
	TArray<USceneComponent*> GridTileSceneComponents;
	TArray<FVector2D> FullLevelArrayCoordinates;

	// Level Formation: Boss Den
	// One large room for the boss, with a corridor that the player starts in

	ABaseClass_LevelRoom* RoomOne = GetWorld()->SpawnActor<ABaseClass_LevelRoom>(LevelRoom_Class);

	for (int x = 5; x < 10; x++) {
		for (int y = 5; y < 10; y++) {
			FullLevelArrayCoordinates.Add(FVector2D(x, y));
		}
	}

	for (int i = 0; i <= 5; i++) {
		FullLevelArrayCoordinates.AddUnique(FVector2D(i, 5));
	}

	// Spawn minimap tiles
	if (MinimapRoom_Class) {
		for (int x = 0; x <= 10; x++) {
			for (int y = 0; y <= 10; y++) {
				MinimapRoom_Widget = CreateWidget<UWidgetComponent_MinimapRoom>(GetWorld(), MinimapRoom_Class);
				MinimapRoom_Widget->MinimapReference = PlayerMinimapReference;

				UUniformGridSlot* MinimapRoom_Slot = PlayerMinimapReference->LevelGrid->AddChildToUniformGrid(Cast<UWidget>(MinimapRoom_Widget));

				MinimapRoom_Slot->SetRow(y);
				MinimapRoom_Slot->SetColumn(x);

				MinimapRoom_Widget->X_Coordinate = x;
				MinimapRoom_Widget->Y_Coordinate = y;

				MinimapRoom_Slot->SetHorizontalAlignment(EHorizontalAlignment::HAlign_Fill);
				MinimapRoom_Slot->SetVerticalAlignment(EVerticalAlignment::VAlign_Fill);

				if (!FullLevelArrayCoordinates.Contains(FVector2D(x, y))) {
					MinimapRoom_Widget->BackgroundImage->SetVisibility(ESlateVisibility::Hidden);
					MinimapRoom_Widget->InteractButton->SetVisibility(ESlateVisibility::Collapsed);
				}
				else
					FullMinimapRoomArray.Add(MinimapRoom_Widget);
			}
		}
	}

	// Spawn Minimap tiles into World
	if (GridTile_Class) {
		for (int i = 0; i < FullMinimapRoomArray.Num(); i++) {
			FVector SpawnLocation = FVector((200 * FullMinimapRoomArray[i]->X_Coordinate) - 200, (200 * FullMinimapRoomArray[i]->Y_Coordinate) - 200, 0);

			GridTile_Actor = GetWorld()->SpawnActor<ABaseClass_GridTile>(GridTile_Class, SpawnLocation, FRotator::ZeroRotator, SpawnParameters);
			GridTile_Actor->X_Coordinate = FullMinimapRoomArray[i]->X_Coordinate;
			GridTile_Actor->Y_Coordinate = FullMinimapRoomArray[i]->Y_Coordinate;

			FullMinimapRoomArray[i]->GridTileReference = GridTile_Actor;
			GridTile_Actor->MinimapRoomReference = FullMinimapRoomArray[i];

			GridTilesArray.Add(GridTile_Actor);

			// Cardinal Directions
			//if (MinimapArrayRoomOneCoordinates.Contains(FVector2D(GridTile_Actor->X_Coordinate, GridTile_Actor->Y_Coordinate))) {
			//	GridTile_Actor->BaseColour = FLinearColor(1.f, 1.f, 0.5f, 1.f);

			//	RoomOneGridTiles.Add(GridTile_Actor);
			//	RoomOne->GridTilesInRoom.Add(GridTile_Actor);
			//	GridTile_Actor->RoomReference = RoomOne;

			//	PlayerSpawnTiles.Add(GridTile_Actor);
			//}
			//else if (MinimapArrayRoomTwoCoordinates.Contains(FVector2D(GridTile_Actor->X_Coordinate, GridTile_Actor->Y_Coordinate))) {
			//	GridTile_Actor->BaseColour = FLinearColor(1.f, 0.5f, 0.5f, 1.f);

			//	RoomTwoGridTiles.Add(GridTile_Actor);
			//	RoomTwo->GridTilesInRoom.Add(GridTile_Actor);
			//	GridTile_Actor->RoomReference = RoomTwo;

			//	PlayerSpawnTiles.Add(GridTile_Actor);
			//}
			//else if (MinimapArrayRoomThreeCoordinates.Contains(FVector2D(GridTile_Actor->X_Coordinate, GridTile_Actor->Y_Coordinate))) {
			//	GridTile_Actor->BaseColour = FLinearColor(0.5f, 0.5f, 1.f, 1.f);

			//	RoomThreeGridTiles.Add(GridTile_Actor);
			//	RoomThree->GridTilesInRoom.Add(GridTile_Actor);
			//	GridTile_Actor->RoomReference = RoomThree;

			//	PlayerSpawnTiles.Add(GridTile_Actor);
			//}
			//else if (MinimapArrayRoomFourCoordinates.Contains(FVector2D(GridTile_Actor->X_Coordinate, GridTile_Actor->Y_Coordinate))) {
			//	GridTile_Actor->BaseColour = FLinearColor(0.5f, 1.f, 0.5f, 1.f);

			//	RoomFourGridTiles.Add(GridTile_Actor);
			//	RoomFour->GridTilesInRoom.Add(GridTile_Actor);
			//	GridTile_Actor->RoomReference = RoomFour;

			//	PlayerSpawnTiles.Add(GridTile_Actor);
			//}

			//GridTile_Actor->DynamicMaterial->SetVectorParameterValue("Color", GridTile_Actor->BaseColour);
		}
	}

	// Add a boss encounter
	GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Red, FString::Printf(TEXT("Generate Boss Encounter")));
	FDataTableRowHandle EnemyFormationsTableRow;

	EnemyFormationsTableRow.DataTable = EnemyFormationsTable;
	EnemyFormationsTableRow.RowName = "SoloTest";

	F_LevelRoom_Encounter NewEncounter("SoloTest", false, EnemyFormationsTableRow);
	NewEncounter.EncounterListEntry.DataTable = EnemyFormationsTable;
	NewEncounter.EncounterListEntry.RowName = "IronShellAutomaton";

	for (TActorIterator<ABaseClass_GridTile> TileItr(GetWorld()); TileItr; ++TileItr) {
		ABaseClass_GridTile* FoundTile = *TileItr;

		if (FoundTile->X_Coordinate == 9 &&
			FoundTile->Y_Coordinate == 5) {

			FoundTile->EncountersList.Add(NewEncounter);
		} else if (FoundTile->X_Coordinate == 0 &&
			FoundTile->Y_Coordinate == 5) {

			ABaseClass_PlayerController* LocalPlayerControllerRef = Cast<ABaseClass_PlayerController>(GetWorld()->GetFirstPlayerController());
			LocalPlayerControllerRef->ControlMode = E_Player_ControlMode::E_Move;

			LocalPlayerControllerRef->MoveToTile(FoundTile);
		}
	}

	// Spawn Player into the level at the start of the corridor
	for (TActorIterator<ABaseClass_GridTile> TileItr(GetWorld()); TileItr; ++TileItr) {
		ABaseClass_GridTile* FoundTile = *TileItr;
		if (FoundTile->RoomReference->IsValidLowLevel()) {
			if (FoundTile->OnPlayerEnterTileFunction == E_GridTile_OnPlayerEnterTileFunctions_Enum::E_None) {
				ABaseClass_PlayerController* LocalPlayerControllerRef = Cast<ABaseClass_PlayerController>(GetWorld()->GetFirstPlayerController());
				LocalPlayerControllerRef->ControlMode = E_Player_ControlMode::E_Move;

				LocalPlayerControllerRef->MoveToTile(FoundTile);
				//FoundTile->OccupyingEntity = LocalPlayerControllerRef->EntityInBattleRef;
				break;
			}
		}
	}
}