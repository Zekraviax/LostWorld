#include "CardFunctions_SuddenInspiration.h"

#include "BaseClass_EntityInBattle.h"


void ACardFunctions_SuddenInspiration::RunCardAbilityFunction(FStackEntry StackEntry)
{
	int DrawValue = StackEntry.Card.AbilitiesAndConditions[0].BaseDraw;

	for (int i = 0; i < DrawValue; i++) {
		Cast<ABaseClass_EntityInBattle>(StackEntry.Card.CurrentTargets[0])->Event_DrawCard();
	}
}