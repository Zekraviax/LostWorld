#pragma once

#include "CoreMinimal.h"
#include "CardAbilityActor_BaseClass.h"
#include "CardFunctions_TwinFangs.generated.h"


// Forward Declarations
class UStatusFunctions_Poison;


UCLASS()
class LOSTWORLD_422_API ACardFunctions_TwinFangs : public ACardAbilityActor_BaseClass
{
	GENERATED_BODY()

	ACardFunctions_TwinFangs();

public:
// Variables
// --------------------------------------------------

// ------------------------- Constructors
	UPROPERTY()
	UDataTable* StatusEffectsTable;

// Functions
// --------------------------------------------------
	virtual void RunCardAbilityFunction(FStackEntry StackEntry) override;

};
