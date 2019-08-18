// Fill out your copyright notice in the Description page of Project Settings.

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

UCLASS()
class LOSTWORLD_422_API UBaseClass_Widget_DeckBuilder : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct();

	//virtual TSharedRef<SWidget> RebuildWidget();

protected:

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Data - Technical")
	ABaseClass_PlayerController* PlayerControllerRef;

	UPROPERTY(meta = (BindWidget))
	UScrollBox* CurrentDeck_ScrollBox;

	UPROPERTY(meta = (BindWidget))
	UScrollBox* CurrentCollection_ScrollBox;

	// The instance of the DeckBuilderCard 
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Data - Technical")
	UBaseClass_Widget_DeckBuilderCard* DeckBuilderCard_Widget;

	// The class that will be used for the DeckBuilderCard
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data - Technical")
	TSubclassOf<UBaseClass_Widget_DeckBuilderCard> DeckBuilderCard_Class;

	UPROPERTY()
	bool TestUnlimitedCardsMode;

	UPROPERTY()
	ALostWorld_422GameModeBase* GameModeRef;

	UPROPERTY()
	UBaseClass_HUD_Battle* HUDRef;

	UFUNCTION(BlueprintCallable)
	void PopulateScrollBoxes();

	UFUNCTION(BlueprintCallable)
	void AddSingleCardToZone(FCardBase ChosenCard, E_DeckBuilder_Zone ChosenZone);

	UFUNCTION(BlueprintCallable)
	void Test_Activate_UnlimitedCards();

	UFUNCTION(BlueprintCallable)
	void Test_Dectivate_UnlimitedCards();

	UFUNCTION(BlueprintCallable)
	void ExitDeckBuilder();
};
