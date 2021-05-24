#pragma once

#include "CoreMinimal.h"
#include "StatusFunctions_BaseClass.h"
#include "StatusFunctions_Poison.generated.h"


UCLASS()
class LOSTWORLD_422_API AStatusFunctions_Poison : public AStatusFunctions_BaseClass
{
	GENERATED_BODY()


public:

// ------------------------- Triggered Functions
	virtual void TriggeredFunction_StarterOfEntityTurn(ABaseClass_EntityInBattle* AffectedEntity);
};
