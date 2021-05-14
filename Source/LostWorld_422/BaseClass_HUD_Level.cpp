#include "BaseClass_HUD_Level.h"

#include "Widget_Inventory_Base.h"
#include "BaseClass_PlayerController.h"


// ------------------------- Widgets
void UBaseClass_HUD_Level::OpenDeckBuilder()
{
	if (DeckBuilder_Class && !DeckBuilderRef)
	{
		DeckBuilderRef = CreateWidget<UBaseClass_Widget_DeckBuilder>(GetWorld(), DeckBuilder_Class);
		DeckBuilderRef->HUDRef = this;
		DeckBuilderRef->PopulateScrollBoxes();
		DeckBuilderRef->AddToViewport();
	}
}


void UBaseClass_HUD_Level::OpenInventory()
{
	if (InventoryWidget_Class) {
		InventoryWidget_Reference = CreateWidget<UWidget_Inventory_Base>(GetWorld(), InventoryWidget_Class);

		InventoryWidget_Reference->OnInventoryOpened(Cast<ABaseClass_PlayerController>(GetWorld()->GetFirstPlayerController()));

		InventoryWidget_Reference->AddToViewport();
	}
}