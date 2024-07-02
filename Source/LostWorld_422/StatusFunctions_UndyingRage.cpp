#include "StatusFunctions_UndyingRage.h"

#include "BaseClass_EntityInBattle.h"


// ------------------------- Triggered Functions
int AStatusFunctions_UndyingRage::TriggeredFunction_EntityAboutToTakeDamage(ABaseClass_EntityInBattle* AffectedEntity, int IncomingDamage)
{
	int DamageValue = IncomingDamage;

	if (DamageValue >= AffectedEntity->EntityBaseData.HealthValues.X_Value) {
		DamageValue = AffectedEntity->EntityBaseData.HealthValues.X_Value - 1;
	}

	return DamageValue;
}