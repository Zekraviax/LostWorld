// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"

#include "BaseClass_Widget_DeckBuilder.h"
#include "Components/ScrollBox.h"
#include "BaseClass_CardUserWidget.h"

#include "BaseClass_HUD_Battle.generated.h"

class ALostWorld_422GameStateBase;

/**
 * 
 */
UCLASS()
class LOSTWORLD_422_API UBaseClass_HUD_Battle : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct();

protected:

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Data - Technical")
	ALostWorld_422GameStateBase* GameStateRef;

	// Deck builder Class
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data - Class")
	TSubclassOf<UBaseClass_Widget_DeckBuilder> DeckBuilder_Class;

	// Deck builder Instance
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Data - Technical")
	UBaseClass_Widget_DeckBuilder* DeckBuilderRef;

	// Deck builder Class
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data - Class")
	TSubclassOf<UBaseClass_CardUserWidget> Card_Class;

	// Deck builder Instance
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Data - Technical")
	UBaseClass_CardUserWidget* CardWidgetRef;

	UPROPERTY(meta = (BindWidget))
	UScrollBox* CardsInHand_ScrollBox;

	UFUNCTION(BlueprintCallable)
	void DebugBeginBattle();

	UFUNCTION(BlueprintCallable)
	void Test_SetPlayerData();

	UFUNCTION(BlueprintCallable)
	void OpenDeckBuilder();

	UFUNCTION()
	void CreatePlayerCardsInHandWidgets(bool ClearHand, FCardBase CardInHand);

	// Battle Functions
	UFUNCTION(BlueprintCallable)
	void EndTurn_Function();
};
