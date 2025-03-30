#include "WidgetPlayerPrompt.h"


void UWidgetPlayerPrompt::SetUpPrompt(EPromptType InPromptType)
{
	CurrentPromptType = InPromptType;
	
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
	
	Title->SetText(FText::FromString("Spend MP for X"));
	Body->SetText(FText::FromString(FString::FromInt(LocalVar)));
	
	LeftButton->SetVisibility(ESlateVisibility::Visible);
	LeftButtonText->SetText(FText::FromString("<"));
	
	RightButton->SetVisibility(ESlateVisibility::Visible);
	LeftButtonText->SetText(FText::FromString(">"));
	
}


void UWidgetPlayerPrompt::OnLeftButtonPressed()
{
	switch (CurrentPromptType)
	{
	case EPromptType::SpendManaOnXCostSpell:
		if (LocalVar > 0) {
			LocalVar--;
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
		LocalVar++;
		break;
	default:
		break;
	}
}
