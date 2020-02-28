// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"

#include "Components/ScrollBox.h"
#include "Components/TextBlock.h"
#include "BaseClass_Widget_DeckBuilder.h"
#include "BaseClass_CardUserWidget.h"
#include "LostWorld_422GameModeBase.h"

#include "BaseClass_HUD_Level.generated.h"


UCLASS()
class LOSTWORLD_422_API UBaseClass_HUD_Level : public UUserWidget
{
	GENERATED_BODY()

public:

protected:

public:
// Base Variables
// --------------------------------------------------

// ------------------------- Components
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (BindWidget))
	UScrollBox* EncounterList_ScrollBox;

// ------------------------- Room Features
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Features")
	TArray<E_LevelRoom_EncounterTypes> EncounterList;

// Functions
// --------------------------------------------------

// ------------------------- Debug
	
};
