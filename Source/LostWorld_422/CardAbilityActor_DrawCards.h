#pragma once

#include "CoreMinimal.h"
#include "CardAbilityActor_BaseClass.h"
#include "CardAbilityActor_DrawCards.generated.h"


UCLASS()
class LOSTWORLD_422_API ACardAbilityActor_DrawCards : public ACardAbilityActor_BaseClass
{
	GENERATED_BODY()
	
public:
// Base Variables
// --------------------------------------------------

// Functions
// --------------------------------------------------
	void RunCardAbilityFunction();
};