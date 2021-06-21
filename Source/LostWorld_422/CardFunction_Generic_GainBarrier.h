#pragma once

#include "CoreMinimal.h"
#include "CardAbilityActor_BaseClass.h"
#include "CardFunction_Generic_GainBarrier.generated.h"


UCLASS()
class LOSTWORLD_422_API ACardFunction_Generic_GainBarrier : public ACardAbilityActor_BaseClass
{
	GENERATED_BODY()
	
// Variables
// --------------------------------------------------

// Functions
// --------------------------------------------------
	virtual void RunCardAbilityFunction(FStackEntry StackEntry) override;

};
