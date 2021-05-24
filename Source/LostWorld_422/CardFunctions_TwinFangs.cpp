#include "CardFunctions_TwinFangs.h"

#include "BaseClass_EntityInBattle.h"
#include "StatusFunctions_Poison.h"


ACardFunctions_TwinFangs::ACardFunctions_TwinFangs()
{
	//PoisonAttachment = CreateDefaultSubobject<UStatusFunctions_Poison>(TEXT("StatusEffect_Poison"));
	//PoisonAttachment->RegisterComponent();
}


void ACardFunctions_TwinFangs::RunCardAbilityFunction(FStackEntry StackEntry)
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, TEXT("Execute Card Function: Twin Fangs"));

	int32 DamageValue = StackEntry.Card.AbilitiesAndConditions[0].BaseDamage;
	Cast<ABaseClass_EntityInBattle>(StackEntry.Card.CurrentTargets[0])->Event_DamageIncoming(DamageValue, StackEntry.Card.Elements[0], E_Card_DamageTypes::E_Magical);

	//StackEntry.Card.CurrentTargets[0]
	//PoisonAttachment->Add

	//PoisonAttachment = StackEntry.Card.CurrentTargets[0]->CreateDefaultSubobject<UStatusFunctions_Poison>(TEXT("StatusEffect_Poison"));
	//PoisonAttachment->RegisterComponent();

	//PoisonAttachment->AttachStatusFunctionToEntity(Cast<ABaseClass_EntityInBattle>(StackEntry.Card.CurrentTargets[0]));
}