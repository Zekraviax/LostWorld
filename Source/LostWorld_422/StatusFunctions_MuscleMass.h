#pragma once

#include "CoreMinimal.h"
#include "StatusFunctions_BaseClass.h"
#include "StatusFunctions_MuscleMass.generated.h"


UCLASS()
class LOSTWORLD_422_API AStatusFunctions_MuscleMass : public AStatusFunctions_BaseClass
{
	GENERATED_BODY()


public:

// ------------------------- Passive Functions
	virtual void PassiveFunction_OnStatusEffectBegin(ABaseClass_EntityInBattle* AffectedEntity);
	virtual void PassiveFunction_OnStatusEffectEnd(ABaseClass_EntityInBattle* AffectedEntity);
};
