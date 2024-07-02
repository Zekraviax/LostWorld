#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Widget_LevelSelectScreen.generated.h"


UENUM(BlueprintType)
enum class E_Levels : uint8
{
	TestLevel			UMETA(DisplayName = "Test Level"),
};


UCLASS()
class LOSTWORLD_422_API UWidget_LevelSelectScreen : public UUserWidget
{
	GENERATED_BODY()

public:
// Variables
// --------------------------------------------------

// ------------------------- Components

// Functions
// --------------------------------------------------

// ------------------------- Widget Functions
	UFUNCTION(BlueprintCallable)
	void OnLevelSelected(E_Levels SelectedLevel);
};