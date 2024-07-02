#include "StatusFunctions_MuscleMass.h"

#include "BaseClass_EntityInBattle.h"


// ------------------------- Passive Functions
void AStatusFunctions_MuscleMass::PassiveFunction_OnStatusEffectBegin(ABaseClass_EntityInBattle * AffectedEntity)
{
	AffectedEntity->EntityBaseData.CoreStats.Strength += 1;
	AffectedEntity->EntityBaseData.CoreStats.Constitution += 1;

	AffectedEntity->Event_StatsChanged();
}


void AStatusFunctions_MuscleMass::PassiveFunction_OnStatusEffectEnd(ABaseClass_EntityInBattle * AffectedEntity)
{
	AffectedEntity->EntityBaseData.CoreStats.Strength -= 1;
	AffectedEntity->EntityBaseData.CoreStats.Constitution -= 1;

	AffectedEntity->Event_StatsChanged();
}