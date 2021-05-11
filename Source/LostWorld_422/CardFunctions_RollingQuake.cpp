#include "CardFunctions_RollingQuake.h"

#include "BaseClass_EntityInBattle.h"
#include "BaseClass_Widget_SpentMana.h"
#include "Blueprint/WidgetBlueprintLibrary.h"


ACardFunctions_RollingQuake::ACardFunctions_RollingQuake()
{
	// SpentMana Widget
	static ConstructorHelpers::FClassFinder<UUserWidget> SpentManaWidget_ClassFinder(TEXT("WidgetBlueprint'/Game/Blueprint_Widget_SpentMana.Blueprint_Widget_SpentMana_C'"));
	if (SpentManaWidget_ClassFinder.Class) {
		SpentManaWidget_Class = SpentManaWidget_ClassFinder.Class;
	}

	// Cards DataTable
	//static ConstructorHelpers::FObjectFinder<UDataTable> CardsDataTable_Object(TEXT("DataTable'/Game/DataTables/Card_List.Card_List'"));
	//if (CardsDataTable_Object.Succeeded()) {
	//	CardsTable = CardsDataTable_Object.Object;
	//}
}


// ------------------------- Base Class Functions
void ACardFunctions_RollingQuake::RunCardAbilityFunction(FStackEntry StackEntry)
{
	int DamageValue = 2;

	//SpentMana_Widget Check
	if (StackEntry.RunWidgetFunction)
		WidgetFunction_SpendMana();
	else {
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, TEXT("Execute Card Function: Rolling Quake (Deal Damage)"));

		int32 OldHealthValue = StackEntry.Card.CurrentTargets[0]->EntityBaseData.HealthValues.X_Value;
		StackEntry.Card.CurrentTargets[0]->Event_DamageIncoming(DamageValue, StackEntry.Card.Elements[0], E_Card_DamageTypes::E_Magical);

		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, (TEXT("Target: " + StackEntry.Card.CurrentTargets[0]->EntityBaseData.DisplayName)));
	}
}


// ------------------------- Widget Functions
void ACardFunctions_RollingQuake::WidgetFunction_SpendMana()
{
	if (SpentManaWidget_Class) {
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, TEXT("Execute Card Function: Rolling Quake (Spend Mana)"));

		SpentManaWidget_Reference = CreateWidget<UBaseClass_Widget_SpentMana>(GetWorld(), SpentManaWidget_Class);
		SpentManaWidget_Reference->AddToViewport();
	}
}