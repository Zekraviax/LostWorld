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

	if (Cast<ALostWorldPlayerControllerBattle>(UGameplayStatics::GetPlayerController(GetWorld(), 0))->
		ControlMode == EPlayerControlModes::Battle) {
		// Calculate the drop position scaled down to between 0.0 and 1.0
		// In the context of the viewport, the Y axis is the up-down axis.
		float DropPositionY = Cast<UDragDropOperationCard>(InOperation)->CursorPositionAsPercentage.Y;
	
		if (DropPositionY < 0.75) {
			if (Cast<UWidgetCard>(InOperation->Payload)->CardData.BaseCost == -1) {
				// Prompt the player to select a value for X if they're casting an X cost card.
				Cast<ALostWorldPlayerControllerBase>(UGameplayStatics::GetPlayerController(
					GetWorld(), 0))->AddPlayerPromptToViewport(EPromptType::SpendManaOnXCostSpell,
					Cast<ALostWorldPlayerControllerBattle>(UGameplayStatics::GetPlayerController(
					GetWorld(), 0))->ControlledPlayerEntity->EntityData.Hand[
					Cast<UWidgetCard>(InOperation->Payload)->IndexInHandArray],
					Cast<UWidgetCard>(InOperation->Payload)->IndexInHandArray);
			} else {
				// CAST THAT CARD BABYYYYY
				Cast<ALostWorldGameModeBattle>(GetWorld()->GetAuthGameMode())->PayCostsAndDiscardCardEntity =
					Cast<ALostWorldPlayerControllerBattle>(UGameplayStatics::
						GetPlayerController(GetWorld(), 0))->ControlledPlayerEntity;

				Cast<ALostWorldGameModeBattle>(GetWorld()->GetAuthGameMode())->PayCostsAndDiscardCardHandIndex =
					Cast<UWidgetCard>(InOperation->Payload)->IndexInHandArray;
			
				Cast<ALostWorldGameModeBattle>(GetWorld()->GetAuthGameMode())->
					CreateStackEntry(Cast<UWidgetCard>(InOperation->Payload)->IndexInHandArray);
			}
		}
		// Else, the drag and drop operation will cancel.
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


void UWidgetHudBattle::ResetAllCardWidgetIndices() const
{
	for (int CardWidgetCount = 0; CardWidgetCount < CardsInHandScrollBox->GetChildrenCount(); CardWidgetCount++) {
		if (Cast<UWidgetCard>(CardsInHandScrollBox->GetChildAt(CardWidgetCount))) {
			Cast<UWidgetCard>(CardsInHandScrollBox->GetChildAt(CardWidgetCount))->IndexInHandArray = CardWidgetCount;
		}
	}
}


void UWidgetHudBattle::PlayerStartCastingCard(const FCard& InCard, int IndexInHand, ECardTargets CurrentTargetMode, int CurrentStackEntry) const
{
	if (Cast<AActorEntityPlayer>(Cast<ALostWorldGameModeBattle>(GetWorld()->GetAuthGameMode())->TurnQueue[0])) {
		if (Cast<ALostWorldPlayerControllerBattle>(UGameplayStatics::GetPlayerController(GetWorld(), 0))->
			ControlMode != EPlayerControlModes::None) {
			// Display a copy of the card the player is in the middle of casting
			CurrentCardBeingCast->SetVisibility(ESlateVisibility::HitTestInvisible);
			CurrentCardBeingCast->UpdateComponentsFromPassedCard(InCard);
			CurrentCardBeingCast->IndexInHandArray = IndexInHand;
			Cast<ALostWorldPlayerControllerBattle>(UGameplayStatics::GetPlayerController(GetWorld(), 0))->
				StackEntryIndexForManualTargetSelection = CurrentStackEntry;
				
			// Update the helper text that tells the player which entities they can select
			// and how many entities they're already selected (if the card allows for selecting more than one.)
			switch (CurrentTargetMode) {
			case ECardTargets::OneEnemy:
				CardTargetText->SetVisibility(ESlateVisibility::HitTestInvisible);
				CardTargetText->SetText(FText::FromString("Select 1 Enemy"));
				break;
			case ECardTargets::AnyOneEntity:
				CardTargetText->SetVisibility(ESlateVisibility::HitTestInvisible);
				CardTargetText->SetText(FText::FromString("Select 1 Entity"));
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
	CardsInHandScrollBox->RemoveChildAt(IndexInHand);
}


void UWidgetHudBattle::PlayerClickedEndTurn()
{
	Cast<ALostWorldPlayerControllerBattle>(UGameplayStatics::GetPlayerController(GetWorld(), 0))->
		ControlledPlayerEntity->EndTurn();
}
