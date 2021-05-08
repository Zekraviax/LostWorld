#include "CardFunctions_RollingQuake.h"

#include "BaseClass_EntityInBattle.h"
#include "BaseClass_Widget_SpentMana.h"


ACardFunctions_RollingQuake::ACardFunctions_RollingQuake()
{
	static ConstructorHelpers::FObjectFinder<UBaseClass_Widget_SpentMana> SpentManaWidget_BlueprintConstruct(TEXT("WidgetBlueprint'/Game/Blueprint_Widget_SpentMana.Blueprint_Widget_SpentMana'"));
	if (SpentManaWidget_BlueprintConstruct.Object) {
		SpentManaWidget_Class = (UClass*)SpentManaWidget_BlueprintConstruct.Object->StaticClass;
	}
}


// ------------------------- Base Class Functions
void ACardFunctions_RollingQuake::RunCardAbilityFunction(FCardBase CardAbility)
{
	if (!SpentManaWidget_Reference->IsValidLowLevel()) {
		if (SpentManaWidget_Class) {
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, TEXT("Execute Card Function: Rolling Quake (Spend Mana)"));

			SpentManaWidget_Reference = CreateWidget<UBaseClass_Widget_SpentMana>(GetWorld(), SpentManaWidget_Class);
			SpentManaWidget_Reference->AddToViewport();
		}
	}
	else {
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, TEXT("Execute Card Function: Rolling Quake (Deal Damage)"));

		int32 OldHealthValue = CardAbility.CurrentTargets[0]->EntityBaseData.HealthValues.X_Value;
		CardAbility.CurrentTargets[0]->EntityBaseData.HealthValues.X_Value -= 2;

		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, (TEXT("Target: " + CardAbility.CurrentTargets[0]->EntityBaseData.DisplayName)));
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, (TEXT("Damage: " + FString::FromInt(2) + "  /  New Health Value: " + FString::FromInt(CardAbility.CurrentTargets[0]->EntityBaseData.HealthValues.X_Value) + "  /  Old Health Value: " + FString::FromInt(OldHealthValue))));
		
	}
}


// ------------------------- Widget Functions
void ACardFunctions_RollingQuake::WidgetFunction_SpendMana()
{

}