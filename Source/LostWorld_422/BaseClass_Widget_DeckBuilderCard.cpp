#include "BaseClass_Widget_DeckBuilderCard.h"

#include "BaseClass_PlayerController.h"


void UBaseClass_Widget_DeckBuilderCard::BindInfo()
{
	NameText->Text = FText::FromString(CardDataRef.DisplayName);
	QuantityText->Text = FText::FromString(FString::FromInt(QuantityBind));
}

void UBaseClass_Widget_DeckBuilderCard::InteractFunction()
{
	if (PlayerControllerRef && DeckBuilderWidgetRef)
	{
		switch (DeckBuilderZone)
		{
		case (E_DeckBuilder_Zone::E_Collection):
			// Add to player's deck
			PlayerControllerRef->CurrentEntityData.CurrentDeck.Add(CardDataRef);

			// Don't subtrach anything if we're using the Infinite Cards test/cheat
			if (!DeckBuilderWidgetRef->TestUnlimitedCardsMode)
			{
				QuantityBind--;

				for (int i = 0; i < PlayerControllerRef->CurrentCollection.Num(); i++) {
					if (PlayerControllerRef->CurrentCollection[i].DisplayName == CardDataRef.DisplayName) {

						PlayerControllerRef->CurrentCollection.RemoveAt(i);
						break;
					}
				}
			}
			DeckBuilderWidgetRef->PopulateScrollBoxes();
			break;
		case (E_DeckBuilder_Zone::E_Deck):
			QuantityBind--;
			// Add back into collection
			PlayerControllerRef->CurrentCollection.Add(CardDataRef);

			for (int i = 0; i < PlayerControllerRef->CurrentEntityData.CurrentDeck.Num(); i++){
				if (PlayerControllerRef->CurrentEntityData.CurrentDeck[i].DisplayName == CardDataRef.DisplayName) {
					PlayerControllerRef->CurrentEntityData.CurrentDeck.RemoveAt(i);
					break;
				}
			}

			DeckBuilderWidgetRef->PopulateScrollBoxes();
			break;
		default:
			break;
		}
	}
}