#include "WidgetCard.h"

#include <string>

#include "LostWorldGameModeBase.h"
#include "Blueprint/WidgetTree.h"
#include "Components/PanelWidget.h"


bool UWidgetCard::NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation)
{
	return Super::NativeOnDrop(InGeometry, InDragDropEvent, InOperation);
}


void UWidgetCard::UpdateComponentsFromPassedCard(const FCard& InCard)
{
	TArray<ECardFunctions> CardFunctions;
	InCard.FunctionsAndTargets.GetKeys(CardFunctions);
	
	CardNameText->SetText(FText::FromString(InCard.DisplayName));

	// If the card has a special cost, the text should be X instead of a number
	if (CardFunctions.Contains(ECardFunctions::CostsAllMana)) {
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
	
	DescriptionText->SetText(FText::FromString(ALostWorldGameModeBase::ParseVariablesInText(InCard, InCard.Description)));

	// Don't make the function const or this won't work.
	//CurrentGridPanel = GetParent()->GetName();
	/*UWidgetTree* CardWidgetTree = this->WidgetTree;
	if (CardWidgetTree) {
		UObject* Parent = CardWidgetTree->GetOuter();
		//CardElementsAsString.Append(UEnum::GetValueAsString("").RightChop(15) + " ");
		TArray<UObject*> OuterObjects;
		GetObjectsWithOuter(Parent, OuterObjects);

		ALostWorldGameModeBase::DualLog("", 3);
	}*/
}
