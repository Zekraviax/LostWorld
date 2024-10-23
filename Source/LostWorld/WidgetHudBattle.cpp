#include "WidgetHudBattle.h"


#include "WidgetCard.h"


void UWidgetHudBattle::CreateCardWidgetInHand(FCard InCard)
{
	UWidgetCard* NewCardWidget = CreateWidget<UWidgetCard>(GetWorld(), CardWidgetBlueprintClass);

	// Set card UI components
	NewCardWidget->CardNameText->SetText(FText::FromString(InCard.DisplayName));

	CardsInHandScrollBox->AddChild(NewCardWidget);
}
