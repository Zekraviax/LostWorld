#include "WidgetHudBattle.h"


#include "WidgetCard.h"
#include "Blueprint/DragDropOperation.h"
#include "Kismet/GameplayStatics.h"


void UWidgetHudBattle::CreateCardWidgetInHand(const FCard& InCard) const
{
	UWidgetCard* NewCardWidget = CreateWidget<UWidgetCard>(GetWorld(), CardWidgetBlueprintClass);

	// Set card UI components
	NewCardWidget->CardNameText->SetText(FText::FromString(InCard.DisplayName));

	CardsInHandScrollBox->AddChild(NewCardWidget);
}


bool UWidgetHudBattle::NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation)
{
	// Calculate the drop position, scaled down between 0.0 and 1.0
	// In the context of the viewport, the Y axis is the up-down axis.
	float DropPositionY = InGeometry.AbsoluteToLocal(InDragDropEvent.GetScreenSpacePosition()).Y / GSystemResolution.ResY;
	
	if (DropPositionY < 0.71) {
		// CAST THAT CARD BABYYYYY
		//InOperation->Payload
	}
	// Otherwise, the drag and drop operation will cancel.
	
	return true;
}

bool UWidgetHudBattle::NativeOnDragOver(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation)
{
	return Super::NativeOnDragOver(InGeometry, InDragDropEvent, InOperation);
}