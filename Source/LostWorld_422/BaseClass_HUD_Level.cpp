#include "BaseClass_HUD_Level.h"

#include "BaseClass_PlayerController.h"
#include "LostWorld_422GameModeBase.h"
#include "Widget_CharacterScreen.h"
#include "Widget_Inventory_Base.h"


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


void UBaseClass_HUD_Level::OpenCharacterSheet()
{
	if (CharacterScreen_Class) {
		CharacterScreen_Reference = CreateWidget<UWidget_CharacterScreen>(GetWorld(), CharacterScreen_Class);
		CharacterScreen_Reference->SetVariables(Cast<ABaseClass_PlayerController>(GetWorld()->GetFirstPlayerController())->EntityInBattleRef->EntityBaseData);
		CharacterScreen_Reference->AddToViewport();
	}
}