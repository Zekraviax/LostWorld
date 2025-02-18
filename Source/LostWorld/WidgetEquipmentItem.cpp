#include "WidgetEquipmentItem.h"

#include "ActorEntityBase.h"
#include "ActorEntityPlayer.h"
#include "InterfaceEntity.h"
#include "LostWorldPlayerControllerBase.h"
#include "WidgetEquipment.h"


void UWidgetEquipmentItem::SetDataFromPassedEquipment(const FEquipment& Equipment)
{
	EquipmentItemData = Equipment;
	
	ItemNameText->SetText(FText::FromString(Equipment.DisplayName));
}


void UWidgetEquipmentItem::OnEquipmentButtonPressed()
{
	AActorEntityPlayer* PlayerEntityReference = Cast<ALostWorldPlayerControllerBase>(
		GetWorld()->GetFirstPlayerController())->ControlledPlayerEntity;
	ALostWorldPlayerControllerBase* PlayerControllerReference = Cast<ALostWorldPlayerControllerBase>(
		GetWorld()->GetFirstPlayerController());
	
	if (EquipUnequipText->Text.EqualTo(FText::FromString("Equip"))) {
		Cast<IInterfaceEntity>(PlayerEntityReference)->EquipItem(IndexInArray);
	} else if (EquipUnequipText->Text.EqualTo(FText::FromString("Remove"))) {
		Cast<IInterfaceEntity>(PlayerEntityReference)->UnequipItem(IndexInArray);
	}

	PlayerControllerReference->EquipmentWidget->
		PopulateEquippedItemsScrollBox(PlayerEntityReference->EntityData.EquippedItems);
	PlayerControllerReference->EquipmentWidget->
		PopulateUnequippedItemsScrollBox(PlayerEntityReference->EntityData.EquipmentInventory);

	// To-Do: Save the player's data when an item is equipped or removed.
}
