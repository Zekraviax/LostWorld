#include "Widget_Inventory_Base.h"

#include "BaseClass_EntityInBattle.h"
#include "BaseClass_PlayerController.h"
#include "WidgetComponent_Inventory_Item_Base.h"


// ------------------------- Widget
void UWidget_Inventory_Base::OnInventoryOpened(ABaseClass_PlayerController* PlayerController)
{
	PlayerControllerReference = PlayerController;

	// Get all equipped items and add them to the EquippedItemsScrollBox
	for (int i = 0; i < PlayerControllerReference->EntityInBattleRef->EquippedItems.Num(); i++) {
		for (int x = 0; x < EquippedItemsScrollBox->GetChildrenCount(); x++) {
			if (Cast<UWidgetComponent_Inventory_Item_Base>(EquippedItemsScrollBox->GetChildAt(x))) {
				InventoryItem_Reference = Cast<UWidgetComponent_Inventory_Item_Base>(EquippedItemsScrollBox->GetChildAt(x));

				if (InventoryItem_Reference->IsValidLowLevel()) {
					if (InventoryItem_Reference->StaticEquipmentSlot &&
						PlayerControllerReference->EntityInBattleRef->EquippedItems[i].EquipSlots.Contains(InventoryItem_Reference->StaticEquipmentSlotType)) {
						InventoryItem_Reference->ItemData = PlayerControllerReference->EntityInBattleRef->EquippedItems[i];
					}
				}

				InventoryItem_Reference->UpdateWidget();
			}
		}
	}

	// Get all unequipped items and add them to the UnequippedItemsScrollBox
	for (int i = 0; i < PlayerControllerReference->PlayerInventory.Num(); i++) {
		if (InventoryItem_Class->IsValidLowLevel()) {
			InventoryItem_Reference = CreateWidget<UWidgetComponent_Inventory_Item_Base>(GetWorld(), InventoryItem_Class);

			InventoryItem_Reference->ItemData = PlayerControllerReference->PlayerInventory[i];
			InventoryItem_Reference->UpdateWidget();

			UnequippedItemsScrollBox->AddChild(InventoryItem_Reference);
		}
	}

	// Clean up?
	InventoryItem_Reference = nullptr;
}