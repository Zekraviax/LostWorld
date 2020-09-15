#include "WidgetComponent_MinimapRoom.h"

#include "BaseClass_EntityInBattle.h"
#include "BaseClass_PlayerController.h"


void UWidgetComponent_MinimapRoom::OnRoomSelected()
{
	for (TObjectIterator<ABaseClass_EntityInBattle> Itr; Itr; ++Itr) {
		ABaseClass_EntityInBattle* FoundEntity = *Itr;

		if (FoundEntity->PlayerControllerRef && GridTileReference) {
			if (GridTileReference) {
				FoundEntity->PlayerControllerRef->MoveToTile(GridTileReference);
			} else {

			}
			break;
		}
	}
}