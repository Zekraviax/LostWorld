#pragma once

#include "CoreMinimal.h"
#include "Level_SpawnTypeBase.h"
#include "Level_SpawnType_FourSquare.generated.h"


UCLASS()
class LOSTWORLD_422_API ALevel_SpawnType_FourSquare : public ALevel_SpawnTypeBase
{
	GENERATED_BODY()
	
// Base Variables
// --------------------------------------------------

// ------------------------- Constructors

// Functions
// --------------------------------------------------

// ------------------------- Base Class Functions
	virtual void RunLevelGeneratorFunction();
};
