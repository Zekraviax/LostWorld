#include "FunctionLibraryStatusEffects.h"


#include "ActorEntityBase.h"
#include "InterfaceBattle.h"
#include "LostWorldGameModeBase.h"


void AFunctionLibraryStatusEffects::ExecuteFunction(EStatusEffectFunctions InFunction, AActorEntityBase* InEffectedEntity)
{
	switch (InFunction)
	{
	case (EStatusEffectFunctions::Poison):
		Poison(InEffectedEntity);
		break;
	case (EStatusEffectFunctions::IronShell):
		IronShell(InEffectedEntity);
		break;
	case (EStatusEffectFunctions::Bleeding):
		Bleeding(InEffectedEntity);
		break;
	default:
		break;
	}
}


void AFunctionLibraryStatusEffects::Poison(AActorEntityBase* EffectedEntity)
{
	float SingleStackDamage = EffectedEntity->EntityData.TotalStats.MaximumHealthPoints * 0.1;
	int Stacks = -1;
	
	Cast<IInterfaceBattle>(EffectedEntity)->GetStatusEffectStacks(EStatusEffectFunctions::Poison, Stacks);
	int PoisonDamageAsInt = FMath::RoundToFloat(SingleStackDamage * Stacks);

	ALostWorldGameModeBase::DualLog(EffectedEntity->EntityData.DisplayName +
		" is hurting from poison!", 2);
	
	Cast<IInterfaceBattle>(EffectedEntity)->TakeDamage(PoisonDamageAsInt);
}


void AFunctionLibraryStatusEffects::IronShell(AActorEntityBase* EffectedEntity)
{
	int BarrierGain = EffectedEntity->EntityData.TotalStats.MaximumHealthPoints * 5;

	Cast<IInterfaceBattle>(EffectedEntity)->GainBarrier(BarrierGain);
}


void AFunctionLibraryStatusEffects::Bleeding(AActorEntityBase* EffectedEntity)
{
	// We can't use any functions that require the GetWorld() function here.
	int BleedingDamageAsInt = 1;
	
	for (auto& StatusEffect : EffectedEntity->EntityData.StatusEffects) {
		if (StatusEffect.StatusEffect == EStatusEffectFunctions::Bleeding) {
			BleedingDamageAsInt = StatusEffect.CurrentStackCount;
		}
	}

	ALostWorldGameModeBase::DualLog(EffectedEntity->EntityData.DisplayName + " is bleeding!", 2);

	Cast<IInterfaceBattle>(EffectedEntity)->TakeDamage(BleedingDamageAsInt);
}