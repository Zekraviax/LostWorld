#include "WidgetHudBattle.h"


#include "DragDropOperationCard.h"
#include "LostWorldGameModeBattle.h"
#include "WidgetCard.h"


bool UWidgetHudBattle::NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation)
{
	Super::NativeOnDrop(InGeometry, InDragDropEvent, InOperation);
	
	// Calculate the drop position, scaled down between 0.0 and 1.0
	// In the context of the viewport, the Y axis is the up-down axis.
	float DropPositionY = Cast<UDragDropOperationCard>(InOperation)->CursorPositionAsPercentage.Y;
	
	if (DropPositionY < 0.75) {
		// CAST THAT CARD BABYYYYY
		Cast<ALostWorldGameModeBattle>(GetWorld()->GetAuthGameMode())->GetTargetsForCard(Cast<UWidgetCard>(InOperation->Payload)->IndexInHandArray);
	}
	// Otherwise, the drag and drop operation will cancel.
	
	return true;
}


UWidgetCard* UWidgetHudBattle::CreateCardWidgetInHand(const FCard& InCard) const
{
	UWidgetCard* NewCardWidget = CreateWidget<UWidgetCard>(GetWorld(), CardWidgetBlueprintClass);

	// Set card UI components
	NewCardWidget->CardNameText->SetText(FText::FromString(InCard.DisplayName));
	CardsInHandScrollBox->AddChild(NewCardWidget);

	return NewCardWidget;
}