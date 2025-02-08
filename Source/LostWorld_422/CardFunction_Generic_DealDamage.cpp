#include "CardFunction_Generic_DealDamage.h"

#include "BaseClass_EntityInBattle.h"


void ACardFunction_Generic_DealDamage::RunCardAbilityFunction(FStackEntry StackEntry)
{
	int32 DamageValue = StackEntry.Card.AbilitiesAndConditions[0].CalculatedDamage;

	for (int i = 0; i < StackEntry.Card.CurrentTargets.Num(); i++) {
		Cast<ABaseClass_EntityInBattle>(StackEntry.Card.CurrentTargets[i])->Event_DamageIncoming(DamageValue, StackEntry.Card.Elements[0], StackEntry.Card.AbilitiesAndConditions[0].DamageType);
	}
}