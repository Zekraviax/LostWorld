#include "WidgetComponent_Inventory_Item_Base.h"

#include "BaseClass_PlayerController.h"
#include "Widget_Inventory_Base.h"


// ------------------------- Item
void UWidgetComponent_Inventory_Item_Base::OnEquipButtonPressed()
{
	FActorSpawnParameters SpawnParameters;

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
				Cast<ABaseClass_PlayerController>(GetWorld()->GetFirstPlayerController())->EntityInBattleRef->EquippedItems.Add(ItemData);

				// Run item equip function
				AItemFunctions_BaseClass* ItemAbilityActor_Reference = GetWorld()->SpawnActor<AItemFunctions_BaseClass>(ItemData.Functions, FVector::ZeroVector, FRotator::ZeroRotator, SpawnParameters);
				ItemAbilityActor_Reference->TriggeredFunction_OnItemEquipped(Cast<ABaseClass_PlayerController>(GetWorld()->GetFirstPlayerController())->EntityInBattleRef);
				ItemAbilityActor_Reference->ConditionalBeginDestroy();

				break;
			}
		}
	} else if (ItemEquipTextWidget->GetText().ToString() == "Unequip") {
		// Unequip item
		Cast<ABaseClass_PlayerController>(GetWorld()->GetFirstPlayerController())->PlayerInventory.Add(ItemData);
		Cast<ABaseClass_PlayerController>(GetWorld()->GetFirstPlayerController())->EntityInBattleRef->EquippedItems.Remove(ItemData);

		// Run item unequip function
		AItemFunctions_BaseClass* ItemAbilityActor_Reference = GetWorld()->SpawnActor<AItemFunctions_BaseClass>(ItemData.Functions, FVector::ZeroVector, FRotator::ZeroRotator, SpawnParameters);

		if (ItemAbilityActor_Reference->IsValidLowLevel()) {
			ItemAbilityActor_Reference->TriggeredFunction_OnItemUnequipped(Cast<ABaseClass_PlayerController>(GetWorld()->GetFirstPlayerController())->EntityInBattleRef);
			ItemAbilityActor_Reference->ConditionalBeginDestroy();
		}

		ItemData = F_Item_Base();
		UpdateWidget();
	}
	else if (ItemEquipTextWidget->GetText().ToString() == "Activate") {

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