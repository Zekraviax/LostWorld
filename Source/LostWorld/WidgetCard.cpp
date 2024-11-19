#include "WidgetCard.h"


bool UWidgetCard::NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation)
{
	return Super::NativeOnDrop(InGeometry, InDragDropEvent, InOperation);
}


void UWidgetCard::UpdateComponentsFromPassedCard(const FCard& InCard) const
{
	CardNameText->SetText(FText::FromString(InCard.DisplayName));
}
