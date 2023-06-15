#include "Level_SpawnType_City.h"

#include "BaseClass_PlayerController.h"
#include "Components/UniformGridSlot.h"
#include "EngineUtils.h"
#include "WidgetComponent_MinimapRoom.h"


// ------------------------- Base Class Functions
void ALevel_SpawnType_City::RunLevelGeneratorFunction()
{
	TArray<FVector2D> FullLevelArrayCoordinates;

	for (TObjectIterator<ABaseClass_GridTile> Itr; Itr; ++Itr) {
		ABaseClass_GridTile* FoundTile = *Itr;
		FullLevelArrayCoordinates.Add(FVector2D(FoundTile->GetActorLocation().X / 200, FoundTile->GetActorLocation().Y / 200));

		// Make sure each tile has coordinates
		FoundTile->X_Coordinate = FoundTile->GetActorLocation().X / 200;
		FoundTile->Y_Coordinate = FoundTile->GetActorLocation().Y / 200;

		if (!FoundTile->PlayerRestPointReference) {
			// Get all child components of the tile
			TArray<UActorComponent*> Components;
			FoundTile->GetComponents<UActorComponent>(Components);

			for (auto& Component : Components) {
				// To-Do: Make sure each tile has a player rest point reference, if one isn't found
				if (Component->GetName().Contains("PlayerRestPoint")) {
					FoundTile->PlayerRestPointReference = Cast<USceneComponent>(Component);
				}
			}
		}
	}

	// Populate minimap widget with tiles
	if (MinimapRoom_Class) {
		for (int x = 0; x <= 20; x++) {
			for (int y = 0; y <= 20; y++) {
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
				} else {
					FullMinimapRoomArray.Add(MinimapRoom_Widget);
				}
			}
		}
	}

	// Set minimap references
	for (TObjectIterator<ABaseClass_GridTile> Itr; Itr; ++Itr) {
		ABaseClass_GridTile* FoundTile = *Itr;

		for (int i = 0; i < FullMinimapRoomArray.Num(); i++) {
			if (FullMinimapRoomArray[i]->X_Coordinate == FoundTile->X_Coordinate &&
				FullMinimapRoomArray[i]->Y_Coordinate == FoundTile->Y_Coordinate) {
				FoundTile->MinimapRoomReference = FullMinimapRoomArray[i];
				break;
			}
		}
	}

	// Spawn Player at the specific spawn tile
	for (TActorIterator<ABaseClass_GridTile> TileItr(GetWorld()); TileItr; ++TileItr) {
		ABaseClass_GridTile* FoundTile = *TileItr;
		if (FoundTile->RoomReference->IsValidLowLevel()) {
			if (FoundTile->OnPlayerEnterTileFunction == E_GridTile_OnPlayerEnterTileFunctions_Enum::E_None) {
				ABaseClass_PlayerController* LocalPlayerControllerRef = Cast<ABaseClass_PlayerController>(GetWorld()->GetFirstPlayerController());
				LocalPlayerControllerRef->ControlMode = E_Player_ControlMode::E_Move;

				LocalPlayerControllerRef->MoveToTile(FoundTile);
				break;
			}
		}
	}
}