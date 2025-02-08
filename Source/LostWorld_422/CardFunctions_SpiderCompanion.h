#pragma once

#include "CoreMinimal.h"
#include "CardAbilityActor_BaseClass.h"
#include "CardFunctions_SpiderCompanion.generated.h"


UCLASS()
class LOSTWORLD_422_API ACardFunctions_SpiderCompanion : public ACardAbilityActor_BaseClass
{
	GENERATED_BODY()

	ACardFunctions_SpiderCompanion();

public:
// Base Variables
// --------------------------------------------------

// ------------------------- Constructors
	UPROPERTY()
	UDataTable* SummonsTable;

	UPROPERTY()
	TSubclassOf<ABaseClass_EntityInBattle> EntityInBattle_BlueprintClass;

// Functions
// --------------------------------------------------

// ------------------------- Base Class Functions
	virtual void RunCardAbilityFunction(FStackEntry StackEntry);
};
