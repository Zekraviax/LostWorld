#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"

#include "Components/TextBlock.h"
#include "Components/Button.h"
#include "LostWorld_422GameModeBase.h"

#include "WidgetComponent_Inventory_Item_Base.generated.h"


// Forward Declarations
class UWidgetComponent_Description;


UCLASS()
class LOSTWORLD_422_API UWidgetComponent_Inventory_Item_Base : public UUserWidget
{
	GENERATED_BODY()

public:
// Variables
// --------------------------------------------------

// ------------------------- Components
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UButton* ItemEquipButton;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* ItemEquipText;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* ItemNameText;

// ------------------------- Widgets
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<UWidgetComponent_Description> DescriptionWidgetBlueprintClass;

// ------------------------- Item
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool StaticEquipmentSlot;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	E_Item_EquipSlots StaticEquipmentSlotType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	F_Item_Base ItemData;

// Functions
// --------------------------------------------------

// ------------------------- Item
	UFUNCTION(BlueprintCallable)
	void OnEquipButtonPressed();

// ------------------------- Widget
	UFUNCTION(BlueprintCallable)
	void UpdateWidget();

	UFUNCTION(BlueprintCallable)
	void OnMouseHoverOverBegin();

	UFUNCTION(BlueprintCallable)
	void OnMouseHoverOverEnd();
};
