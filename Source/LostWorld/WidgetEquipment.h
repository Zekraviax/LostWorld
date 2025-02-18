#pragma once


#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/ScrollBox.h"
#include "Variables.h"
#include "WidgetEquipment.generated.h"


class UWidgetEquipmentItem;


UCLASS()
class LOSTWORLD_API UWidgetEquipment : public UUserWidget
{
	GENERATED_BODY()

public:
// ---------------------------------------- Variables ---------------------------------------- //
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<UWidgetEquipmentItem> EquipmentItemWidgetBlueprintClass;

// -------------------------------- Widget components
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (BindWidget))
	UScrollBox* EquippedItemsScrollBox;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (BindWidget))
	UScrollBox* UnequippedItemsScrollBox;

	
// ---------------------------------------- Functions ---------------------------------------- //
	void PopulateEquippedItemsScrollBox(TArray<FEquipment> EquippedItems) const;
	void PopulateUnequippedItemsScrollBox(TArray<FEquipment> UnequippedItems) const;

	UFUNCTION(BlueprintCallable)
	void CloseEquipmentWidget();
};
