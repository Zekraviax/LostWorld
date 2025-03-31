#pragma once


#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"
#include "Components/Image.h"
#include "CoreMinimal.h"
#include "Variables.h"

#include "WidgetPlayerPrompt.generated.h"


UENUM(BlueprintType)
enum class EPromptType : uint8
{
	SpendManaOnXCostSpell,
};


/** A jack-of-all-trades widget that does the following:
Allows the player to decide how much mana to spend on X cost spells.
Warns the player when they are about to leave a menu without saving their changes.
*/
UCLASS()
class LOSTWORLD_API UWidgetPlayerPrompt : public UUserWidget
{
	GENERATED_BODY()

public:
// ---------------------------------------- Variables ---------------------------------------- //
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	EPromptType CurrentPromptType;

	// Used for things such as incrementing and decrementing the MP the player will spend on an X spell.
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	int LocalVar;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	FCard LocalCard;

	int LocalIndexInHand;

// -------------------------------- Widget components
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (BindWidget))
	UImage* BackgroundImage;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (BindWidget))
	UTextBlock* Title;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (BindWidget))
	UTextBlock* Body;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (BindWidget))
	UButton* LeftButton;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (BindWidget))
	UTextBlock* LeftButtonText;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (BindWidget))
	UButton* RightButton;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (BindWidget))
	UTextBlock* RightButtonText;

	// Accept the prompt.
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (BindWidget))
	UButton* ConfirmButton;

	// Close the prompt without changing anything.
	// No discarding or saving changes.
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (BindWidget))
	UButton* CancelButton;

// -------------------------------- Default variables for widget components
	// To-Do: Make a json file for widget default variables?
	int TitleFontSize = 24;
	int BodyFontSize = 16;

	FVector2D BackgroundImageDimension = FVector2D(600, 300);

// ---------------------------------------- Functions ---------------------------------------- //
	void SetUpPrompt(EPromptType InPromptType, const FCard& InCard, int IndexInHand);
	void SpendManaOnXCostSpell();

// -------------------------------- Widget components
	UFUNCTION(BlueprintCallable)
	void OnLeftButtonPressed();

	UFUNCTION(BlueprintCallable)
	void OnRightButtonPressed();
	
	UFUNCTION(BlueprintCallable)
	void OnConfirmButtonPressed();

	UFUNCTION(BlueprintCallable)
	void OnCancelButtonPressed();
};
