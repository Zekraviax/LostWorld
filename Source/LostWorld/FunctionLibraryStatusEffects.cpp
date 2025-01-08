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
		default:
			break;
	}
}


void AFunctionLibraryStatusEffects::Poison(AActorEntityBase* EffectedEntity)
{
	// To-Do: Make poison damage scale based on the number of stacks the entity has.
	float PoisonDamageAsFloat = EffectedEntity->EntityData.Stats.MaximumHealthPoints * 0.125;
	int PoisonDamageAsInt = FMath::RoundToFloat(PoisonDamageAsFloat);

	ALostWorldGameModeBase::DualLog(EffectedEntity->EntityData.DisplayName + " is poisoned!", 2);
	
	Cast<IInterfaceBattle>(EffectedEntity)->TakeDamage(PoisonDamageAsInt);
}


void AFunctionLibraryStatusEffects::IronShell(AActorEntityBase* EffectedEntity)
{
	int BarrierGain = EffectedEntity->EntityData.Stats.MaximumHealthPoints * 5;

	Cast<IInterfaceBattle>(EffectedEntity)->GainBarrier(BarrierGain);
}
