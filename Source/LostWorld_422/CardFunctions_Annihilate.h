#pragma once

#include "CoreMinimal.h"
#include "CardAbilityActor_BaseClass.h"
#include "CardFunctions_Annihilate.generated.h"


UCLASS()
class LOSTWORLD_422_API ACardFunctions_Annihilate : public ACardAbilityActor_BaseClass
{
	GENERATED_BODY()
	
public:
// Variables
// --------------------------------------------------

// Functions
// --------------------------------------------------
	virtual void RunCardAbilityFunction(FCardBase CardAbility) override;

};
