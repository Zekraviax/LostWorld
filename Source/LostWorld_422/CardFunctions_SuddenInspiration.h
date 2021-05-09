#pragma once

#include "CoreMinimal.h"
#include "CardAbilityActor_BaseClass.h"
#include "CardFunctions_SuddenInspiration.generated.h"


UCLASS()
class LOSTWORLD_422_API ACardFunctions_SuddenInspiration : public ACardAbilityActor_BaseClass
{
	GENERATED_BODY()

public:
// Variables
// --------------------------------------------------

// Functions
// --------------------------------------------------
	virtual void RunCardAbilityFunction(FStackEntry StackEntry) override;
	
};
