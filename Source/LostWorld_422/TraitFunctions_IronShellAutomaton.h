#pragma once

#include "CoreMinimal.h"
#include "TraitFunctions_BaseClass.h"
#include "TraitFunctions_IronShellAutomaton.generated.h"


UCLASS()
class LOSTWORLD_422_API ATraitFunctions_IronShellAutomaton : public ATraitFunctions_BaseClass
{
	GENERATED_BODY()
	

// ------------------------- Triggered Functions
	virtual void TriggeredFunction_StartOfBattle(ABaseClass_EntityInBattle* Self);
};
