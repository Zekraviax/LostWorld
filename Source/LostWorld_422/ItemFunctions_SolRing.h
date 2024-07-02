#pragma once

#include "CoreMinimal.h"
#include "ItemFunctions_BaseClass.h"
#include "ItemFunctions_SolRing.generated.h"


// Forward Declarations
class ABaseClass_EntityInBattle;


UCLASS()
class LOSTWORLD_422_API AItemFunctions_SolRing : public AItemFunctions_BaseClass
{
	GENERATED_BODY()

	
	virtual void TriggeredFunction_OnItemEquipped(ABaseClass_EntityInBattle* EquippedEntity);
	virtual void TriggeredFunction_OnItemUnequipped(ABaseClass_EntityInBattle* EquippedEntity);

	virtual void TriggeredFunction_StarterOfWearerTurn(ABaseClass_EntityInBattle* EquippedEntity);
};
