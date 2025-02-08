#include "Widget_HUD_City_Base.h"


#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Widget_LevelSelectScreen.h"


void UWidget_HUD_City_Base::OnLeaveCityButtonPressed()
{
	// Find a pre-existing widget
	// If there is none, create one
	TArray<UUserWidget*> LevelSelectWidgets;
	UWidgetBlueprintLibrary::GetAllWidgetsOfClass(GetWorld(), LevelSelectWidgets, UWidget_LevelSelectScreen::StaticClass(), false);
	UWidget_LevelSelectScreen* LevelSelectWidget = nullptr;

	if (LevelSelectWidgets.Num() < 1 && LevelSelectWidgetBlueprintClass) {
		LevelSelectWidget = CreateWidget<UWidget_LevelSelectScreen>(GetWorld(), LevelSelectWidgetBlueprintClass);
	} else if (LevelSelectWidgets.Num() > 0) {
		LevelSelectWidget = Cast<UWidget_LevelSelectScreen>(LevelSelectWidgets[0]);
	}

	LevelSelectWidget->AddToViewport();
}