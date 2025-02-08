#include "ItemFunctions_JuiceOfLife.h"

#include "BaseClass_EntityInBattle.h"


void AItemFunctions_JuiceOfLife::ActivatedFunction(ABaseClass_EntityInBattle* EquippedEntity)
{
	EquippedEntity->EntityBaseData.HealthValues.X_Value = EquippedEntity->EntityBaseData.HealthValues.Y_Value;
}