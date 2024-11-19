#pragma once


#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "Variables.h"
#include "WidgetCard.generated.h"


UCLASS()
class LOSTWORLD_API UWidgetCard : public UUserWidget
{
	GENERATED_BODY()

public:
// ---------------------------------------- Variables ---------------------------------------- //
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	int IndexInHandArray; // this int points to the card in the player's hand

// -------------------------------- Widget components
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (BindWidget))
	UTextBlock* CardNameText;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (BindWidget))
	UImage* BackgroundImage;

	
// ---------------------------------------- Functions ---------------------------------------- //
protected:
	virtual bool NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation) override;

public:
	void UpdateComponentsFromPassedCard(const FCard& InCard) const;
};
