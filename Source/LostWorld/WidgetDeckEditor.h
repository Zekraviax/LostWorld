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

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (BindWidget))
	UScrollBox* CardsInCollectionScrollBox;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (BindWidget))
	UUniformGridPanel* CardsInCollectionUniformGridPanel;


// ---------------------------------------- Functions ---------------------------------------- //
protected:
	virtual bool NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation) override;

public:
	void PopulateCardsInDeckUniformGridPanel(TArray<FCard> Deck) const;
	void PopulateCardsInCollectionUniformGridPanel(TArray<FCard> Collection) const;

	UFUNCTION(BlueprintCallable)
	void CloseDeckEditor();
};
