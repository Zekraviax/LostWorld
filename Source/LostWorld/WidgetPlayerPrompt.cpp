#include "WidgetPlayerPrompt.h"


#include "ActorEntityPlayer.h"
#include "Kismet/GameplayStatics.h"
#include "LostWorldGameModeBattle.h"
#include "LostWorldPlayerControllerBattle.h"


void UWidgetPlayerPrompt::SetUpPrompt(const EPromptType InPromptType, const FCard& InCard, int IndexInHand)
{
	CurrentPromptType = InPromptType;
	LocalCard = InCard;
	LocalIndexInHand = IndexInHand;
	
	switch (InPromptType)
	{
	case EPromptType::SpendManaOnXCostSpell:
		SpendManaOnXCostSpell();
		break;
	default:
		break;
	}
}


void UWidgetPlayerPrompt::SpendManaOnXCostSpell()
{
	LocalVar = 0;
	
	Title->SetText(FText::FromString("Casting X cost spell " + LocalCard.DisplayName));
	Body->SetText(FText::FromString("Choose a value for X:\n" + FString::FromInt(LocalVar)));
	Body->Font.Size = 20;
	
	LeftButton->SetVisibility(ESlateVisibility::Visible);
	LeftButtonText->SetText(FText::FromString("<"));
	
	RightButton->SetVisibility(ESlateVisibility::Visible);
	RightButtonText->SetText(FText::FromString(">"));

	ConfirmButton->SetVisibility(ESlateVisibility::Visible);
	CancelButton->SetVisibility(ESlateVisibility::Visible);
}


void UWidgetPlayerPrompt::OnLeftButtonPressed()
{
	switch (CurrentPromptType)
	{
	case EPromptType::SpendManaOnXCostSpell:
		if (LocalVar > 0) {
			LocalVar--;
			Body->SetText(FText::FromString("Choose a value for X:\n" + FString::FromInt(LocalVar)));
		}
		break;
	default:
		break;
	}
}

void UWidgetPlayerPrompt::OnRightButtonPressed()
{
	switch (CurrentPromptType)
	{
	case EPromptType::SpendManaOnXCostSpell:
		// To-Do: Warn the player if the value for X they've set is greater than their current MP.
		LocalVar++;
		Body->SetText(FText::FromString("Choose a value for X:\n" + FString::FromInt(LocalVar)));
		break;
	default:
		break;
	}
}


void UWidgetPlayerPrompt::OnConfirmButtonPressed()
{
	switch (CurrentPromptType)
	{
	case EPromptType::SpendManaOnXCostSpell:
		Cast<ALostWorldGameModeBattle>(GetWorld()->GetAuthGameMode())->PayCostsAndDiscardCardEntity =
			Cast<ALostWorldPlayerControllerBattle>(UGameplayStatics::
			GetPlayerController(GetWorld(), 0))->ControlledPlayerEntity;

		Cast<ALostWorldGameModeBattle>(GetWorld()->GetAuthGameMode())->PayCostsAndDiscardCardHandIndex =
			LocalIndexInHand;
		
		// Override the TotalCost of the card before creating a StackEntry.
		Cast<ALostWorldPlayerControllerBattle>(UGameplayStatics::
			GetPlayerController(GetWorld(), 0))->ControlledPlayerEntity->EntityData.Hand[LocalIndexInHand].
			TotalCost = LocalVar;
		
		Cast<ALostWorldGameModeBattle>(GetWorld()->GetAuthGameMode())->
			CreateStackEntry(LocalIndexInHand);
		break;
	default:
		break;
	}

	// Ongoing To-Do: Either make sure that the prompt should always be closed after clicking the confirm button, or add exceptions into the PromptType switch.
	this->RemoveFromViewport();
}


void UWidgetPlayerPrompt::OnCancelButtonPressed()
{
}
