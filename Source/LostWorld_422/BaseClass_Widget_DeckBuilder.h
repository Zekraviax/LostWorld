#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"

#include "LostWorld_422GameModeBase.h"
#include "Components/ScrollBox.h"
#include "Components/WidgetComponent.h"
#include "BaseClass_Widget_DeckBuilderCard.h"

#include "BaseClass_Widget_DeckBuilder.generated.h"


// Forward Declaration
class ABaseClass_PlayerController;
class UBaseClass_HUD_Battle;
class UBaseClass_HUD_Level;


UCLASS()
class LOSTWORLD_422_API UBaseClass_Widget_DeckBuilder : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct();

public:
// Variables
// --------------------------------------------------

// ------------------------- Components
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (BindWidget))
	UScrollBox* CurrentDeck_ScrollBox;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (BindWidget))
	UScrollBox* CurrentCollection_ScrollBox;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	ABaseClass_PlayerController* PlayerControllerRef;

// ------------------------- Technical Variables
	// The instance of the DeckBuilderCard 
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UBaseClass_Widget_DeckBuilderCard* DeckBuilderCard_Widget;

	// The class that will be used for the DeckBuilderCard
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<UBaseClass_Widget_DeckBuilderCard> DeckBuilderCard_Class;

	UPROPERTY()
	bool TestUnlimitedCardsMode;

	UPROPERTY()
	ALostWorld_422GameModeBase* GameModeRef;

	UPROPERTY()
	UBaseClass_HUD_Level* HUDRef;

// Functions
// --------------------------------------------------

// ------------------------- Components
	UFUNCTION(BlueprintCallable)
	void PopulateScrollBoxes();

	UFUNCTION(BlueprintCallable)
	void AddSingleCardToZone(FCardBase ChosenCard, E_DeckBuilder_Zone ChosenZone);

// ------------------------- Debug
	UFUNCTION(BlueprintCallable)
	void Test_Activate_UnlimitedCards();

	UFUNCTION(BlueprintCallable)
	void Test_Dectivate_UnlimitedCards();

// ------------------------- Other
	UFUNCTION(BlueprintCallable)
	void ExitDeckBuilder();
};
