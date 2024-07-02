#include "CardFunctions_Shock.h"

#include "BaseClass_EntityInBattle.h"


void ACardFunctions_Shock::RunCardAbilityFunction(FStackEntry StackEntry)
{
	int32 DamageValue = StackEntry.Card.AbilitiesAndConditions[0].CalculatedDamage;

	Cast<ABaseClass_EntityInBattle>(StackEntry.Card.CurrentTargets[0])->Event_DamageIncoming(DamageValue, StackEntry.Card.Elements[0], StackEntry.Card.AbilitiesAndConditions[0].DamageType);
}