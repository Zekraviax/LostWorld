#include "CardFunctions_Shock.h"

#include "BaseClass_EntityInBattle.h"


void ACardFunctions_Shock::RunCardAbilityFunction(FStackEntry StackEntry)
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, TEXT("Execute Card Function: Shock"));

	int32 DamageValue = 1;

	for (int i = 0; i < StackEntry.Card.CurrentTargets.Num(); i++)
	{
		int32 OldHealthValue = StackEntry.Card.CurrentTargets[i]->EntityBaseData.HealthValues.X_Value;
		StackEntry.Card.CurrentTargets[i]->EntityBaseData.HealthValues.X_Value -= DamageValue;

		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, (TEXT("Target: " + StackEntry.Card.CurrentTargets[i]->EntityBaseData.DisplayName)));
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, (TEXT("Damage: " + FString::FromInt(DamageValue) + "  /  New Health Value: " + FString::FromInt(StackEntry.Card.CurrentTargets[i]->EntityBaseData.HealthValues.X_Value) + "  /  Old Health Value: " + FString::FromInt(OldHealthValue))));
	}
}