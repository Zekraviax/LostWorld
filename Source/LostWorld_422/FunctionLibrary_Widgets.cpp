#include "FunctionLibrary_Widgets.h"

#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Widget_Inventory_Base.h"


FunctionLibrary_Widgets::FunctionLibrary_Widgets()
{
}

FunctionLibrary_Widgets::~FunctionLibrary_Widgets()
{
}


// ------------------------- Inventory
UWidget_Inventory_Base* FunctionLibrary_Widgets::GetInventory(const UObject * WorldContextObject)
{
	UWorld* World = GEngine->GameViewport->GetWorld();

	if (!Inventory_Reference) {
		//Inventory_Reference = CreateWidget<UWidget_Inventory_Base>(World, Inventory_Class);
	}

	return nullptr;
}