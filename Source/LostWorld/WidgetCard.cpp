#include "WidgetCard.h"


#include "ActorEntityPlayer.h"
#include "InterfaceBattle.h"
#include "LostWorldGameModeBase.h"
#include "LostWorldPlayerControllerBattle.h"
#include "Blueprint/WidgetTree.h"
#include "Kismet/GameplayStatics.h"


bool UWidgetCard::NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation)
{
	return Super::NativeOnDrop(InGeometry, InDragDropEvent, InOperation);
}


void UWidgetCard::UpdateComponentsFromPassedCard(const FCard& InCard) const
{
	TArray<ECardFunctions> Functions;
	TArray<ECardModifiers> Modifiers;
	InCard.FunctionsAndTargets.GetKeys(Functions);
	InCard.ModifiersWithTriggers.GetKeys(Modifiers);
	
	CardNameText->SetText(FText::FromString(InCard.DisplayName));
	
	// If the card has a special cost, the text should be X instead of a number.
	if (Functions.Contains(ECardFunctions::CostsAllMana) || InCard.BaseCost == -1) {
		CostText->SetText(FText::FromString("X"));
	} else {
		CostText->SetText(FText::FromString(FString::FromInt(InCard.TotalCost)));
	}

	
	FString CardTypesAsString;
	for (const ECardTypes Type : InCard.CardTypes) {
		CardTypesAsString.Append(UEnum::GetValueAsString(Type).RightChop(12) + " ");
	}
	TypesText->SetText(FText::FromString(CardTypesAsString));

	
	FString CardElementsAsString;
	for (const ECardElements Element : InCard.CardElements) {
		CardElementsAsString.Append(UEnum::GetValueAsString(Element).RightChop(15) + " ");
	}
	ElementsText->SetText(FText::FromString(CardElementsAsString));

	
	// To-Do: Apply keywords to the description first.
	if (InCard.Keywords.Num() > 0) {
		FString DescriptionAsString;

		for (int Index = 0; Index < InCard.Keywords.Num(); Index++) {
			// If there is multiple keywords, we need to append a comma and a space after the keyword,
			// unless we've reach the last keyword.
			if (InCard.Keywords.Num() > 1 && Index != InCard.Keywords.Num() - 1) {
				DescriptionAsString.Append(UEnum::GetDisplayValueAsText(InCard.Keywords[Index]).ToString() + ", ");
			} else {
				DescriptionAsString.Append(UEnum::GetDisplayValueAsText(InCard.Keywords[Index]).ToString());
			}
			
			if (Index == InCard.Keywords.Num() - 1) {
				DescriptionAsString.Append("\n");
			}
		}
	}
	
	if (Modifiers.Num() > 0) {
		if (Modifiers.Contains(ECardModifiers::Cantrip)) {
			DescriptionText->SetText(FText::FromString(ALostWorldGameModeBase::ParseVariablesInText(
			InCard, InCard.Description) + "\nDraw a card."));
		}
	}
	
	DescriptionText->SetText(FText::FromString(ALostWorldGameModeBase::ParseVariablesInText(
	InCard, InCard.Description)));
}


void UWidgetCard::OnCardClicked()
{
	ALostWorldPlayerControllerBase* PlayerControllerReference = Cast<ALostWorldPlayerControllerBattle>(
	UGameplayStatics::GetPlayerController(GetWorld(), 0));
	
	switch (GetPlayerControlMode())
	{
	case EPlayerControlModes::BottomOneCardInHand:
		Cast<IInterfaceBattle>(PlayerControllerReference->ControlledPlayerEntity)->BottomCard(CardData);
		break;
	default:
		break;
	}
}


EPlayerControlModes UWidgetCard::GetPlayerControlMode()
{
	return Cast<ALostWorldPlayerControllerBattle>(UGameplayStatics::GetPlayerController(
		GetWorld(), 0))->ControlMode;
}
