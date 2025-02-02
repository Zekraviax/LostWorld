#include "WidgetEquipmentItem.h"


void UWidgetEquipmentItem::SetDataFromPassedEquipment(const FEquipment& Equipment)
{
	EquipmentItemData = Equipment;
	
	ItemNameText->SetText(FText::FromString(Equipment.DisplayName));
}
