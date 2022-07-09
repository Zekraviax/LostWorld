#include "WidgetComponent_Inventory_Item_Base.h"

#include "BaseClass_PlayerController.h"
#include "Widget_Inventory_Base.h"


// ------------------------- Item
void UWidgetComponent_Inventory_Item_Base::OnEquipButtonPressed()
{
	FActorSpawnParameters SpawnParameters;
	ABaseClass_PlayerController* CurrentPlayerController = Cast<ABaseClass_PlayerController>(GetWorld()->GetFirstPlayerController());

	// Equip item
	if (ItemEquipText->GetText().ToString() == "Equip") {
		// Find a slot that the item can be equipped to
		for (TObjectIterator<UWidgetComponent_Inventory_Item_Base> Itr; Itr; ++Itr) {
			UWidgetComponent_Inventory_Item_Base* FoundWidget = *Itr;

			if (ItemData.EquipSlots.Contains(FoundWidget->StaticEquipmentSlotType)) {
				// Unequip the currently equipped item, if there is one equipped
				/*
				if (FoundWidget->ItemData.DisplayName != "Default")
					Cast<ABaseClass_PlayerController>(GetWorld()->GetFirstPlayerController())->PlayerInventory.Add(FoundWidget->ItemData);
				*/

				FoundWidget->ItemData = ItemData;
				CurrentPlayerController->PlayerInventory.Remove(ItemData);
				CurrentPlayerController->EntityInBattleRef->EquippedItems.Add(ItemData);

				// Run item equip function
				AItemFunctions_BaseClass* ItemAbilityActor_Reference = GetWorld()->SpawnActor<AItemFunctions_BaseClass>(ItemData.Functions, FVector::ZeroVector, FRotator::ZeroRotator, SpawnParameters);
				ItemAbilityActor_Reference->TriggeredFunction_OnItemEquipped(CurrentPlayerController->EntityInBattleRef);
				ItemAbilityActor_Reference->ConditionalBeginDestroy();

				break;
			}
		}
	} else if (ItemEquipText->GetText().ToString() == "Unequip") {
		// Unequip item
		CurrentPlayerController->PlayerInventory.Add(ItemData);
		CurrentPlayerController->EntityInBattleRef->EquippedItems.Remove(ItemData);

		// Run item unequip function
		AItemFunctions_BaseClass* ItemAbilityActor_Reference = GetWorld()->SpawnActor<AItemFunctions_BaseClass>(ItemData.Functions, FVector::ZeroVector, FRotator::ZeroRotator, SpawnParameters);

		if (ItemAbilityActor_Reference->IsValidLowLevel()) {
			ItemAbilityActor_Reference->TriggeredFunction_OnItemUnequipped(CurrentPlayerController->EntityInBattleRef);
			ItemAbilityActor_Reference->ConditionalBeginDestroy();
		}

		ItemData = F_Item_Base();
		UpdateWidget();
	}

	for (TObjectIterator<UWidget_Inventory_Base> Itr; Itr; ++Itr) {
		UWidget_Inventory_Base* FoundWidget = *Itr;

		FoundWidget->OnInventoryOpened(CurrentPlayerController, false);
	}
}


// ------------------------- Widget
void UWidgetComponent_Inventory_Item_Base::UpdateWidget()
{
	// Static Equipment Widgets
	if (StaticEquipmentSlot) {
		if (ItemEquipText->IsValidLowLevel())
			ItemEquipText->SetText(FText::FromString("Unequip"));

		if (ItemData.DisplayName == "Default") {
			if (ItemEquipButton->IsValidLowLevel())
				ItemEquipButton->SetIsEnabled(false);

			if (ItemNameText->IsValidLowLevel())
				ItemNameText->SetText(FText::FromString("Nothing"));
		}
		else {
			if (ItemNameText->IsValidLowLevel())
				ItemNameText->SetText(FText::FromString(ItemData.DisplayName));
			if (ItemEquipButton->IsValidLowLevel())
				ItemEquipButton->SetIsEnabled(true);
		}
	// Unequipped Item Widgets
	} else {
		if (ItemData.DisplayName == "Default")
			RemoveFromParent();
		else {
			if (ItemNameText->IsValidLowLevel())
				ItemNameText->SetText(FText::FromString(ItemData.DisplayName));
		}
	}
}