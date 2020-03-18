#include "CardAbilityActor_DealDamage.h"

#include "BaseClass_EntityInBattle.h"


void ACardAbilityActor_DealDamage::RunCardAbilityFunction(FCardBase CardAbility)
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, TEXT("Execute Function: Deal Damage"));

	int32 DamageValue = 0;
	TMap<E_Card_AbilityConditions, int32> ConditionsArray = CardAbility.AbilitiesAndConditions[0].AbilityConditions;

	if (ConditionsArray.Contains(E_Card_AbilityConditions::E_Damage)) {
		DamageValue = ConditionsArray.FindChecked(E_Card_AbilityConditions::E_Damage);
	}

	for (int i = 0; i < CardAbility.CurrentTargets.Num(); i++)
	{
		int32 OldHealthValue = CardAbility.CurrentTargets[i]->EntityBaseData.HealthValues.X_Value;
		CardAbility.CurrentTargets[i]->EntityBaseData.HealthValues.X_Value -= DamageValue;

		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, (TEXT("Target: " + CardAbility.CurrentTargets[i]->EntityBaseData.DisplayName)));
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, (TEXT("Damage: " + FString::FromInt(DamageValue) + "  /  New Health Value: " + FString::FromInt(CardAbility.CurrentTargets[i]->EntityBaseData.HealthValues.X_Value) + "  /  Old Health Value: " + FString::FromInt(OldHealthValue))));
	}
}