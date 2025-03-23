#include "DragDropOperationCard.h"


#include "ActorEntityPlayer.h"
#include "Blueprint/SlateBlueprintLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "LostWorldGameModeBattle.h"
#include "LostWorldPlayerControllerBattle.h"
#include "WidgetCard.h"


void UDragDropOperationCard::Dragged_Implementation(const FPointerEvent& PointerEvent)
{
	Super::Dragged_Implementation(PointerEvent);

	// Ignore the AtoVPosition, it's only there because the AbsoluteToViewport function needs it.
	FVector2D PixelPosition, AtoVPosition, ViewportDimensions;
	FVector2D ScreenSpacePosition = PointerEvent.GetScreenSpacePosition();
	USlateBlueprintLibrary::AbsoluteToViewport(Payload, ScreenSpacePosition, PixelPosition, AtoVPosition);
	GEngine->GameViewport->GetViewportSize(ViewportDimensions);

	CursorPosition.X = PixelPosition.X;
	CursorPositionAsPercentage.X = PixelPosition.X / ViewportDimensions.X;
	CursorPositionAsPercentage.Y = PixelPosition.Y / ViewportDimensions.Y;

	Cast<UWidgetCard>(DefaultDragVisual)->UpdateComponentsFromPassedCard(Cast<UWidgetCard>(Payload)->CardData);
	
	// To-Do: Find an alternative way of getting the world context.
	UWorld* World = GEngine->GameViewport->GetWorld();
	ALostWorldPlayerControllerBase* PlayerController = Cast<ALostWorldPlayerControllerBattle>(
		UGameplayStatics::GetPlayerController(World, 0));
	AActorEntityPlayer* PlayerEntity = PlayerController->ControlledPlayerEntity;
	
	// Check if the player can afford to cast the card, if it's their turn, and if they're not in the deck editor.
	if (PlayerController->ControlMode != EPlayerControlModes::DeckEditor) {
		if (PlayerEntity->EntityData.BaseStats.CurrentManaPoints < Cast<UWidgetCard>(Payload)->CardData.TotalCost ||
			Cast<ALostWorldGameModeBattle>(World->GetAuthGameMode())->TurnQueue[0] != PlayerEntity)  {
			Cast<UWidgetCard>(DefaultDragVisual)->BackgroundImage->SetColorAndOpacity(FLinearColor(1.f, 0.f, 0.f, 1.f));
		} else {
			if (CursorPositionAsPercentage.Y < 0.749) {
				Cast<UWidgetCard>(DefaultDragVisual)->BackgroundImage->SetColorAndOpacity(FLinearColor(1.f, 0.5f, 0.f, 1.f));
			} else {
				Cast<UWidgetCard>(DefaultDragVisual)->BackgroundImage->SetColorAndOpacity(FLinearColor(0.f, 0.f, 0.f, 1.f));
			}
		}
	} else {
		Cast<UWidgetCard>(DefaultDragVisual)->BackgroundImage->SetColorAndOpacity(FLinearColor(0.f, 0.f, 0.f, 1.f));
	}
}
