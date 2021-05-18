#include "CardFunctions_Annihilate.h"

#include "BaseClass_EntityInBattle.h"


void ACardFunctions_Annihilate::RunCardAbilityFunction(FStackEntry StackEntry)
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, TEXT("Execute Card Function: Annihilate"));

	Cast<ABaseClass_EntityInBattle>(StackEntry.Card.CurrentTargets[0])->EntityBaseData.HealthValues.X_Value = 0;
}