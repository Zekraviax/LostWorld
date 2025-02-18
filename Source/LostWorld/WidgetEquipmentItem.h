#pragma once


#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "Variables.h"
#include "WidgetEquipmentItem.generated.h"


UCLASS()
class LOSTWORLD_API UWidgetEquipmentItem : public UUserWidget
{
	GENERATED_BODY()

public:
// ---------------------------------------- Variables ---------------------------------------- //
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	FEquipment EquipmentItemData;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	int IndexInArray;

// -------------------------------- Widget components
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (BindWidget))
	UImage* BackgroundImage;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (BindWidget))
	UTextBlock* ItemNameText;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (BindWidget))
	UTextBlock* EquipUnequipText;


// ---------------------------------------- Functions ---------------------------------------- //
	void SetDataFromPassedEquipment(const FEquipment& Equipment);

	UFUNCTION(BlueprintCallable)
	void OnEquipmentButtonPressed();
};
