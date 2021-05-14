#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"

#include "Components/TextBlock.h"
#include "Components/Button.h"
#include "LostWorld_422GameModeBase.h"

#include "WidgetComponent_Inventory_Item_Base.generated.h"


UCLASS()
class LOSTWORLD_422_API UWidgetComponent_Inventory_Item_Base : public UUserWidget
{
	GENERATED_BODY()

public:
// Variables
// --------------------------------------------------

// ------------------------- Components
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (BindWidget))
	UButton* ItemEquipButton;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (BindWidget))
	UTextBlock* ItemEquipText;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (BindWidget))
	UTextBlock* ItemNameText;

// ------------------------- Widget
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool StaticEquipmentSlot;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	E_Item_EquipSlots StaticEquipmentSlotType;

// ------------------------- Item
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	F_Item_Base ItemData;

// Functions
// --------------------------------------------------

// ------------------------- Item
	UFUNCTION(BlueprintCallable)
	void OnEquipButtonPressed();

// ------------------------- Widget
	UFUNCTION()
	void UpdateWidget();
};
