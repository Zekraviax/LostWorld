#pragma once


#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/ScrollBox.h"
#include "Components/UniformGridPanel.h"
#include "Variables.h"
#include "WidgetDeckEditor.generated.h"


class UWidgetCard;


UCLASS()
class LOSTWORLD_API UWidgetDeckEditor : public UUserWidget
{
	GENERATED_BODY()

public:
// ---------------------------------------- Variables ---------------------------------------- //
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<UWidgetCard> CardWidgetBlueprintClass;

// -------------------------------- Widget components
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (BindWidget))
	UScrollBox* CardsInDeckScrollBox;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (BindWidget))
	UUniformGridPanel* CardsInDeckUniformGridPanel;

	//UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (BindWidget))
	//UScrollBox* CardsInCollectionScrollBox;


// ---------------------------------------- Functions ---------------------------------------- //
	void PopulateCardsInDeckUniformGridPanel(TArray<FCard> Deck) const;

	UFUNCTION(BlueprintCallable)
	void CloseDeckEditor();
};
