#include "WidgetHudBattle.h"


#include "LostWorldGameModeBase.h"
#include "WidgetCard.h"
#include "Kismet/GameplayStatics.h"


void UWidgetHudBattle::CreateCardWidgetInHand(FCard InCard)
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
	float ViewportSizeY = GSystemResolution.ResY;
	float CursorPositionY = InGeometry.AbsoluteToLocal(InDragDropEvent.GetScreenSpacePosition()).Y;
	
	float DropPositionY = CursorPositionY / ViewportSizeY;
	Cast<ALostWorldGameModeBase>(GetWorld()->GetAuthGameMode())->DualLog("Cursor Position Y: " + FString::SanitizeFloat(CursorPositionY));
	Cast<ALostWorldGameModeBase>(GetWorld()->GetAuthGameMode())->DualLog("Viewport Size Y: " + FString::SanitizeFloat(ViewportSizeY));
	Cast<ALostWorldGameModeBase>(GetWorld()->GetAuthGameMode())->DualLog("Drop Position Y: " + FString::SanitizeFloat(DropPositionY));

	if (DropPositionY < 0.71) {
		// CAST THAT CARD BABYYYYY
	}
	// Otherwise, the drag and drop operation will cancel.
	
	return true;
}
