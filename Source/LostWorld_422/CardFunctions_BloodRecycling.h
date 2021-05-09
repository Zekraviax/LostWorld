#pragma once

#include "CoreMinimal.h"
#include "CardAbilityActor_BaseClass.h"
#include "CardFunctions_BloodRecycling.generated.h"


UCLASS()
class LOSTWORLD_422_API ACardFunctions_BloodRecycling : public ACardAbilityActor_BaseClass
{
	GENERATED_BODY()
	
public:
// Variables
// --------------------------------------------------

// Functions
// --------------------------------------------------
	virtual void RunCardAbilityFunction(FStackEntry StackEntry) override;
};
