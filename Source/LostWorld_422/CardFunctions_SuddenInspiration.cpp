#include "CardFunctions_SuddenInspiration.h"

#include "BaseClass_EntityInBattle.h"


void ACardFunctions_SuddenInspiration::RunCardAbilityFunction(FStackEntry StackEntry)
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("Execute Card Function: Sudden Inspiration"));

	int DrawValue = StackEntry.Card.AbilitiesAndConditions[0].BaseDraw;

	for (int i = 0; i < DrawValue; i++) {
		StackEntry.Card.CurrentTargets[0]->Event_DrawCard();
	}
}