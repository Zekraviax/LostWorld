// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"

#include "Components/ScrollBox.h"
#include "Components/TextBlock.h"
#include "BaseClass_CardUserWidget.h"

#include "BaseClass_Widget_ZoneSearch.generated.h"


UCLASS()
class LOSTWORLD_422_API UBaseClass_Widget_ZoneSearch : public UUserWidget
{
	GENERATED_BODY()

public:
// Base Variables
// --------------------------------------------------

// ------------------------- Components
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (BindWidget))
	UScrollBox* CardScrollBox;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (BindWidget))
	UTextBlock* ZoneName;
};
