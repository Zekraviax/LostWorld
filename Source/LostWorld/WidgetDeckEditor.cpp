#include "WidgetDeckEditor.h"


#include "Components/UniformGridSlot.h"
#include "LostWorldPlayerControllerBase.h"
#include "WidgetCard.h"


void UWidgetDeckEditor::PopulateCardsInDeckUniformGridPanel(TArray<FCard> Deck) const
{
	// Clean up scroll box.
	CardsInDeckUniformGridPanel->ClearChildren();

	// For each card in the deck, create a widget and add it to the scroll box.
	// The row of the widget should be equal to the CardCount int divided by 4.
	// The column of the widget should be equal to the modulo of the CardCount int divided by 4.
	for (int CardCount = 0; CardCount < Deck.Num(); CardCount++) {
		int Row = FMath::RoundToInt(CardCount / 4);
		int Column = CardCount % 4;
		UWidgetCard* NewCardWidget = CreateWidget<UWidgetCard>(GetWorld(), CardWidgetBlueprintClass);
		
		NewCardWidget->CardData = Deck[CardCount];
		NewCardWidget->UpdateComponentsFromPassedCard(Deck[CardCount]);
		CardsInDeckUniformGridPanel->AddChild(NewCardWidget);
		
		Cast<UUniformGridSlot>(CardsInDeckUniformGridPanel->GetChildAt(CardsInDeckUniformGridPanel->
			GetChildrenCount() - 1)->Slot)->SetRow(Row);
		Cast<UUniformGridSlot>(CardsInDeckUniformGridPanel->GetChildAt(CardsInDeckUniformGridPanel->
			GetChildrenCount() - 1)->Slot)->SetColumn(Column);
	}
}


void UWidgetDeckEditor::CloseDeckEditor()
{
	Cast<ALostWorldPlayerControllerBase>(GetWorld()->GetFirstPlayerController())->AddLevelHudToViewport();
}
