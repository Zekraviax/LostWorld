#include "WidgetComponent_Inventory_Item_Base.h"

#include "BaseClass_PlayerController.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "WidgetComponent_Description.h"
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

			// If a valid equip slot has been found...
			if (ItemData.EquipSlots.Contains(FoundWidget->StaticEquipmentSlotType)) {
				// Unequip the currently equipped item, if there is one equipped
				FoundWidget->ItemData = ItemData;
				CurrentPlayerController->PlayerInventory.Remove(ItemData);
				CurrentPlayerController->EntityInBattleRef->EquippedItems.Add(ItemData);

				// Run item equip function
				AItemFunctions_BaseClass* ItemAbilityActor_Reference = GetWorld()->SpawnActor<AItemFunctions_BaseClass>(ItemData.Functions, FVector::ZeroVector, FRotator::ZeroRotator, SpawnParameters);
				
				if (ItemAbilityActor_Reference) {
					ItemAbilityActor_Reference->TriggeredFunction_OnItemEquipped(CurrentPlayerController->EntityInBattleRef);
					ItemAbilityActor_Reference->ConditionalBeginDestroy();
				}

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
	} else if (ItemEquipText->GetText().ToString() == "Activate") {

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
		if (ItemEquipText->IsValidLowLevel()) {
			if (!ItemEquipText->GetText().EqualTo(FText::FromString("Activate"))) {
				ItemEquipText->SetText(FText::FromString("Unequip"));
			}
		}

		if (ItemData.DisplayName == "Default") {
			if (ItemEquipButton->IsValidLowLevel()) {
				ItemEquipButton->SetIsEnabled(false);
			}

			if (ItemNameText->IsValidLowLevel()) {
				ItemNameText->SetText(FText::FromString("Nothing"));
			}
		} else {
			if (ItemNameText->IsValidLowLevel()) {
				ItemNameText->SetText(FText::FromString(ItemData.DisplayName));
			}

			if (ItemEquipButton->IsValidLowLevel()) {
				ItemEquipButton->SetIsEnabled(true);
			}
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

	// Hide description widgets
	OnMouseHoverOverEnd();
}


void UWidgetComponent_Inventory_Item_Base::OnMouseHoverOverBegin()
{
	// Put together the description text
	FString DescriptionTextAsString;

	DescriptionTextAsString.Append("Name: " + ItemData.DisplayName + "\n");
	DescriptionTextAsString.Append("Description: " + ItemData.Description.Replace(TEXT("/n"), TEXT("\n")));

	// Find a pre-existing description widget
	// If there is none, create one
	TArray<UUserWidget*> DescriptionWidgets;
	UWidgetBlueprintLibrary::GetAllWidgetsOfClass(GetWorld(), DescriptionWidgets, UWidgetComponent_Description::StaticClass(), false);
	UWidgetComponent_Description* DescriptionWidget = nullptr;

	if (DescriptionWidgets.Num() < 1) {
		if (DescriptionWidgetBlueprintClass) {
			DescriptionWidget = CreateWidget<UWidgetComponent_Description>(GetWorld(), DescriptionWidgetBlueprintClass);

			DescriptionWidget->AddToViewport();
		} else {
			UE_LOG(LogTemp, Warning, TEXT("UWidgetComponent_Inventory_Item_Base / OnMouseHoverOverBegin / Error: DescriptionWidgetBlueprintClass is not valid."));
		}
	} else {
		DescriptionWidget = Cast<UWidgetComponent_Description>(DescriptionWidgets[0]);

		DescriptionWidget->SetVisibility(ESlateVisibility::HitTestInvisible);
	}

	if (DescriptionWidget) {
		DescriptionWidget->SetDescriptionText(DescriptionTextAsString);
	} else {
		UE_LOG(LogTemp, Warning, TEXT("UWidgetComponent_Inventory_Item_Base / OnMouseHoverOverBegin / Error: DescriptionWidget is not valid."));
	}
}


void UWidgetComponent_Inventory_Item_Base::OnMouseHoverOverEnd()
{
	TArray<UUserWidget*> DescriptionWidgets;
	UWidgetBlueprintLibrary::GetAllWidgetsOfClass(GetWorld(), DescriptionWidgets, UWidgetComponent_Description::StaticClass(), false);

	if (DescriptionWidgets.Num() > 0) {
		DescriptionWidgets[0]->SetVisibility(ESlateVisibility::Collapsed);
	}
}