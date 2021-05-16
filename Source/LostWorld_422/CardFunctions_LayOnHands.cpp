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
}


// ------------------------- Base Class Functions
void ACardFunctions_LayOnHands::RunCardAbilityFunction(FStackEntry StackEntry)
{
	//SpentMana_Widget Check
	if (StackEntry.RunWidgetFunction)
		WidgetFunction_SpendMana();
	else {

	}
}


// ------------------------- Widget Functions
void ACardFunctions_LayOnHands::WidgetFunction_SpendMana()
{
	if (SpentManaWidget_Class) {
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, TEXT("Execute Card Function: Lay on Hands (Spend Mana)"));

		SpentManaWidget_Reference = CreateWidget<UBaseClass_Widget_SpentMana>(GetWorld(), SpentManaWidget_Class);
		SpentManaWidget_Reference->AddToViewport();
	}
}