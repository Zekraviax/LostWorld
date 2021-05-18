#include "CardFunctions_NormalPunch.h"

#include "BaseClass_EntityInBattle.h"


void ACardFunctions_NormalPunch::RunCardAbilityFunction(FStackEntry StackEntry)
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, TEXT("Execute Card Function: Normal Punch"));

	int32 DamageValue = StackEntry.Card.Controller->EntityBaseData.CoreStats.Strength + StackEntry.Card.AbilitiesAndConditions[0].BaseDamage;

	Cast<ABaseClass_EntityInBattle>(StackEntry.Card.CurrentTargets[0])->Event_DamageIncoming(DamageValue, StackEntry.Card.Elements[0], E_Card_DamageTypes::E_Physical);
}