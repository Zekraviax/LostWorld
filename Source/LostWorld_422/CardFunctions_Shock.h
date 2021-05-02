#pragma once

#include "CoreMinimal.h"
#include "CardAbilityActor_BaseClass.h"
#include "CardFunctions_Shock.generated.h"


UCLASS()
class LOSTWORLD_422_API ACardFunctions_Shock : public ACardAbilityActor_BaseClass
{
	GENERATED_BODY()
	
public:
// Variables
// --------------------------------------------------

// Functions
// --------------------------------------------------
	virtual void RunCardAbilityFunction(FCardBase CardAbility) override;

};
