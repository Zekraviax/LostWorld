#include "WidgetDeckEditor.h"


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
		int HoveredSlotIndex = -1;
		FString GridPanel = "None";
		UWidgetCard* SourceWidget = nullptr;
		
		FWidgetPath Path = FSlateApplication::Get().LocateWindowUnderMouse(FSlateApplication::Get().GetCursorPos(),
			FSlateApplication::Get().GetInteractiveTopLevelWindows(), true);
		
		if (Path.IsValid()) {
			bool FoundRoot = false;
			for ( int32 i = 0; i < Path.Widgets.Num(); ++i )
			{
				FArrangedWidget& ArrangedWidget = Path.Widgets[ i ];
				TSharedRef<SWidget> Widget = ArrangedWidget.Widget;

				if ( Widget->GetTypeAsString() == "SUniformGridPanel" ) {
					FoundRoot = true;
				} else if ( FoundRoot ) {
					TSharedPtr<FReflectionMetaData> metadata = Widget->GetMetaData<FReflectionMetaData>();
					if (metadata.IsValid() && metadata->SourceObject.IsValid()) {
						SourceWidget = Cast<UWidgetCard>(metadata->SourceObject.Get());
						ALostWorldGameModeBase::DualLog("Found card: ", 3);
						break;
					}
				}
			}
		}

		if (HoveredSlotIndex != -1) {
		
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
	Cast<ALostWorldPlayerControllerBase>(GetWorld()->GetFirstPlayerController())->ControlMode = EPlayerControlModes::LevelExploration;
	Cast<ALostWorldPlayerControllerBase>(GetWorld()->GetFirstPlayerController())->AddLevelHudToViewport();
}
