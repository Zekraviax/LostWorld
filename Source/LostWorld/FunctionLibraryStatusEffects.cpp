#include "FunctionLibraryStatusEffects.h"


#include "ActorEntityBase.h"
#include "InterfaceBattle.h"


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
	float PoisonDamageAsFloat = EffectedEntity->EntityData.Stats.MaximumHealthPoints * 0.125;
	int PoisonDamageAsInt = FMath::RoundToFloat(PoisonDamageAsFloat);

	Cast<IInterfaceBattle>(EffectedEntity)->TakeDamage(PoisonDamageAsInt);
}


void AFunctionLibraryStatusEffects::IronShell(AActorEntityBase* EffectedEntity)
{
	int BarrierGain = EffectedEntity->EntityData.Stats.MaximumHealthPoints * 5;

	Cast<IInterfaceBattle>(EffectedEntity)->GainBarrier(BarrierGain);
}
