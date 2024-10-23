#pragma once


#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/ScrollBox.h"
#include "Variables.h"
#include "WidgetHudBattle.generated.h"


class UWidgetCard;


UCLASS()
class LOSTWORLD_API UWidgetHudBattle : public UUserWidget
{
	GENERATED_BODY()

public:
// ---------------------------------------- Variables ---------------------------------------- //
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<UWidgetCard> CardWidgetBlueprintClass;

// -------------------------------- Widget components
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (BindWidget))
	UScrollBox* CardsInHandScrollBox;

// ---------------------------------------- Functions ---------------------------------------- //
	void CreateCardWidgetInHand(FCard InCard);
};
