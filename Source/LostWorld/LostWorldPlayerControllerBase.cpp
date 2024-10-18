#include "LostWorldPlayerControllerBase.h"

#include "WidgetHudBattle.h"
#include "WidgetHudLevelExploration.h"


void ALostWorldPlayerControllerBase::AddBattleHudToViewport()
{
	if (LevelHudWidget) {
		if (LevelHudWidget->IsInViewport()) {
			LevelHudWidget->RemoveFromViewport();
		}
	}
	
	if (BattleHudWidgetBlueprintClass && !BattleHudWidget) {
		BattleHudWidget = CreateWidget<UWidgetHudBattle>(GetWorld(), BattleHudWidgetBlueprintClass);
	}

	if (BattleHudWidget) {
		BattleHudWidget->AddToViewport();
	}
}


void ALostWorldPlayerControllerBase::AddLevelHudToViewport()
{
	if (BattleHudWidget) {
		if (BattleHudWidget->IsInViewport()) {
			BattleHudWidget->RemoveFromViewport();
		}
	}
	
	if (LevelHudWidgetBlueprintClass && !LevelHudWidget) {
		LevelHudWidget = CreateWidget<UWidgetHudLevelExploration>(GetWorld(), LevelHudWidgetBlueprintClass);
	}

	if (LevelHudWidget) {
		LevelHudWidget->AddToViewport();
	}
}
