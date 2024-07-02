#pragma once

#include "CoreMinimal.h"

#include "Kismet/BlueprintFunctionLibrary.h"
#include "Widget_Inventory_Base.h"


class LOSTWORLD_422_API FunctionLibrary_Widgets
{
public:
	FunctionLibrary_Widgets();
	~FunctionLibrary_Widgets();

// Inventory
// --------------------------------------------------
	static TSubclassOf<UWidget_Inventory_Base> Inventory_Class;
	static UWidget_Inventory_Base* Inventory_Reference;

	UFUNCTION(BlueprintCallable, meta = (WorldContext = "WorldContextObject"))
	static UWidget_Inventory_Base* GetInventory(const UObject* WorldContextObject);
};
