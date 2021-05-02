#include "CardFunctions_SuddenInspiration.h"

#include "BaseClass_EntityInBattle.h"


void ACardFunctions_SuddenInspiration::RunCardAbilityFunction(FCardBase CardAbility)
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("Execute Card Function: Sudden Inspiration"));

	for (int j = 0; j < CardAbility.CurrentTargets.Num(); j++) {
		for (int i = 0; i < 2; i++) {
			if (CardAbility.CurrentTargets[j]->CardsInDeck.Num() > 0) {
				CardAbility.CurrentTargets[j]->CardsInHand.Add(CardAbility.CurrentTargets[j]->CardsInDeck[0]);

				// Set ownership
				if (!CardAbility.CurrentTargets[j]->CardsInHand[0].Owner) {
					CardAbility.CurrentTargets[j]->CardsInHand.Last().Owner = CardAbility.Controller;
					GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("Set Card Owner"));
				}
				if (!CardAbility.CurrentTargets[j]->CardsInHand[0].Controller) {
					CardAbility.CurrentTargets[j]->CardsInHand.Last().Controller = CardAbility.Controller;
					GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("Set Card Controller"));
				}

				CardAbility.CurrentTargets[j]->CardsInDeck.RemoveAt(0);
			}
			else {
				GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Orange, TEXT("Ran out of cards in deck!"));
			}
		}

		CardAbility.CurrentTargets[j]->UpdateCardIndicesInAllZones();
		CardAbility.CurrentTargets[j]->UpdateCardWidgets();
	}
}