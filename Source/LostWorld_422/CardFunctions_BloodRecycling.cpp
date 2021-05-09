#include "CardFunctions_BloodRecycling.h"

#include "BaseClass_EntityInBattle.h"


void ACardFunctions_BloodRecycling::RunCardAbilityFunction(FStackEntry StackEntry)
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("Execute Card Function: Blood Recycling"));

	int32 DamageValue = 2;

	for (int j = 0; j < StackEntry.Card.CurrentTargets.Num(); j++) {
		for (int i = 0; i < 2; i++) {
			if (StackEntry.Card.CurrentTargets[j]->CardsInDeck.Num() > 0) {
				StackEntry.Card.CurrentTargets[j]->CardsInHand.Add(StackEntry.Card.CurrentTargets[j]->CardsInDeck[0]);

				// Set ownership
				if (!StackEntry.Card.CurrentTargets[j]->CardsInHand[0].Owner) {
					StackEntry.Card.CurrentTargets[j]->CardsInHand.Last().Owner = StackEntry.Card.Controller;
					GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("Set Card Owner"));
				}
				if (!StackEntry.Card.CurrentTargets[j]->CardsInHand[0].Controller) {
					StackEntry.Card.CurrentTargets[j]->CardsInHand.Last().Controller = StackEntry.Card.Controller;
					GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("Set Card Controller"));
				}

				StackEntry.Card.CurrentTargets[j]->CardsInDeck.RemoveAt(0);
			}
			else {
				GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Orange, TEXT("Ran out of cards in deck!"));
			}
		}

		int32 OldHealthValue = StackEntry.Card.CurrentTargets[j]->EntityBaseData.HealthValues.X_Value;
		StackEntry.Card.CurrentTargets[j]->EntityBaseData.HealthValues.X_Value -= DamageValue;

		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, (TEXT("Target: " + StackEntry.Card.CurrentTargets[j]->EntityBaseData.DisplayName)));
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, (TEXT("Damage: " + FString::FromInt(DamageValue) + "  /  New Health Value: " + FString::FromInt(StackEntry.Card.CurrentTargets[j]->EntityBaseData.HealthValues.X_Value) + "  /  Old Health Value: " + FString::FromInt(OldHealthValue))));

		StackEntry.Card.CurrentTargets[j]->UpdateCardIndicesInAllZones();
		StackEntry.Card.CurrentTargets[j]->UpdateCardWidgets();
	}
}