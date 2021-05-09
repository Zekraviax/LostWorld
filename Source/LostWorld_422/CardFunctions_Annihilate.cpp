#include "CardFunctions_Annihilate.h"

#include "BaseClass_EntityInBattle.h"


void ACardFunctions_Annihilate::RunCardAbilityFunction(FStackEntry StackEntry)
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, TEXT("Execute Card Function: Annihilate"));

	int32 DamageValue = 1;

	for (int i = 0; i < StackEntry.Card.CurrentTargets.Num(); i++)
	{
		StackEntry.Card.CurrentTargets[i]->EntityBaseData.HealthValues.X_Value = 0;
	}
}