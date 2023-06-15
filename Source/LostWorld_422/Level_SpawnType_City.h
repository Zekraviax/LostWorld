#pragma once

#include "CoreMinimal.h"
#include "Level_SpawnTypeBase.h"
#include "Level_SpawnType_City.generated.h"


class UWidget_HUD_City_Base;


UCLASS()
class LOSTWORLD_422_API ALevel_SpawnType_City : public ALevel_SpawnTypeBase
{
	GENERATED_BODY()


// Variables
// --------------------------------------------------

// ------------------------- Widgets
	// To-Do: Figure out why this line causes compiling to fail
	//UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<UWidget_HUD_City_Base> LevelSelectWidgetBlueprintClass;

	

// Functions
// --------------------------------------------------

// ------------------------- Base Class Functions
	virtual void RunLevelGeneratorFunction();
};
