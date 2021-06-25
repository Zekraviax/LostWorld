#pragma once

#include "CoreMinimal.h"
#include "Level_SpawnTypeBase.h"
#include "Level_SpawnType_BossDen.generated.h"


UCLASS()
class LOSTWORLD_422_API ALevel_SpawnType_BossDen : public ALevel_SpawnTypeBase
{
	GENERATED_BODY()
	
// ------------------------- Base Class Functions
	virtual void RunLevelGeneratorFunction();
};
