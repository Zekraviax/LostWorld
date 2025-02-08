#include "Widget_CustomConsole_Base.h"

#include "Components/TextBlock.h"
#include "Blueprint/WidgetTree.h"


// ------------------------- Widget
void UWidget_CustomConsole_Base::AddEntry(FString text)
{
	UTextBlock* ConsoleEntry = WidgetTree->ConstructWidget<UTextBlock>(UTextBlock::StaticClass(), TEXT("TextEntry"));

	ConsoleEntry->SetText(FText::FromString(text));
	ConsoleScrollBox->AddChild(ConsoleEntry);
}