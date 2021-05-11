#pragma once

#include "CoreMinimal.h"
#include "ItemFunctions_BaseClass.h"
#include "ItemFunctions_SolRing.generated.h"


UCLASS()
class LOSTWORLD_422_API AItemFunctions_SolRing : public AItemFunctions_BaseClass
{
	GENERATED_BODY()
	

// ------------------------- Triggered Functions
	virtual void TriggeredFunction_OnItemEquipped();
	virtual void TriggeredFunction_StarterOfWearerTurn();
};
