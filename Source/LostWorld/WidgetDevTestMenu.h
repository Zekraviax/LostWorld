#pragma once


#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "Components/ComboBoxString.h"
#include "WidgetDevTestMenu.generated.h"


UCLASS()
class LOSTWORLD_API UWidgetDevTestMenu : public UUserWidget
{
	GENERATED_BODY()
	
public:
// ---------------------------------------- Variables ---------------------------------------- //

// -------------------------------- Widget components
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (BindWidget))
	UComboBoxString* AddCardsToCollectionDropDown;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (BindWidget))
	UButton* AddCardsToCollectionButton;
	
// ---------------------------------------- Functions ---------------------------------------- //

// -------------------------------- Widget functions
	void OnDevTestMenuWidgetOpened() const;
	void AddCardNamesToCardDropDown() const;

// -------------------------------- Test functions
	UFUNCTION(BlueprintCallable)
	void AddCardToDeck(const FString& CardDisplayName) const;
};
