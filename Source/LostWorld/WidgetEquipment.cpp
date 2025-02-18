#include "WidgetEquipment.h"


#include "LostWorldGameInstanceBase.h"
#include "Components/TextBlock.h"
#include "LostWorldPlayerControllerBase.h"
#include "WidgetEquipmentItem.h"


void UWidgetEquipment::PopulateEquippedItemsScrollBox(TArray<FEquipment> EquippedItems) const
{
	EquippedItemsScrollBox->ClearChildren();
	
	for (FEquipment EquippedItem : EquippedItems) {
		UWidgetEquipmentItem* EquipmentItemWidget = CreateWidget<UWidgetEquipmentItem>(
			GetWorld(), EquipmentItemWidgetBlueprintClass);

		EquipmentItemWidget->SetDataFromPassedEquipment(EquippedItem);
		EquipmentItemWidget->IndexInArray = EquippedItems.Find(EquippedItem);
		EquipmentItemWidget->EquipUnequipText->SetText(FText::FromString("Remove"));

		EquippedItemsScrollBox->AddChild(EquipmentItemWidget);
	}
}


void UWidgetEquipment::PopulateUnequippedItemsScrollBox(TArray<FEquipment> UnequippedItems) const
{
	UnequippedItemsScrollBox->ClearChildren();
	
	for (FEquipment UnequippedItem : UnequippedItems) {
		UWidgetEquipmentItem* EquipmentItemWidget = CreateWidget<UWidgetEquipmentItem>(
			GetWorld(), EquipmentItemWidgetBlueprintClass);

		EquipmentItemWidget->SetDataFromPassedEquipment(UnequippedItem);
		EquipmentItemWidget->EquipUnequipText->SetText(FText::FromString("Equip"));

		UnequippedItemsScrollBox->AddChild(EquipmentItemWidget);
	}
}


void UWidgetEquipment::CloseEquipmentWidget()
{
	Cast<ULostWorldGameInstanceBase>(GetWorld()->GetGameInstance())->SavePlayerActorDataToJson();
	Cast<ALostWorldPlayerControllerBase>(GetWorld()->GetFirstPlayerController())->AddLevelHudToViewport();
}
