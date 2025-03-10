#include "DragDropOperationCard.h"


#include "WidgetCard.h"
#include "Blueprint/SlateBlueprintLibrary.h"


void UDragDropOperationCard::Dragged_Implementation(const FPointerEvent& PointerEvent)
{
	Super::Dragged_Implementation(PointerEvent);

	// Ignore the AtoVPosition.
	// It's only there because the AbsoluteToViewport function needs it.
	FVector2D PixelPosition, AtoVPosition, ViewportDimensions;
	FVector2D ScreenSpacePosition = PointerEvent.GetScreenSpacePosition();
	USlateBlueprintLibrary::AbsoluteToViewport(Payload, ScreenSpacePosition, PixelPosition, AtoVPosition);
	GEngine->GameViewport->GetViewportSize(ViewportDimensions);

	CursorPosition.X = PixelPosition.X;
	CursorPositionAsPercentage.X = PixelPosition.X / ViewportDimensions.X;
	CursorPositionAsPercentage.Y = PixelPosition.Y / ViewportDimensions.Y;

	// To-Do: Check if the player can afford to cast the card (?)
	// AActorEntityPlayer* Player = Cast<>(GetWorld->GetAuthGameMode())

	Cast<UWidgetCard>(DefaultDragVisual)->UpdateComponentsFromPassedCard(Cast<UWidgetCard>(Payload)->CardData);
	
	if (CursorPositionAsPercentage.Y > 0.749) {
		Cast<UWidgetCard>(DefaultDragVisual)->BackgroundImage->SetColorAndOpacity(FLinearColor(0.f, 0.f, 0.f, 1.f));
	} else {
		Cast<UWidgetCard>(DefaultDragVisual)->BackgroundImage->SetColorAndOpacity(FLinearColor(1.f, 0.5f, 0.f, 1.f));
	}
}
