#include "WidgetComponent_MinimapRoom.h"

#include "BaseClass_EntityInBattle.h"
#include "BaseClass_PlayerController.h"
#include "BaseClass_Widget_Minimap.h"


void UWidgetComponent_MinimapRoom::SetColour()
{
	if (GridTileReference->EncountersList.Num() > 0) {
		BackgroundImage->SetColorAndOpacity(FLinearColor(0.f, 0.f, 1.f, 1.f));
		return;
	}
}


void UWidgetComponent_MinimapRoom::OnRoomSelected()
{
	if (PlayerCanMoveTo) {
		for (TObjectIterator<ABaseClass_EntityInBattle> Itr; Itr; ++Itr) {
			ABaseClass_EntityInBattle* FoundEntity = *Itr;

			if (FoundEntity->PlayerControllerRef && GridTileReference) {
				FoundEntity->PlayerControllerRef->MoveToTile(GridTileReference);
				break;
			}
		}
	}
}