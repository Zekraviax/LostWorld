// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"

#include "LostWorld_422GameModeBase.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"

#include "BaseClass_Widget_DeckBuilderCard.generated.h"

// Forward Declarations
class ABaseClass_PlayerController;
class UBaseClass_Widget_DeckBuilder;


UENUM(BlueprintType)
enum class E_DeckBuilder_Zone : uint8
{
	E_Deck,
	E_Collection,
};


UCLASS()
class LOSTWORLD_422_API UBaseClass_Widget_DeckBuilderCard : public UUserWidget
{
	GENERATED_BODY()
	
public:
// Base Variables
// --------------------------------------------------

// ------------------------- Components
	UPROPERTY(meta = (BindWidget))
	UButton* InteractButton;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* NameText;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* QuantityText;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* InteractButtonText;

// ------------------------- Technical
	UPROPERTY()
	ABaseClass_PlayerController* PlayerControllerRef;

	UPROPERTY()
	E_DeckBuilder_Zone DeckBuilderZone;

	UPROPERTY()
	UBaseClass_Widget_DeckBuilder* DeckBuilderWidgetRef;

// ------------------------- Card
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Card")
	FCardBase CardDataRef;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Card")
	int32 QuantityBind;

// Functions
// --------------------------------------------------

// ------------------------- Bind
	UFUNCTION(BlueprintCallable)
	void BindInfo();

// ------------------------- Card
	UFUNCTION(BlueprintCallable)
	void InteractFunction();
};
