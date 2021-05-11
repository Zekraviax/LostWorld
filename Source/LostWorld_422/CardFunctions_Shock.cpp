#include "CardFunctions_Shock.h"

#include "BaseClass_EntityInBattle.h"


void ACardFunctions_Shock::RunCardAbilityFunction(FStackEntry StackEntry)
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, TEXT("Execute Card Function: Shock"));

	int32 DamageValue = 1;
	int32 OldHealthValue = StackEntry.Card.CurrentTargets[0]->EntityBaseData.HealthValues.X_Value;

	//StackEntry.Card.CurrentTargets[i]->EntityBaseData.HealthValues.X_Value -= DamageValue;
	StackEntry.Card.CurrentTargets[0]->Event_DamageIncoming(DamageValue, StackEntry.Card.Elements[0], E_Card_DamageTypes::E_Magical);

	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, (TEXT("Target: " + StackEntry.Card.CurrentTargets[0]->EntityBaseData.DisplayName)));
	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, (TEXT("Damage: " + FString::FromInt(DamageValue) + "  /  New Health Value: " + FString::FromInt(StackEntry.Card.CurrentTargets[0]->EntityBaseData.HealthValues.X_Value) + "  /  Old Health Value: " + FString::FromInt(OldHealthValue))));
}