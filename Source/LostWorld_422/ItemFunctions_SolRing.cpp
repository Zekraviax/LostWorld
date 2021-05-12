#include "ItemFunctions_SolRing.h"

#include "BaseClass_EntityInBattle.h"


// ------------------------- Triggered Functions ------------------------- //
void AItemFunctions_SolRing::TriggeredFunction_OnItemEquipped(ABaseClass_EntityInBattle* EquippedEntity)
{
	EquippedEntity->EntityBaseData.ManaValues.Y_Value -= 1;

	if (EquippedEntity->EntityBaseData.ManaValues.X_Value > EquippedEntity->EntityBaseData.ManaValues.Y_Value) {
		EquippedEntity->EntityBaseData.ManaValues.X_Value = EquippedEntity->EntityBaseData.ManaValues.Y_Value;
	}
}


void AItemFunctions_SolRing::TriggeredFunction_StarterOfWearerTurn(ABaseClass_EntityInBattle* EquippedEntity)
{
	EquippedEntity->EntityBaseData.ManaValues.X_Value += 2;

	if (EquippedEntity->EntityBaseData.ManaValues.X_Value > EquippedEntity->EntityBaseData.ManaValues.Y_Value) {
		EquippedEntity->EntityBaseData.ManaValues.X_Value = EquippedEntity->EntityBaseData.ManaValues.Y_Value;
	}
}