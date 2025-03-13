#include "WidgetDeckEditor.h"


#include "ActorEntityPlayer.h"
#include "DragDropOperationCard.h"
#include "LostWorldGameModeBase.h"
#include "Components/UniformGridSlot.h"
#include "Kismet/GameplayStatics.h"
#include "LostWorldPlayerControllerBase.h"
#include "LostWorldPlayerControllerBattle.h"
#include "Types/ReflectionMetadata.h"
#include "WidgetCard.h"
#include "Widgets/SViewport.h"
#include "Blueprint/WidgetLayoutLibrary.h"


class FReflectionMetaData;

bool UWidgetDeckEditor::NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation)
{
	if (Cast<ALostWorldPlayerControllerBattle>(UGameplayStatics::GetPlayerController(GetWorld(), 0))->
		ControlMode == EPlayerControlModes::DeckEditor) {
		FString GridPanel = "None";
		UWidget* DragFromWidget = Cast<UWidgetCard>(InOperation->Payload)->ParentWidget;
		UWidget* DragToWidget = nullptr;
		FCard DraggedCard = Cast<UWidgetCard>(InOperation->Payload)->CardData;
		
		ALostWorldPlayerControllerBase* PlayerController = Cast<ALostWorldPlayerControllerBattle>(
			UGameplayStatics::GetPlayerController(GetWorld(), 0));
		AActorEntityBase* PlayerEntity = PlayerController->ControlledPlayerEntity;
		
		FWidgetPath Path = FSlateApplication::Get().LocateWindowUnderMouse(FSlateApplication::Get().GetCursorPos(),
			FSlateApplication::Get().GetInteractiveTopLevelWindows(), true);
		
		if (Path.IsValid()) {
			bool FoundRoot = false;
			for (int32 i = 0; i < Path.Widgets.Num(); i++) {
				FArrangedWidget& ArrangedWidget = Path.Widgets[i];
				TSharedRef<SWidget> Widget = ArrangedWidget.Widget;

				// If we've found a UniformGridPanel, then the widget below it should be a card.
				if (Widget->GetTypeAsString() == "SUniformGridPanel") {
					FoundRoot = true;

					// Find out which UniformGridPanel the hovered widget belongs to.
					TSharedPtr<FReflectionMetaData> Metadata = Widget->GetMetaData<FReflectionMetaData>();
					if (Metadata.IsValid() && Metadata->SourceObject.IsValid()) {
						GridPanel = Cast<UUniformGridPanel>(Metadata->SourceObject.Get())->GetName();
					}
				} else if (FoundRoot) {
					TSharedPtr<FReflectionMetaData> Metadata = Widget->GetMetaData<FReflectionMetaData>();
					if (Metadata.IsValid() && Metadata->SourceObject.IsValid()) {
						DragToWidget = Cast<UWidgetCard>(Metadata->SourceObject.Get());
						break;
					}
				} else if (Widget->GetTypeAsString() == "SScrollBox") {
					TSharedPtr<FReflectionMetaData> Metadata = Widget->GetMetaData<FReflectionMetaData>();
					if (Metadata.IsValid() && Metadata->SourceObject.IsValid()) {
						DragToWidget = Cast<UWidget>(Metadata->SourceObject.Get());
						GridPanel = DragToWidget->GetName();
						//break;
					}
				}
			}
		}

		// If the hovered widget is a card, then
		// find the index of the hovered card in the players' deck or collection.
		if (IsValid(DragToWidget)) {
			// Scenario 1: Dragging a card onto another card.
			// This inserts the dragged card into the array at the second card's index.
			/*if (Cast<UWidgetCard>(DragToWidget)) {
				FCard CardData = Cast<UWidgetCard>(DragToWidget)->CardData;
				
				if (GridPanel.Contains("Deck")) {
					int DeckIndex = PlayerEntity->EntityData.Deck.Find(CardData);

					PlayerEntity->EntityData.Collection.Remove(DraggedCard);
					PlayerEntity->EntityData.Deck.Insert(DraggedCard, DeckIndex);
				} else if (GridPanel.Contains("Collection")) {
					int DeckIndex = PlayerEntity->EntityData.Collection.Find(CardData);

					PlayerEntity->EntityData.Deck.Remove(DraggedCard);
					PlayerEntity->EntityData.Collection.Insert(DraggedCard, DeckIndex);
				}*/
			// Scenario 2: Dragging a card onto the grid panel widget.
			// Insert the card into the array at the end.	
			} if (Cast<UScrollBox>(DragToWidget)) {
				if (GridPanel.Contains("Deck")) {
					PlayerEntity->EntityData.Collection.Remove(DraggedCard);
					PlayerEntity->EntityData.Deck.Add(DraggedCard);
				} else if (GridPanel.Contains("Collection")) {
					PlayerEntity->EntityData.Deck.Remove(DraggedCard);
					PlayerEntity->EntityData.Collection.Add(DraggedCard);
				}
			}
		}

		// Refresh the widget.
		PlayerController->DeckEditorWidget->PopulateCardsInDeckUniformGridPanel(PlayerEntity->EntityData.Deck);
		PlayerController->DeckEditorWidget->PopulateCardsInCollectionUniformGridPanel(PlayerEntity->EntityData.Collection);

		// Save the players' changes as well.
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
		NewCardWidget->ParentWidget = CardsInDeckUniformGridPanel;
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
		NewCardWidget->ParentWidget = CardsInCollectionUniformGridPanel;
		
		Cast<UUniformGridSlot>(CardsInCollectionUniformGridPanel->GetChildAt(CardsInCollectionUniformGridPanel->
			GetChildrenCount() - 1)->Slot)->SetRow(Row);
		Cast<UUniformGridSlot>(CardsInCollectionUniformGridPanel->GetChildAt(CardsInCollectionUniformGridPanel->
			GetChildrenCount() - 1)->Slot)->SetColumn(Column);
	}
}


void UWidgetDeckEditor::CloseDeckEditor()
{
	Cast<ALostWorldPlayerControllerBase>(GetWorld()->GetFirstPlayerController())->ControlMode = EPlayerControlModes::LevelExploration;
	Cast<ALostWorldPlayerControllerBase>(GetWorld()->GetFirstPlayerController())->AddLevelHudToViewport();
}
