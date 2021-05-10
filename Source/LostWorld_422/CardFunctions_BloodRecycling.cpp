#include "CardFunctions_BloodRecycling.h"

#include "BaseClass_EntityInBattle.h"


void ACardFunctions_BloodRecycling::RunCardAbilityFunction(FStackEntry StackEntry)
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("Execute Card Function: Blood Recycling"));

	int32 DamageValue = 2;

	for (int i = 0; i < 2; i++) {
		if (StackEntry.Card.CurrentTargets[0]->CardsInDeck.Num() > 0) {
			StackEntry.Card.CurrentTargets[0]->CardsInHand.Add(StackEntry.Card.CurrentTargets[0]->CardsInDeck[0]);

			// Set ownership
			if (!StackEntry.Card.CurrentTargets[0]->CardsInHand[0].Owner) {
				StackEntry.Card.CurrentTargets[0]->CardsInHand.Last().Owner = StackEntry.Card.Controller;
				GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("Set Card Owner"));
			}
			if (!StackEntry.Card.CurrentTargets[0]->CardsInHand[0].Controller) {
				StackEntry.Card.CurrentTargets[0]->CardsInHand.Last().Controller = StackEntry.Card.Controller;
				GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("Set Card Controller"));
			}

			StackEntry.Card.CurrentTargets[0]->CardsInDeck.RemoveAt(0);
		}
		else {
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Orange, TEXT("Ran out of cards in deck!"));
		}
	}

	int32 OldHealthValue = StackEntry.Card.CurrentTargets[0]->EntityBaseData.HealthValues.X_Value;
	//StackEntry.Card.CurrentTargets[0]->EntityBaseData.HealthValues.X_Value -= DamageValue;
	StackEntry.Card.CurrentTargets[0]->Event_DamageIncoming(DamageValue, StackEntry.Card.Elements[0], E_Card_DamageTypes::E_Other);

	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, (TEXT("Target: " + StackEntry.Card.CurrentTargets[0]->EntityBaseData.DisplayName)));
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, (TEXT("Damage: " + FString::FromInt(DamageValue) + "  /  New Health Value: " + FString::FromInt(StackEntry.Card.CurrentTargets[0]->EntityBaseData.HealthValues.X_Value) + "  /  Old Health Value: " + FString::FromInt(OldHealthValue))));

	StackEntry.Card.CurrentTargets[0]->UpdateCardIndicesInAllZones();
	StackEntry.Card.CurrentTargets[0]->UpdateCardWidgets();
}