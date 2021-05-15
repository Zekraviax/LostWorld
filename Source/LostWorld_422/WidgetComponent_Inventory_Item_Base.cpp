#include "WidgetComponent_Inventory_Item_Base.h"

#include "BaseClass_PlayerController.h"
#include "Widget_Inventory_Base.h"


// ------------------------- Item
void UWidgetComponent_Inventory_Item_Base::OnEquipButtonPressed()
{
	// Equip item
	if (ItemEquipTextWidget->GetText().ToString() == "Equip") {
		// Find a slot that the item can be equipped to
		for (TObjectIterator<UWidgetComponent_Inventory_Item_Base> Itr; Itr; ++Itr) {
			UWidgetComponent_Inventory_Item_Base* FoundWidget = *Itr;

			if (ItemData.EquipSlots.Contains(FoundWidget->StaticEquipmentSlotType)) {
				// Unequip the currently equipped item, if there is one equipped
				if (FoundWidget->ItemData.DisplayName != "Default")
					Cast<ABaseClass_PlayerController>(GetWorld()->GetFirstPlayerController())->PlayerInventory.Add(FoundWidget->ItemData);

				FoundWidget->ItemData = ItemData;

				Cast<ABaseClass_PlayerController>(GetWorld()->GetFirstPlayerController())->PlayerInventory.Remove(ItemData);
			}
		}
	} else if (ItemEquipTextWidget->GetText().ToString() == "Unequip") {
		// Unequip item
		//if (FoundWidget->ItemData.DisplayName != "Default")
			//Cast<ABaseClass_PlayerController>(GetWorld()->GetFirstPlayerController())->PlayerInventory.Add(FoundWidget->ItemData);

		Cast<ABaseClass_PlayerController>(GetWorld()->GetFirstPlayerController())->PlayerInventory.Add(ItemData);
		ItemData = F_Item_Base();
	}

	for (TObjectIterator<UWidget_Inventory_Base> Itr; Itr; ++Itr) {
		UWidget_Inventory_Base* FoundWidget = *Itr;

		FoundWidget->OnInventoryOpened(Cast<ABaseClass_PlayerController>(GetWorld()->GetFirstPlayerController()));
	}
}


// ------------------------- Widget
void UWidgetComponent_Inventory_Item_Base::UpdateWidget()
{
	// Static Equipment Widgets
	if (StaticEquipmentSlot) {
		if (ItemEquipTextWidget->IsValidLowLevel())
			ItemEquipTextWidget->SetText(FText::FromString("Unequip"));

		if (ItemData.DisplayName == "Default") {
			if (ItemEquipButtonWidget->IsValidLowLevel())
				ItemEquipButtonWidget->SetIsEnabled(false);

			if (ItemNameTextWIdget->IsValidLowLevel())
				ItemNameTextWIdget->SetText(FText::FromString("Nothing"));
		}
		else {
			if (ItemNameTextWIdget->IsValidLowLevel())
				ItemNameTextWIdget->SetText(FText::FromString(ItemData.DisplayName));
			if (ItemEquipButtonWidget->IsValidLowLevel())
				ItemEquipButtonWidget->SetIsEnabled(true);
		}
	// Unequipped Item Widgets
	} else {
		if (ItemData.DisplayName == "Default")
			RemoveFromParent();
		else {
			if (ItemNameTextWIdget->IsValidLowLevel())
				ItemNameTextWIdget->SetText(FText::FromString(ItemData.DisplayName));
		}
	}
}