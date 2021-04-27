#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"

#include "Components/ScrollBox.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"
#include "BaseClass_Widget_DeckBuilder.h"
#include "BaseClass_CardUserWidget.h"

#include "BaseClass_HUD_Battle.generated.h"


// Forward Declarations
class ALostWorld_422GameStateBase;


// Class-Specific Enums
UENUM(BlueprintType)
enum class E_ContinueTurnButton_Function : uint8
{
	E_EndTurn,
	E_ContinueTurn,
};


UCLASS()
class LOSTWORLD_422_API UBaseClass_HUD_Battle : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct();

protected:

public:
// Base Variables
// --------------------------------------------------

// ------------------------- Components
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (BindWidget))
	UScrollBox* CardsInHand_ScrollBox;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (BindWidget))
	UButton* GraveyardButton;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (BindWidget))
	UButton* DeckButton;

// ------------------------- Technical Variables
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	ALostWorld_422GameStateBase* GameStateRef;

// ------------------------- Widgets
	// Deck Builder Class
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<UBaseClass_Widget_DeckBuilder> DeckBuilder_Class;

	// Deck Builder Instance
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UBaseClass_Widget_DeckBuilder* DeckBuilderRef;

	// Card Class
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<UBaseClass_CardUserWidget> Card_Class;

	// Card Instance
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UBaseClass_CardUserWidget* CardWidgetRef;


// Functions
// --------------------------------------------------

// ------------------------- Debug
	UFUNCTION(BlueprintCallable)
	void DebugBeginBattle();

	UFUNCTION(BlueprintCallable)
	void Test_SetPlayerData();

// ------------------------- Widgets
	UFUNCTION(BlueprintCallable)
	void OpenDeckBuilder();

	UFUNCTION()
	void CreatePlayerCardsInHandWidgets(bool ClearHand, FCardBase CardInHand);

// ------------------------- Battle
	UFUNCTION(BlueprintCallable)
	void EndTurn_Function();
};
