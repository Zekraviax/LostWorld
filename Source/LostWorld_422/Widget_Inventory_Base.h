#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"

#include "Components/ScrollBox.h"

#include "Widget_Inventory_Base.generated.h"

// Forward Declarations
class ABaseClass_EntityInBattle;
class ABaseClass_PlayerController;
class UWidgetComponent_Inventory_Item_Base;


UCLASS()
class LOSTWORLD_422_API UWidget_Inventory_Base : public UUserWidget
{
	GENERATED_BODY()
	
public:
// Variables
// --------------------------------------------------

// ------------------------- Components
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (BindWidget))
	UScrollBox* EquippedItemsScrollBox;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (BindWidget))
	UScrollBox* UnequippedItemsScrollBox;

// ------------------------- Widget
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<UWidgetComponent_Inventory_Item_Base> InventoryItem_Class;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UWidgetComponent_Inventory_Item_Base* InventoryItem_Reference;

// ------------------------- References
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	ABaseClass_EntityInBattle* PlayerEntityReference;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	ABaseClass_PlayerController* PlayerControllerReference;

// Functions
// --------------------------------------------------

// ------------------------- Widget
	UFUNCTION()
	void OnInventoryOpened(ABaseClass_PlayerController* PlayerController = nullptr);
};
