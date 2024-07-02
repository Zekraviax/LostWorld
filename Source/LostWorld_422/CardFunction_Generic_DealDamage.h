#pragma once

#include "CoreMinimal.h"
#include "CardAbilityActor_BaseClass.h"
#include "CardFunction_Generic_DealDamage.generated.h"


UCLASS()
class LOSTWORLD_422_API ACardFunction_Generic_DealDamage : public ACardAbilityActor_BaseClass
{
	GENERATED_BODY()
	
public:
// Variables
// --------------------------------------------------

// Functions
// --------------------------------------------------
	virtual void RunCardAbilityFunction(FStackEntry StackEntry) override;
};
