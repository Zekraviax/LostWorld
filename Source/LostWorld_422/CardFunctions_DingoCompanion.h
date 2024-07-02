#pragma once

#include "CoreMinimal.h"
#include "CardAbilityActor_BaseClass.h"
#include "CardFunctions_DingoCompanion.generated.h"


// Forward Declarations
class ABaseClass_EntityInBattle;


UCLASS()
class LOSTWORLD_422_API ACardFunctions_DingoCompanion : public ACardAbilityActor_BaseClass
{
	GENERATED_BODY()

	ACardFunctions_DingoCompanion();

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
