#pragma once


#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "WidgetPauseMenu.generated.h"


UCLASS()
class LOSTWORLD_API UWidgetPauseMenu : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	void SaveGame();
	
	UFUNCTION(BlueprintCallable)
	void LoadGame();
	
	UFUNCTION(BlueprintCallable)
	void ExitMenu();
};
