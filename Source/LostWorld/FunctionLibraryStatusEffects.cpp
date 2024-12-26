#include "FunctionLibraryStatusEffects.h"


#include "ActorEntityBase.h"
#include "InterfaceBattle.h"


void AFunctionLibraryStatusEffects::ExecuteFunction(EStatusEffectFunctions InFunction)
{
	switch (InFunction)
	{
		case (EStatusEffectFunctions::Poison):
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
