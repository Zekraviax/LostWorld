#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Widget_HUD_City_Base.generated.h"


class UWidget_LevelSelectScreen;


UCLASS()
class LOSTWORLD_422_API UWidget_HUD_City_Base : public UUserWidget
{
	GENERATED_BODY()
	
public:
// Variables
// --------------------------------------------------

// ------------------------- Widgets
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<UWidget_LevelSelectScreen> LevelSelectWidgetBlueprintClass;

// Functions
// --------------------------------------------------

// ------------------------- Widget Functions
	UFUNCTION(BlueprintCallable)
	void OnLeaveCityButtonPressed();
};
