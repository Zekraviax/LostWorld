#include "WidgetHudLevelExploration.h"


#include "LostWorldPlayerControllerBase.h"


void UWidgetHudLevelExploration::OpenDeckEditorWidget()
{
	Cast<ALostWorldPlayerControllerBase>(GetWorld()->GetFirstPlayerController())->ControlMode = EPlayerControlModes::DeckEditor;
	Cast<ALostWorldPlayerControllerBase>(GetWorld()->GetFirstPlayerController())->AddDeckEditorToViewport();
}


void UWidgetHudLevelExploration::OpenEquipmentWidget()
{
	Cast<ALostWorldPlayerControllerBase>(GetWorld()->GetFirstPlayerController())->AddEquipmentToViewport();
}


void UWidgetHudLevelExploration::OpenDevTestMenuWidget()
{
	Cast<ALostWorldPlayerControllerBase>(GetWorld()->GetFirstPlayerController())->AddDevTestMenuToViewport();
}
