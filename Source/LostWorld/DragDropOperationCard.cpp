#include "DragDropOperationCard.h"


#include "LostWorldGameModeBase.h"
#include "Blueprint/SlateBlueprintLibrary.h"


void UDragDropOperationCard::Dragged_Implementation(const FPointerEvent& PointerEvent)
{
	Super::Dragged_Implementation(PointerEvent);

	ScreenSpacePosition = PointerEvent.GetScreenSpacePosition();
	FVector2D ViewportPosition, AbsolutePosition, PixelPosition, AtoVPosition, ViewportDimensions;
	USlateBlueprintLibrary::ScreenToViewport(Payload, ScreenSpacePosition, ViewportPosition);
	USlateBlueprintLibrary::ScreenToWidgetAbsolute(Payload, ScreenSpacePosition, AbsolutePosition, false);
	USlateBlueprintLibrary::AbsoluteToViewport(Payload, ScreenSpacePosition, PixelPosition, AtoVPosition);
	GEngine->GameViewport->GetViewportSize(ViewportDimensions);
	
	ALostWorldGameModeBase::DualLog("Viewport Dimension " + FString::SanitizeFloat(ViewportDimensions.Y));
	
	ALostWorldGameModeBase::DualLog("Screen " + FString::SanitizeFloat(ScreenSpacePosition.Y));
	ALostWorldGameModeBase::DualLog("Absolute: " + FString::SanitizeFloat(AbsolutePosition.Y));
	ALostWorldGameModeBase::DualLog("Viewport " + FString::SanitizeFloat(ViewportPosition.Y));
	ALostWorldGameModeBase::DualLog("Pixel " + FString::SanitizeFloat(PixelPosition.Y));  // THIS ONE!
	ALostWorldGameModeBase::DualLog("A to V " + FString::SanitizeFloat(AtoVPosition.Y));
}
