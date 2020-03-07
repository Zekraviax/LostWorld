// Fill out your copyright notice in the Description page of Project Settings.


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
	//if (CardReference->CardData.ManaCost <= CurrentManaValue) {
		UBaseClass_CardUserWidget* DuplicateCard = CreateWidget<UBaseClass_CardUserWidget>(GetWorld(), CardWidget_Class);

		DuplicateCard->CardData = CardReference->CardData;
		//DuplicateCard->CardData.ManaCost = CurrentManaValue;
		DuplicateCard->CardData.Controller->EntityBaseData.ManaValues.X_Value -= CurrentManaValue;
		DuplicateCard->CastCard();

		this->RemoveFromParent();
	//}
}