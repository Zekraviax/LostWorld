#include "Widget_Inventory_Base.h"

#include "BaseClass_EntityInBattle.h"
#include "BaseClass_PlayerController.h"
#include "BaseClass_HUD_Battle.h"
#include "WidgetComponent_Inventory_Item_Base.h"


// ------------------------- Widget
void UWidget_Inventory_Base::OnInventoryOpened(ABaseClass_PlayerController* PlayerController, bool SetInBattleMode)
{
	// Set variables for later use
	InBattleMode = SetInBattleMode;
	if (!PlayerController->IsValidLowLevel())
		PlayerControllerReference = PlayerController;


	// Get all equipped items and add them to the EquippedItemsScrollBox
	bool BreakOutOfLoop = false;
	for (int x = 0; x < EquippedItemsScrollBox->GetChildrenCount(); x++) {
		//if (BreakOutOfLoop)
		//	break;

		if (Cast<UWidgetComponent_Inventory_Item_Base>(EquippedItemsScrollBox->GetChildAt(x))) {
			InventoryItem_Reference = Cast<UWidgetComponent_Inventory_Item_Base>(EquippedItemsScrollBox->GetChildAt(x));
			InventoryItem_Reference->ItemData = F_Item_Base(); // Fixes that annoying auto-equipping Sol Ring

			// Make sure that all children widgets are visible
			if (InventoryItem_Reference->GetVisibility() != ESlateVisibility::Visible) {
				InventoryItem_Reference->SetVisibility(ESlateVisibility::Visible);
			}

			if (!BreakOutOfLoop) {
				for (int i = 0; i < PlayerController->EntityInBattleRef->EquippedItems.Num(); i++) {
					if (InventoryItem_Reference->IsValidLowLevel()) {
						if (InventoryItem_Reference->StaticEquipmentSlot) {
							if (PlayerController->EntityInBattleRef->EquippedItems[i].EquipSlots.Contains(InventoryItem_Reference->StaticEquipmentSlotType)) {
								InventoryItem_Reference->ItemData = PlayerController->EntityInBattleRef->EquippedItems[i];
								BreakOutOfLoop = true;
								break;
							}
						}
					}
				}

				InventoryItem_Reference->UpdateWidget();
			}
		}
	}

	//Get all unequipped items and add them to the UnequippedItemsScrollBox
	if (InventoryItem_Class)
		UnequippedItemsScrollBox->ClearChildren();

	for (int i = 0; i < PlayerController->PlayerInventory.Num(); i++) {
		if (InventoryItem_Class->IsValidLowLevel()) {
			InventoryItem_Reference = CreateWidget<UWidgetComponent_Inventory_Item_Base>(GetWorld(), InventoryItem_Class);

			InventoryItem_Reference->ItemData = PlayerController->PlayerInventory[i];
			InventoryItem_Reference->UpdateWidget();

			UnequippedItemsScrollBox->AddChild(InventoryItem_Reference);

			// Don't let players change equipment in the middle of battle(?)
			if (InBattleMode) {
				if (InventoryItem_Reference->ItemEquipButtonWidget->IsValidLowLevel()) {
					InventoryItem_Reference->ItemEquipButtonWidget->bIsEnabled = false;
				}
			}
		}
	}

	// In-Battle Mode: Change all of the Equip buttons to Activate buttons for items that have activated abilities
	// Remove all others 
	if (InBattleMode) {
		for (int i = 0; i < EquippedItemsScrollBox->GetAllChildren().Num(); i++) {
			// Hide all text
			if (Cast<UTextBlock>(EquippedItemsScrollBox->GetChildAt(i))) {
				EquippedItemsScrollBox->GetChildAt(i)->SetVisibility(ESlateVisibility::Collapsed);
			}
			// Hide all equipped items that don't have in-battle functions
			else if (Cast<UWidgetComponent_Inventory_Item_Base>(EquippedItemsScrollBox->GetChildAt(i))) {
				UWidgetComponent_Inventory_Item_Base* ChildItem = Cast<UWidgetComponent_Inventory_Item_Base>(EquippedItemsScrollBox->GetChildAt(i));

				if (!ChildItem->ItemData.HasInBattleFunction) {
					ChildItem->SetVisibility(ESlateVisibility::Collapsed);
				} else {
					//InventoryItem_Reference->ItemEquipButtonWidget.Text
				}
			}
		}
	}

	// Clean up?
	InventoryItem_Reference = nullptr;
}