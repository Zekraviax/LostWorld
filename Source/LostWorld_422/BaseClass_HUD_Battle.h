// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"

#include "Components/ScrollBox.h"
#include "Components/TextBlock.h"
#include "BaseClass_Widget_DeckBuilder.h"
#include "BaseClass_CardUserWidget.h"

#include "BaseClass_HUD_Battle.generated.h"

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
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (BindWidget))
	UScrollBox* CardsInHand_ScrollBox;

// ------------------------- Technical Variables
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Technical")
	ALostWorld_422GameStateBase* GameStateRef;

// ------------------------- Widgets
	// Deck Builder Class
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widget")
	TSubclassOf<UBaseClass_Widget_DeckBuilder> DeckBuilder_Class;

	// Deck Builder Instance
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Widget")
	UBaseClass_Widget_DeckBuilder* DeckBuilderRef;

	// Card Class
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widget")
	TSubclassOf<UBaseClass_CardUserWidget> Card_Class;

	// Card Instance
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Widget")
	UBaseClass_CardUserWidget* CardWidgetRef;


// Functions
// --------------------------------------------------

// ------------------------- Debug
	UFUNCTION(BlueprintCallable)
	void DebugBeginBattle();

	UFUNCTION(BlueprintCallable)
	void Test_SetPlayerData();

// ------------------------- Widget
	UFUNCTION(BlueprintCallable)
	void OpenDeckBuilder();

	UFUNCTION()
	void CreatePlayerCardsInHandWidgets(bool ClearHand, FCardBase CardInHand);

// ------------------------- Battle
	UFUNCTION(BlueprintCallable)
	void EndTurn_Function();
};
