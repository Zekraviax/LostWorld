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
	FCardBase* DuplicateCard = CardsTable->FindRow<FCardBase>(FName(*CardsTableRowName), ContextString, true);

	FActorSpawnParameters SpawnParameters;
	SpawnParameters.bNoFail = true;
	SpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	ACardAbilityActor_BaseClass* CardAbilityActor_Reference = GetWorld()->SpawnActor<ACardAbilityActor_BaseClass>(DuplicateCard->AbilitiesAndConditions[0].Ability, FVector::ZeroVector, FRotator::ZeroRotator, SpawnParameters);
	CardAbilityActor_Reference->WidgetFunction_SpendMana(CurrentManaValue, StackEntry);

	this->RemoveFromParent();
}