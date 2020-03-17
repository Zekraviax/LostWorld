#include "CardAbilityActor_DrawCards.h"

#include "BaseClass_EntityInBattle.h"


void ACardAbilityActor_DrawCards::RunCardAbilityFunction(FCardBase CardAbility)
{
	//UE_LOG(LogTemp, Warning, TEXT("Execute Ability: Draw Cards"));
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("Execute Ability: Draw Cards"));
	//LocalAbilityReference = CardAbility;

	int32 DrawValue = 0;
	TMap<E_Card_AbilityConditions, int32> ConditionsArray = CardAbility.AbilitiesAndConditions[0].AbilityConditions;

	if (ConditionsArray.Contains(E_Card_AbilityConditions::E_NumberOfCards)) {
		DrawValue = ConditionsArray.FindChecked(E_Card_AbilityConditions::E_NumberOfCards);
	}

	for (int i = 0; i < DrawValue; i++)
	{
		if (CardAbility.Controller->CardsInDeck.Num() > 0) {
			CardAbility.Controller->CardsInHand.Add(CardAbility.Controller->CardsInDeck[0]);

			// Set ownership
			if (!CardAbility.Controller->CardsInHand[0].Owner) {
				CardAbility.Controller->CardsInHand.Last().Owner = CardAbility.Controller;
				GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("Set Card Owner"));
			}
			if (!CardAbility.Controller->CardsInHand[0].Controller) {
				CardAbility.Controller->CardsInHand.Last().Controller = CardAbility.Controller;
				GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("Set Card Controller"));
			}

			CardAbility.Controller->CardsInDeck.RemoveAt(0);
		} else {
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Orange, TEXT("Ran out of cards in deck!"));
		}
	}

	CardAbility.Controller->UpdateCardIndicesInAllZones();
	CardAbility.Controller->UpdateCardWidgets();
}