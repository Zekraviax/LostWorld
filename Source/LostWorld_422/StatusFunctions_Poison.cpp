#include "StatusFunctions_Poison.h"

#include "BaseClass_EntityInBattle.h"


// ------------------------- Triggered Functions
void AStatusFunctions_Poison::TriggeredFunction_StarterOfEntityTurn(ABaseClass_EntityInBattle* AffectedEntity)
{
	AffectedEntity->Event_DamageIncoming(1, E_Card_Elements::E_NonElemental, E_Card_DamageTypes::E_LifeLoss);
}