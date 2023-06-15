#pragma once

#include "CoreMinimal.h"

#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"

#include "WidgetComponent_Description.generated.h"


UCLASS()
class LOSTWORLD_422_API UWidgetComponent_Description : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* DescriptionText;

	UFUNCTION(BlueprintCallable)
	void SetDescriptionText(FString TextAsString);
};
