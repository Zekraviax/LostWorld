#include "CardFunctions_BloodRecycling.h"

#include "BaseClass_EntityInBattle.h"


void ACardFunctions_BloodRecycling::RunCardAbilityFunction(FStackEntry StackEntry)
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("Execute Card Function: Blood Recycling"));

	int32 DamageValue = StackEntry.Card.AbilitiesAndConditions[0].BaseDamage;
	int32 DrawValue = StackEntry.Card.AbilitiesAndConditions[0].BaseDraw;

	for (int i = 0; i < DrawValue; i++) {
		StackEntry.Card.CurrentTargets[0]->Event_DrawCard();
	}

	StackEntry.Card.CurrentTargets[0]->Event_DamageIncoming(DamageValue, StackEntry.Card.Elements[0], E_Card_DamageTypes::E_Other);
}