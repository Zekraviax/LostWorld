#include "WidgetHudLevelExploration.h"


#include "LostWorldPlayerControllerBase.h"


void UWidgetHudLevelExploration::OpenDeckEditorWidget()
{
	Cast<ALostWorldPlayerControllerBase>(GetWorld()->GetFirstPlayerController())->AddDeckEditorToViewport();
}
