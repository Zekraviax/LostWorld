#include "WidgetDeckEditor.h"


#include "DragDropOperationCard.h"
#include "Components/UniformGridSlot.h"
#include "Kismet/GameplayStatics.h"
#include "LostWorldPlayerControllerBase.h"
#include "LostWorldPlayerControllerBattle.h"
#include "WidgetCard.h"
#include "Components/CanvasPanelSlot.h"


bool UWidgetDeckEditor::NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation)
{
	if (Cast<ALostWorldPlayerControllerBattle>(UGameplayStatics::GetPlayerController(GetWorld(), 0))->
		ControlMode == EPlayerControlModes::DeckEditor) {
		bool FoundHoveredSlot = false;
		int HoveredSlotIndex = -1;
		
		// Check if the cursor is within the bounds of each slot of both of the grid panels.
		for (int SlotCount = 0; SlotCount < CardsInDeckUniformGridPanel->GetSlots().Num(); SlotCount++) {
			if (Cast<UCanvasPanelSlot>(CardsInDeckUniformGridPanel->GetSlots()[SlotCount])->GetPosition().X >=
				Cast<UDragDropOperationCard>(InOperation)->CursorPosition.X &&
				Cast<UCanvasPanelSlot>(CardsInDeckUniformGridPanel->GetSlots()[SlotCount])->GetPosition().Y <=
				Cast<UDragDropOperationCard>(InOperation)->CursorPosition.Y &&
				!FoundHoveredSlot) {
				FoundHoveredSlot = true;
				HoveredSlotIndex = SlotCount;
			}
		}

		for (int SlotCount = 0; SlotCount < CardsInCollectionUniformGridPanel->GetSlots().Num(); SlotCount++) {
			if (Cast<UCanvasPanelSlot>(CardsInCollectionUniformGridPanel->GetSlots()[SlotCount])->GetPosition().X >=
				Cast<UDragDropOperationCard>(InOperation)->CursorPosition.X &&
				Cast<UCanvasPanelSlot>(CardsInCollectionUniformGridPanel->GetSlots()[SlotCount])->GetPosition().Y <=
				Cast<UDragDropOperationCard>(InOperation)->CursorPosition.Y &&
				!FoundHoveredSlot) {
				FoundHoveredSlot = true;
				HoveredSlotIndex = SlotCount;
			}
		}
	}

	return Super::NativeOnDrop(InGeometry, InDragDropEvent, InOperation);
}


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


void UWidgetDeckEditor::PopulateCardsInCollectionUniformGridPanel(TArray<FCard> Collection) const
{
	// Clean up scroll box.
	CardsInCollectionUniformGridPanel->ClearChildren();

	// For each card in the deck, create a widget and add it to the scroll box.
	// The row of the widget should be equal to the CardCount int divided by 4.
	// The column of the widget should be equal to the modulo of the CardCount int divided by 4.
	for (int CardCount = 0; CardCount < Collection.Num(); CardCount++) {
		int Row = FMath::RoundToInt(CardCount / 4);
		int Column = CardCount % 4;
		UWidgetCard* NewCardWidget = CreateWidget<UWidgetCard>(GetWorld(), CardWidgetBlueprintClass);
		
		NewCardWidget->CardData = Collection[CardCount];
		NewCardWidget->UpdateComponentsFromPassedCard(Collection[CardCount]);
		CardsInCollectionUniformGridPanel->AddChild(NewCardWidget);
		
		Cast<UUniformGridSlot>(CardsInCollectionUniformGridPanel->GetChildAt(CardsInCollectionUniformGridPanel->
			GetChildrenCount() - 1)->Slot)->SetRow(Row);
		Cast<UUniformGridSlot>(CardsInCollectionUniformGridPanel->GetChildAt(CardsInCollectionUniformGridPanel->
			GetChildrenCount() - 1)->Slot)->SetColumn(Column);
	}
}


void UWidgetDeckEditor::CloseDeckEditor()
{
	Cast<ALostWorldPlayerControllerBase>(GetWorld()->GetFirstPlayerController())->AddLevelHudToViewport();
}
