#include "BaseClass_Widget_SpentMana.h"

#include "BaseClass_EntityInBattle.h"


void UBaseClass_Widget_SpentMana::OnWidgetCreated()
{
	CurrentManaValue = 1;
}


void UBaseClass_Widget_SpentMana::ChangeManaValue(int32 NewValue)
{
	if (NewValue >= 0) {
		CurrentManaValue = NewValue;
		Number_EditableBox->SetText(FText::AsNumber(CurrentManaValue));
	}
}


void UBaseClass_Widget_SpentMana::CheckInputText(FText Text)
{
	FString StringValue = Text.ToString();

	if (Text.IsNumeric()) {
		CurrentManaValue = FCString::Atoi(*StringValue);
	}

	Number_EditableBox->SetText(FText::AsNumber(CurrentManaValue));
}


void UBaseClass_Widget_SpentMana::ConfirmManaValue()
{
	FString ContextString;
	FCardBase* DuplicateCard = CardsTable->FindRow<FCardBase>("RollingQuake", ContextString, true);
	TArray<ABaseClass_EntityInBattle*> ValidTargets;

	// Get Random Targets
	for (TActorIterator<ABaseClass_EntityInBattle> EntityItr(GetWorld()); EntityItr; ++EntityItr)
	{
		ABaseClass_EntityInBattle* BattleEntity = *EntityItr;

		if (!BattleEntity->EntityBaseData.IsPlayerControllable) {
			ValidTargets.Add(BattleEntity);
		}
		else {
			BattleEntity->EntityBaseData.ManaValues.X_Value -= CurrentManaValue;
		}
	}


	for (int r = 0; r < CurrentManaValue; r++) {
		// Get random targets
		DuplicateCard->CurrentTargets.Empty();
		DuplicateCard->CurrentTargets.Add(ValidTargets[FMath::RandRange(0, (ValidTargets.Num() - 1))]);

		Cast<ALostWorld_422GameStateBase>(GetWorld()->GetGameState())->AddCardFunctionsToTheStack(*DuplicateCard);
	}

	//this->RemoveFromParent();
	this->SetVisibility(ESlateVisibility::Collapsed);
}