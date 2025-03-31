#include "InterfaceEntity.h"


bool IInterfaceEntity::OverrideHp(int InHp)
{
	return true;
}


bool IInterfaceEntity::CalculateTotalStats()
{
	return true;
}


bool IInterfaceEntity::EquipItem(int IndexInInventoryArray)
{
	return true;
}


bool IInterfaceEntity::UnequipItem(int IndexInEquipmentArray)
{
	return true;
}
