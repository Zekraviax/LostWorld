#include "BaseClass_HUD_Level.h"


void UBaseClass_HUD_Level::OpenDeckBuilder()
{
	if (DeckBuilder_Class && !DeckBuilderRef)
	{
		DeckBuilderRef = CreateWidget<UBaseClass_Widget_DeckBuilder>(GetWorld(), DeckBuilder_Class);
		DeckBuilderRef->HUDRef = this;
		DeckBuilderRef->PopulateScrollBoxes();
		DeckBuilderRef->AddToViewport();
	}
}