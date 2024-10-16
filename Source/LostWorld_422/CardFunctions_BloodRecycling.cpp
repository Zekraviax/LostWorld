#include "CardFunctions_BloodRecycling.h"

#include "BaseClass_EntityInBattle.h"


void ACardFunctions_BloodRecycling::RunCardAbilityFunction(FStackEntry StackEntry)
{
	int32 DamageValue = StackEntry.Card.AbilitiesAndConditions[0].BaseDamage;
	int32 DrawValue = StackEntry.Card.AbilitiesAndConditions[0].BaseDraw;

	for (int i = 0; i < DrawValue; i++) {
		Cast<ABaseClass_EntityInBattle>(StackEntry.Card.CurrentTargets[0])->Event_DrawCard();
	}

	Cast<ABaseClass_EntityInBattle>(StackEntry.Card.CurrentTargets[0])->Event_DamageIncoming(DamageValue, StackEntry.Card.Elements[0], StackEntry.Card.AbilitiesAndConditions[0].DamageType);
}