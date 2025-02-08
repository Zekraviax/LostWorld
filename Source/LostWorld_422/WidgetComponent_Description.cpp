#include "WidgetComponent_Description.h"


void UWidgetComponent_Description::SetDescriptionText(FString TextAsString)
{
	DescriptionText->SetText(FText::FromString(TextAsString));
}