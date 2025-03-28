#include "WidgetDeckEditor.h"


#include "ActorEntityPlayer.h"
#include "Blueprint/WidgetLayoutLibrary.h"
#include "Components/UniformGridSlot.h"
#include "DragDropOperationCard.h"
#include "Kismet/GameplayStatics.h"
#include "LostWorldGameModeBase.h"
#include "LostWorldPlayerControllerBase.h"
#include "LostWorldPlayerControllerBattle.h"
#include "Types/ReflectionMetadata.h"
#include "WidgetCard.h"
#include "Widgets/SViewport.h"



class FReflectionMetaData;


bool UWidgetDeckEditor::NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation)
{
	if (Cast<ALostWorldPlayerControllerBattle>(UGameplayStatics::GetPlayerController(GetWorld(), 0))->
		ControlMode == EPlayerControlModes::DeckEditor) {
		FString GridPanel = "None";
		UWidget* DragFromWidget = Cast<UWidgetCard>(InOperation->Payload)->ParentWidget;
		UWidget* DragToWidget = nullptr;
		FCard DraggedCard = Cast<UWidgetCard>(InOperation->Payload)->CardData;
		int DraggedCardIndex = Cast<UWidgetCard>(InOperation->Payload)->IndexInGridPanel;
		
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
					}
				}
			}
		}

		// To-Do: Fix all the bugs associated with dragging and dropping cards onto other cards.
		// If the hovered widget is a card, then
		// find the index of the hovered card in the players' deck or collection.
		if (IsValid(DragToWidget)) {
			// Scenario 1: Dragging a card onto another card.
			// This inserts the dragged card into the array at the second card's index.
			if (Cast<UWidgetCard>(DragToWidget)) {
				// Clear the whole array and add elements back one-by-one.
				// Create a temporary copy of the array before clearing the original.
				
				// ReSharper disable once CppInitializedValueIsAlwaysRewritten
				int CardInArrayIndex = -1;
				TArray<FCard> ArrayCopy;
				FCard CardData = Cast<UWidgetCard>(DragToWidget)->CardData;
				
				
				if (GridPanel.Contains("Deck")) {
					ArrayCopy = PlayerEntity->EntityData.Deck;
					PlayerEntity->EntityData.Deck.Empty();
				} else if (GridPanel.Contains("Collection")) {
					ArrayCopy = PlayerEntity->EntityData.Collection;
					PlayerEntity->EntityData.Collection.Empty();
				}

				CardInArrayIndex = ArrayCopy.Find(CardData);
				

				if (CardInArrayIndex > -1 && DraggedCardIndex > -1) {
					for (int ArrayCount = 0; ArrayCount <= ArrayCopy.Num(); ArrayCount++) {
						if (GridPanel.Contains("Deck")) {
							if (ArrayCount < CardInArrayIndex) {
								PlayerEntity->EntityData.Deck.Add(ArrayCopy[ArrayCount]);
							} else if (ArrayCount == CardInArrayIndex) {
								PlayerEntity->EntityData.Deck.Add(DraggedCard);
							} else if (ArrayCount > CardInArrayIndex) {
								PlayerEntity->EntityData.Deck.Add(ArrayCopy[ArrayCount - 1]);
							}
						} else if (GridPanel.Contains("Collection")) {
							if (ArrayCount < CardInArrayIndex) {
								PlayerEntity->EntityData.Collection.Add(ArrayCopy[ArrayCount]);
							} else if (ArrayCount == CardInArrayIndex) {
								PlayerEntity->EntityData.Collection.Add(DraggedCard);
							} else if (ArrayCount > CardInArrayIndex) {
								PlayerEntity->EntityData.Collection.Add(ArrayCopy[ArrayCount - 1]);
							}
						}
					}
				
					if (GridPanel.Contains("Deck")) {
						PlayerEntity->EntityData.Collection.RemoveAt(DraggedCardIndex);
					} else if (GridPanel.Contains("Collection")) {
						PlayerEntity->EntityData.Deck.RemoveAt(DraggedCardIndex);
					}
				}

				if (CardInArrayIndex < 0) {
					ALostWorldGameModeBase::DualLog("Error! Could not get array index!", 2);

					if (PlayerEntity->EntityData.Deck.Num() < 1) {
						PlayerEntity->EntityData.Deck = ArrayCopy;
					} else if (PlayerEntity->EntityData.Collection.Num() < 1) {
						PlayerEntity->EntityData.Collection = ArrayCopy;
					}
				}

				if (DraggedCardIndex < 0) {
					ALostWorldGameModeBase::DualLog("Error! Could not get dragged card index!", 2);

					if (PlayerEntity->EntityData.Deck.Num() < 1) {
						PlayerEntity->EntityData.Deck = ArrayCopy;
					} else if (PlayerEntity->EntityData.Collection.Num() < 1) {
						PlayerEntity->EntityData.Collection = ArrayCopy;
					}
				}

			// Scenario 2: Dragging a card onto the grid panel widget.
			// Insert the card into the array at the end.	
			} else if (Cast<UScrollBox>(DragToWidget)) {
				if (DraggedCardIndex > -1) {
					if (DragFromWidget->GetName().Contains("Deck")) {
						PlayerEntity->EntityData.Deck.RemoveAt(DraggedCardIndex);
					} else if (DragFromWidget->GetName().Contains("Collection")) {
						PlayerEntity->EntityData.Collection.RemoveAt(DraggedCardIndex);
					}

					if (GridPanel.Contains("Deck")) {
						PlayerEntity->EntityData.Deck.Add(DraggedCard);
					} else if (GridPanel.Contains("Collection")) {
						PlayerEntity->EntityData.Collection.Add(DraggedCard);
					}
				} else {
					ALostWorldGameModeBase::DualLog("Error! Could not get dragged card index in array!", 2);
				}
			}
		} else {
			ALostWorldGameModeBase::DualLog("Error! Drag-to-widget is not valid!", 2);
		}

		// Refresh the widgets' grid panels.
		// When they're refreshed, each card widget should be reassigned an index within the grid panel.
		PlayerController->DeckEditorWidget->PopulateCardsInDeckUniformGridPanel(PlayerEntity->EntityData.Deck);
		PlayerController->DeckEditorWidget->PopulateCardsInCollectionUniformGridPanel(PlayerEntity->EntityData.Collection);
		

		// To-Do: Save the players' changes as well.
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
		NewCardWidget->IndexInGridPanel = CardCount;
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
		NewCardWidget->IndexInGridPanel = CardCount;
		
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
