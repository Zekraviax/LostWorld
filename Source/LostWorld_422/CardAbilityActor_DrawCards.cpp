#include "CardAbilityActor_DrawCards.h"

#include "BaseClass_EntityInBattle.h"


void ACardAbilityActor_DrawCards::RunCardAbilityFunction()
{
	UE_LOG(LogTemp, Warning, TEXT("Execute Ability: Draw Cards"));
	int32 DrawValue = 0;
	TMap<E_Card_AbilityConditions, int32> ConditionsArray = LocalCardReference.AbilitiesAndConditions[0].AbilityConditions;

	if (ConditionsArray.Contains(E_Card_AbilityConditions::E_NumberOfCards)) {
		DrawValue = ConditionsArray.FindChecked(E_Card_AbilityConditions::E_NumberOfCards);
	}

	for (int i = 0; i < DrawValue; i++)
	{
		if (LocalCardReference.Controller->CardsInDeck.Num() > 0) {
			LocalCardReference.Controller->CardsInHand.Add(LocalCardReference.Controller->CardsInDeck[0]);

			// Set ownership
			if (!LocalCardReference.Controller->CardsInHand[0].Owner) {
				LocalCardReference.Controller->CardsInHand.Last().Owner = LocalCardReference.Controller;
				GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("Set Card Owner"));
			}
			if (!LocalCardReference.Controller->CardsInHand[0].Controller) {
				LocalCardReference.Controller->CardsInHand.Last().Controller = LocalCardReference.Controller;
				GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("Set Card Controller"));
			}

			LocalCardReference.Controller->CardsInDeck.RemoveAt(0);
		}
	}

	LocalCardReference.Controller->UpdateCardIndicesInAllZones();
	LocalCardReference.Controller->UpdateCardWidgets();
}