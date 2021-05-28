#include "CardFunctions_TwinFangs.h"

#include "BaseClass_EntityInBattle.h"
#include "LostWorld_422GameModeBase.h"


ACardFunctions_TwinFangs::ACardFunctions_TwinFangs()
{
	// Get Status Effects DataTable
	static ConstructorHelpers::FObjectFinder<UDataTable> StatusEffectsDataTable_Object(TEXT("DataTable'/Game/DataTables/StatusEffects_List.StatusEffects_List'"));
	if (StatusEffectsDataTable_Object.Succeeded()) {
		StatusEffectsTable = StatusEffectsDataTable_Object.Object;
	}
}


void ACardFunctions_TwinFangs::RunCardAbilityFunction(FStackEntry StackEntry)
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, TEXT("Execute Card Function: Twin Fangs"));

	int32 DamageValue = StackEntry.Card.AbilitiesAndConditions[0].CalculatedDamage;
	Cast<ABaseClass_EntityInBattle>(StackEntry.Card.CurrentTargets[0])->Event_DamageIncoming(DamageValue, StackEntry.Card.Elements[0], StackEntry.Card.AbilitiesAndConditions[0].DamageType);

	if (StatusEffectsTable) {
		FString ContextString;

		F_StatusEffect_Base* PoisonData = StatusEffectsTable->FindRow<F_StatusEffect_Base>(FName("Poison"), ContextString);
		PoisonData->Source = StackEntry.Card.Controller;
		
		Cast<ABaseClass_EntityInBattle>(StackEntry.Card.CurrentTargets[0])->Event_StatusEffectIncoming(*PoisonData);
	}
}