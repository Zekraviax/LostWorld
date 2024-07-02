#pragma once

#include "CoreMinimal.h"
#include "ItemFunctions_BaseClass.h"
#include "ItemFunctions_JuiceOfLife.generated.h"


// Forward Declarations
class ABaseClass_EntityInBattle;


UCLASS()
class LOSTWORLD_422_API AItemFunctions_JuiceOfLife : public AItemFunctions_BaseClass
{
	GENERATED_BODY()
	
	virtual void ActivatedFunction(ABaseClass_EntityInBattle* EquippedEntity);
};