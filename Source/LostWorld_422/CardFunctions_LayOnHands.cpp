#include "CardFunctions_LayOnHands.h"

#include "BaseClass_EntityInBattle.h"
#include "BaseClass_Widget_SpentMana.h"
#include "Blueprint/WidgetBlueprintLibrary.h"


ACardFunctions_LayOnHands::ACardFunctions_LayOnHands()
{
	// SpentMana Widget
	static ConstructorHelpers::FClassFinder<UUserWidget> SpentManaWidget_ClassFinder(TEXT("WidgetBlueprint'/Game/Widget_SpentMana_Blueprint.Widget_SpentMana_Blueprint_C'"));
	if (SpentManaWidget_ClassFinder.Class) {
		SpentManaWidget_Class = SpentManaWidget_ClassFinder.Class;
	}

	// Cards DataTable
	static ConstructorHelpers::FObjectFinder<UDataTable> CardsDataTable_Object(TEXT("DataTable'/Game/DataTables/Cards_List.Cards_List'"));
	if (CardsDataTable_Object.Succeeded()) {
		CardsTable = CardsDataTable_Object.Object;
	}
}


// ------------------------- Base Class Functions
void ACardFunctions_LayOnHands::RunCardAbilityFunction(FStackEntry StackEntry)
{
	/*
	int HealingValue = StackEntry.Card.AbilitiesAndConditions[0].CalculatedHealing;

	//SpentMana_Widget Check
	if (StackEntry.RunWidgetFunction) {
		if (SpentManaWidget_Class) {
			SpentManaWidget_Reference = CreateWidget<UBaseClass_Widget_SpentMana>(GetWorld(), SpentManaWidget_Class);
			SpentManaWidget_Reference->CardsTableRowName = "LayOnHands";
			SpentManaWidget_Reference->StackEntry = StackEntry;
			SpentManaWidget_Reference->AddToViewport();
		}
	} else {
		Cast<ABaseClass_EntityInBattle>(StackEntry.Card.CurrentTargets[0])->Event_HealingIncoming(HealingValue);

		StackEntry.Card.Controller->Event_DrawCard();
		StackEntry.Card.Controller->UpdateCardVariables();
	}
	*/
}


// ------------------------- Widget Functions
void ACardFunctions_LayOnHands::WidgetFunction_SpendMana(int ManaSpent, FStackEntry StackEntry)
{
	/*
	StackEntry.Card.AbilitiesAndConditions[0].CalculatedHealing = StackEntry.Card.AbilitiesAndConditions[0].CalculatedHealing + ManaSpent;
	StackEntry.RunWidgetFunction = false;

	Cast<ALostWorld_422GameStateBase>(GetWorld()->GetGameState())->AddCardFunctionsToTheStack(StackEntry);

	// Subtract mana
	StackEntry.Card.Controller->EntityBaseData.ManaValues.X_Value -= ManaSpent;

	ConditionalBeginDestroy();
	*/
}