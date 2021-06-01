#pragma once

#include "CoreMinimal.h"
#include "StatusFunctions_BaseClass.h"
#include "StatusFunctions_UndyingRage.generated.h"


UCLASS()
class LOSTWORLD_422_API AStatusFunctions_UndyingRage : public AStatusFunctions_BaseClass
{
	GENERATED_BODY()
	

public:
// ------------------------- Triggered Functions
	virtual int TriggeredFunction_EntityAboutToTakeDamage(ABaseClass_EntityInBattle* AffectedEntity, int IncomingDamage);
};