#pragma once


#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "WidgetHudLevelExploration.generated.h"


UCLASS()
class LOSTWORLD_API UWidgetHudLevelExploration : public UUserWidget
{
	GENERATED_BODY()

public:
// ---------------------------------------- Variables ---------------------------------------- //

	
// ---------------------------------------- Functions ---------------------------------------- //
	UFUNCTION(BlueprintCallable)
	void OpenDeckEditorWidget();

	UFUNCTION(BlueprintCallable)
	void OpenEquipmentWidget();
};
