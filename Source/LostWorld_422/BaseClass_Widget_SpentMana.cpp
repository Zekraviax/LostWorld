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
	TArray<E_Card_AbilityConditions> ConditionsArray;
	UBaseClass_CardUserWidget* DuplicateCard = CreateWidget<UBaseClass_CardUserWidget>(GetWorld(), CardWidget_Class);
	DuplicateCard->CardData = CardReference->CardData;

	DuplicateCard->CardData.ManaCost = CurrentManaValue;
	DuplicateCard->CardData.Controller->EntityBaseData.ManaValues.X_Value -= CurrentManaValue;

	// Alter Values Based On Casting Cost
	for (int i = 0; i < DuplicateCard->CardData.AbilitiesAndConditions.Num(); i++) {
		DuplicateCard->CardData.AbilitiesAndConditions[i].AbilityConditions.GetKeys(ConditionsArray);

		for (int j = 0; j < ConditionsArray.Num(); j++) {
			if (ConditionsArray[j] == E_Card_AbilityConditions::E_NextAbility_CastingCost) {
				j++;

				E_Card_AbilityConditions FoundCondition = ConditionsArray[j];
				DuplicateCard->CardData.AbilitiesAndConditions[i].AbilityConditions.Remove(ConditionsArray[j]);
				DuplicateCard->CardData.AbilitiesAndConditions[i].AbilityConditions.Add(FoundCondition, DuplicateCard->CardData.ManaCost);
			}
		}
	}

	DuplicateCard->CastCard();

	this->RemoveFromParent();
}