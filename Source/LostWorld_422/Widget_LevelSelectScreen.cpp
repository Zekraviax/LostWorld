#include "Widget_LevelSelectScreen.h"


#include "Kismet/GameplayStatics.h"


void UWidget_LevelSelectScreen::OnLevelSelected(E_Levels SelectedLevel)
{
	switch (SelectedLevel)
	{
	case(E_Levels::TestLevel):
		UGameplayStatics::OpenLevel(GetWorld(), "Test Level");
		break;
	default:
		break;
	}
}