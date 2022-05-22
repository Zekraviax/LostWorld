#pragma once

#include "CoreMinimal.h"
#include "Level_SpawnTypeBase.h"
#include "Level_SpawnType_City.generated.h"


UCLASS()
class LOSTWORLD_422_API ALevel_SpawnType_City : public ALevel_SpawnTypeBase
{
	GENERATED_BODY()
	
// Functions
// --------------------------------------------------

// ------------------------- Base Class Functions
	virtual void RunLevelGeneratorFunction();
};
