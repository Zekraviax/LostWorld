#pragma once


#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "Components/ScrollBox.h"
#include "Components/TextBlock.h"
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
	UButton* EndTurnButton;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (BindWidget))
	UScrollBox* CardsInHandScrollBox;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (BindWidget))
	UTextBlock* CardTargetText;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (BindWidget))
	UWidgetCard* CurrentCardBeingCast;

// ---------------------------------------- Functions ---------------------------------------- //
protected:
	virtual bool NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation) override;

public:
	UWidgetCard* CreateCardWidgetInHand(const FCard& InCard) const;
	void ResetAllCardWidgetIndices() const;
	
	void PlayerStartCastingCard(const FCard& InCard, int IndexInHand, ECardTargets CurrentTargetMode, int CurrentStackEntry) const;
	void PlayerFinishCastingCard(int IndexInHand) const;	// Also triggers if the player cancels casting a card

	UFUNCTION(BlueprintCallable)
	void PlayerClickedEndTurn();
};
