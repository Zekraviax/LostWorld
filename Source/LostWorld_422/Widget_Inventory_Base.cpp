#include "Widget_Inventory_Base.h"

#include "BaseClass_EntityInBattle.h"
#include "BaseClass_PlayerController.h"
#include "BaseClass_HUD_Battle.h"
#include "WidgetComponent_Inventory_Item_Base.h"


// ------------------------- Widget
void UWidget_Inventory_Base::OnInventoryOpened(ABaseClass_PlayerController* PlayerController)
{
	// Check if the Battle HUD exists.
	// If true, set the Inventory to Battle Mode.
	//if () {

	//}

	if (!PlayerController->IsValidLowLevel())
		PlayerControllerReference = PlayerController;

	if (!PlayerControllerReference->IsValidLowLevel()) {
		PlayerControllerReference = Cast<ABaseClass_PlayerController>(GetWorld()->GetFirstPlayerController());
	}

	// Get all equipped items and add them to the EquippedItemsScrollBox
	for (int x = 0; x < EquippedItemsScrollBox->GetChildrenCount(); x++) {
		if (Cast<UWidgetComponent_Inventory_Item_Base>(EquippedItemsScrollBox->GetChildAt(x))) {
			InventoryItem_Reference = Cast<UWidgetComponent_Inventory_Item_Base>(EquippedItemsScrollBox->GetChildAt(x));
			InventoryItem_Reference->ItemData = F_Item_Base(); // Fixes that annoying auto-equipping Sol Ring

			for (int i = 0; i < PlayerControllerReference->EntityInBattleRef->EquippedItems.Num(); i++) {
				if (InventoryItem_Reference->IsValidLowLevel()) {
					if (InventoryItem_Reference->StaticEquipmentSlot) { 
						if (PlayerControllerReference->EntityInBattleRef->EquippedItems[i].EquipSlots.Contains(InventoryItem_Reference->StaticEquipmentSlotType)) {
							InventoryItem_Reference->ItemData = PlayerControllerReference->EntityInBattleRef->EquippedItems[i];
							break;
						}
					}
				}
			}

			InventoryItem_Reference->UpdateWidget();
		}
	}

	//Get all unequipped items and add them to the UnequippedItemsScrollBox
	if (InventoryItem_Class)
		UnequippedItemsScrollBox->ClearChildren();

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

	// In-Battle Mode: Change all of the Equip buttons to Activate buttons for items that have activated abilities
	// Remove all others 
	if (InBattleMode) {
		for (int i = 0; i < EquippedItemsScrollBox->GetAllChildren().Num(); i++) {

		}
	}
}