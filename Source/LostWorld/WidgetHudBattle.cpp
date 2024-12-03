#include "WidgetHudBattle.h"


#include "ActorEntityPlayer.h"
#include "DragDropOperationCard.h"
#include "LostWorldGameModeBattle.h"
#include "LostWorldPlayerControllerBattle.h"
#include "WidgetCard.h"
#include "Kismet/GameplayStatics.h"


bool UWidgetHudBattle::NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation)
{
	Super::NativeOnDrop(InGeometry, InDragDropEvent, InOperation);

	if (Cast<ALostWorldPlayerControllerBattle>(UGameplayStatics::GetPlayerController(GetWorld(), 0))->ControlMode == EPlayerControlModes::Battle) {
		// Calculate the drop position, scaled down between 0.0 and 1.0
		// In the context of the viewport, the Y axis is the up-down axis.
		float DropPositionY = Cast<UDragDropOperationCard>(InOperation)->CursorPositionAsPercentage.Y;
	
		if (DropPositionY < 0.75) {
			// CAST THAT CARD BABYYYYY
			Cast<ALostWorldGameModeBattle>(GetWorld()->GetAuthGameMode())->GetTargetsForCard(Cast<UWidgetCard>(InOperation->Payload)->IndexInHandArray);
		}
		// Otherwise, the drag and drop operation will cancel.
	}

	return true;
}


UWidgetCard* UWidgetHudBattle::CreateCardWidgetInHand(const FCard& InCard) const
{
	UWidgetCard* NewCardWidget = CreateWidget<UWidgetCard>(GetWorld(), CardWidgetBlueprintClass);

	// Set card UI components
	NewCardWidget->UpdateComponentsFromPassedCard(InCard);
	CardsInHandScrollBox->AddChild(NewCardWidget);

	return NewCardWidget;
}


void UWidgetHudBattle::PlayerStartCastingCard(const FCard& InCard, ECardFunctions CurrentFunction, int CurrentNumberOfTargets) const
{
	if (Cast<AActorEntityPlayer>(Cast<ALostWorldGameModeBattle>(GetWorld()->GetAuthGameMode())->TurnQueue[0])) {
		if (Cast<ALostWorldPlayerControllerBattle>(UGameplayStatics::GetPlayerController(GetWorld(), 0))->ControlMode != EPlayerControlModes::None) {
			// Display a copy of the card the player is in the middle of casting
			CurrentCardBeingCast->SetVisibility(ESlateVisibility::HitTestInvisible);
			CurrentCardBeingCast->UpdateComponentsFromPassedCard(InCard);
				
			// Update the helper text that tells the player which entities they can select
			// and how many entities they're already selected (if the card allows selecting more than one.)
			switch (CurrentFunction) {
				case ECardFunctions::TestFunctionOne:
					CardTargetText->SetVisibility(ESlateVisibility::HitTestInvisible);
					CardTargetText->SetText(FText::FromString("Select 1 Enemy"));
					break;
				case ECardFunctions::TestFunctionTwo:
					break;
				default:
					break;
			}
		}
	}
}


void UWidgetHudBattle::PlayerFinishCastingCard(int IndexInHand) const
{
	CurrentCardBeingCast->SetVisibility(ESlateVisibility::Collapsed);
	CardTargetText->SetVisibility(ESlateVisibility::Collapsed);

	// Remove the card from the HUD.
	CardsInHandScrollBox->RemoveChildAt(IndexInHand - 1);
}
