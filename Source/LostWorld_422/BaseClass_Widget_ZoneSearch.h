#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"

#include "LostWorld_422GameModeBase.h"
#include "Components/ScrollBox.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"
#include "BaseClass_CardUserWidget.h"

#include "BaseClass_Widget_ZoneSearch.generated.h"


// Unique Enum
UENUM(BlueprintType)
enum class E_ZoneSearch_Functions : uint8
{
	E_DrawCards,
};


UCLASS()
class LOSTWORLD_422_API UBaseClass_Widget_ZoneSearch : public UUserWidget
{
	GENERATED_BODY()

public:
// Base Variables
// --------------------------------------------------

// ------------------------- Components
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (BindWidget))
	UScrollBox* CardScrollBox;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (BindWidget))
	UTextBlock* ZoneName;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (BindWidget))
	UButton* Confirm_Button;

// ------------------------- Widgets
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<class UBaseClass_CardUserWidget> CardWidget_Class;

// ------------------------- Function Variables
	UPROPERTY()
	E_ZoneSearch_Functions Function;

// ------------------------- Cards
	UPROPERTY()
	TArray<FCardBase> ChosenCards;

	UPROPERTY()
	int32 CurrentMaxCardSelectCount;

// Functions
// --------------------------------------------------
	UFUNCTION()
	void PopulateWidget(TArray<FCardBase> Cards, int32 MaxCardSelectCount, E_ZoneSearch_Functions ConfirmButtonFunction, E_Card_Zones SearchZone);

	UFUNCTION(BlueprintCallable)
	void ConfirmButton_Function(TArray<FCardBase> &ReturnChosenCards);
};
