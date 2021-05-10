#include "BaseClass_Widget_Minimap.h"

#include "WidgetComponent_MinimapRoom.h"
#include "Components/SceneComponent.h"
#include "Components/UniformGridSlot.h"
#include "Components/GridSlot.h"
#include "BaseClass_GridTile.h"
#include "BaseClass_LevelRoom.h"
#include "BaseClass_PlayerController.h"
#include "Level_SpawnTypeBase.h"
#include "Level_SpawnType_FourSquare.h"


void UBaseClass_Widget_Minimap::GenerateLevel()
{
	ALevel_SpawnTypeBase* LevelGenerator = nullptr;

	for (TObjectIterator<ALevel_SpawnTypeBase> Itr; Itr; ++Itr) {
		ALevel_SpawnTypeBase* FoundGenerator = *Itr;
		LevelGenerator = FoundGenerator;
	}

	LevelGenerator->PlayerMinimapReference = this;
	LevelGenerator->RunLevelGeneratorFunction();

	Cast<ALostWorld_422GameStateBase>(GetWorld()->GetGameState())->CurrentFloorNumber++;
}


void UBaseClass_Widget_Minimap::UpdateMinimap(ABaseClass_GridTile* CurrentPlayerLocation)
{
	for (TObjectIterator<UWidgetComponent_MinimapRoom> Itr; Itr; ++Itr) {
		UWidgetComponent_MinimapRoom* FoundWidget = *Itr;

		// Get immediate player's neighbours, not including diagonals
		if (FoundWidget->X_Coordinate == CurrentPlayerLocation->X_Coordinate + 1 && FoundWidget->Y_Coordinate == CurrentPlayerLocation->Y_Coordinate ||
			FoundWidget->X_Coordinate == CurrentPlayerLocation->X_Coordinate - 1 && FoundWidget->Y_Coordinate == CurrentPlayerLocation->Y_Coordinate ||
			FoundWidget->X_Coordinate == CurrentPlayerLocation->X_Coordinate && FoundWidget->Y_Coordinate == CurrentPlayerLocation->Y_Coordinate + 1 ||
			FoundWidget->X_Coordinate == CurrentPlayerLocation->X_Coordinate && FoundWidget->Y_Coordinate == CurrentPlayerLocation->Y_Coordinate - 1) {
			FoundWidget->BackgroundImage->SetColorAndOpacity(FLinearColor(0.f, 1.f, 0.f, 1.f));
			FoundWidget->PlayerCanMoveTo = true;
		}
		else if (FoundWidget->X_Coordinate == CurrentPlayerLocation->X_Coordinate && FoundWidget->Y_Coordinate == CurrentPlayerLocation->Y_Coordinate) {
			FoundWidget->BackgroundImage->SetColorAndOpacity(FLinearColor(0.34f, 0.34f, 0.34f, 1.f));
			FoundWidget->PlayerCanMoveTo = false;
		}
		else {
			FoundWidget->BackgroundImage->SetColorAndOpacity(FLinearColor(1.f, 1.f, 1.f, 1.f));
			FoundWidget->PlayerCanMoveTo = false;
		}

		
		if (FoundWidget->GridTileReference->IsValidLowLevel()) {
			// If there's an enemy at any given tile, change that tiles colour.
			if (FoundWidget->GridTileReference->OnPlayerEnterTileFunction == E_GridTile_OnPlayerEnterTileFunctions_Enum::E_TriggerBattle) {
				FoundWidget->BackgroundImage->SetColorAndOpacity(FLinearColor(1.f, 0.6f, 0.f, 1.f));
			}

			// Highlight the stairs
			else if (FoundWidget->GridTileReference->OnPlayerEnterTileFunction == E_GridTile_OnPlayerEnterTileFunctions_Enum::E_Stairs) {
				FoundWidget->BackgroundImage->SetColorAndOpacity(FLinearColor(0.6f, 0.f, 1.f, 1.f));
			}
		}
	}
}