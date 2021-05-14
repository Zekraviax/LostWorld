#include "WidgetComponent_Inventory_Item_Base.h"


// ------------------------- Item
void UWidgetComponent_Inventory_Item_Base::OnEquipButtonPressed()
{
	// Equip item
	if (ItemNameText->GetText().ToString() == "Equip") {

	}
}


// ------------------------- Widget
void UWidgetComponent_Inventory_Item_Base::UpdateWidget()
{
	// Static Equipment Widgets
	if (StaticEquipmentSlot) {
		ItemEquipText->SetText(FText::FromString("Unequip"));

		if (ItemData.DisplayName == "Default") {
			ItemEquipButton->SetIsEnabled(false);
			ItemNameText->SetText(FText::FromString("Nothing"));
		}
	} else {
		ItemNameText->SetText(FText::FromString(ItemData.DisplayName));
	}
}