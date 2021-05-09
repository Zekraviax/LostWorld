#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"

#include "LostWorld_422GameModeBase.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Components/EditableTextBox.h"
#include "BaseClass_CardUserWidget.h"

#include "BaseClass_Widget_SpentMana.generated.h"


UCLASS()
class LOSTWORLD_422_API UBaseClass_Widget_SpentMana : public UUserWidget
{
	GENERATED_BODY()
	
public:
// Base Variables
// --------------------------------------------------

// ------------------------- Components
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UButton* AddValueButton;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UButton* SubtractValueButton;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UButton* ConfirmValueButton;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UEditableTextBox* Number_EditableBox;

// ------------------------- Mana Value
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	int32 CurrentManaValue;

// ------------------------- Card
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UBaseClass_CardUserWidget* CardReference;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	ACardAbilityActor_BaseClass* CurrentCardFunctionClass;

	// ------------------------- Technical Variables
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<UBaseClass_CardUserWidget> CardWidget_Class;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UDataTable* CardsTable;


// Functions
// --------------------------------------------------

	UFUNCTION()
	void OnWidgetCreated();

	UFUNCTION(BlueprintCallable)
	void ConfirmManaValue();

// ------------------------- Mana Value
	UFUNCTION(BlueprintCallable)
	void ChangeManaValue(int32 NewValue);

// ------------------------- Text
	UFUNCTION(BlueprintCallable)
	void CheckInputText(FText Text);
};