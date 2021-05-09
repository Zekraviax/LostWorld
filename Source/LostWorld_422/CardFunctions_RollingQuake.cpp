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
void ACardFunctions_RollingQuake::RunCardAbilityFunction(FCardBase CardAbility)
{
	TArray<UUserWidget*> FoundSpentManaWidgets;
	UWidgetBlueprintLibrary::GetAllWidgetsOfClass(GetWorld(), FoundSpentManaWidgets, UBaseClass_Widget_SpentMana::StaticClass(), true);

	//SpentMana_Widget Check
	if (FoundSpentManaWidgets.Num() <= 0)
		WidgetFunction_SpendMana();
	else {
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, TEXT("Execute Card Function: Rolling Quake (Deal Damage)"));

		int32 OldHealthValue = CardAbility.CurrentTargets[0]->EntityBaseData.HealthValues.X_Value;
		CardAbility.CurrentTargets[0]->EntityBaseData.HealthValues.X_Value -= 2;

		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, (TEXT("Target: " + CardAbility.CurrentTargets[0]->EntityBaseData.DisplayName)));
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, (TEXT("Damage: " + FString::FromInt(2) + "  /  New Health Value: " + FString::FromInt(CardAbility.CurrentTargets[0]->EntityBaseData.HealthValues.X_Value) + "  /  Old Health Value: " + FString::FromInt(OldHealthValue))));
		
		if (Cast<ALostWorld_422GameStateBase>(GetWorld()->GetGameState())->TheStack.Num() <= 0) {
			for (int i = 0; i < FoundSpentManaWidgets.Num(); i++) {
				FoundSpentManaWidgets[i]->RemoveFromParent();
				FoundSpentManaWidgets[i]->ConditionalBeginDestroy();
				FoundSpentManaWidgets[i] = NULL;

				GetWorld()->ForceGarbageCollection(true);
			}
		}
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