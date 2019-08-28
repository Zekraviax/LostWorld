// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"

#include "LostWorld_422GameModeBase.h"
#include "BaseClass_HUD_Battle.h"
#include "BaseClass_EntityInWorld.h"
#include "BaseClass_EntityInBattle.h"
#include "BaseClass_CardUserWidget.h"

#include "BaseClass_PlayerController.generated.h"

// Forward Declarations
//class UBaseClass_HUD_Battle;

UCLASS()
class LOSTWORLD_422_API ABaseClass_PlayerController : public APlayerController
{
	GENERATED_BODY()

protected:
	virtual void SetupInputComponent() override;

	// BeginPlay function
	virtual void BeginPlay() override;

	ABaseClass_PlayerController();

public:
	virtual void Tick(float DeltaTime) override;

// Base Variables
// --------------------------------------------------

// ------------------------- Entity
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Entity")
	FEntityBase CurrentEntityData;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Entity")
	TArray<FCardBase> CurrentCollection;

// ------------------------- Technical Variables
	// Player EntityInBattle class
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Technical")
	class ABaseClass_EntityInBattle* EntityInBattleRef;

	// Player EntityInBattle instance
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Technical")
	TSubclassOf<ABaseClass_EntityInBattle> EntityInBattle_Class;

// ------------------------- Widget
	// The instance of the players Inventory UI Widget
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Technical")
	class UBaseClass_HUD_Battle* Battle_HUD_Widget;

	// The class that will be used for the players Inventory UI
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Technical")
	TSubclassOf<class UBaseClass_HUD_Battle> Battle_HUD_Class;

	// The instance of the DeckBuilderCard 
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Widget")
	UBaseClass_CardUserWidget* Card_Widget;

	// The class that will be used for the DeckBuilderCard
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widget")
	TSubclassOf<UBaseClass_CardUserWidget> Card_Class;

	// Dragging Card Widget Reference
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Widget")
	UBaseClass_CardUserWidget* CurrentDragCardRef;

	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data - Setup")
	//FEntityBase TestData;

// Functions
// --------------------------------------------------

// ------------------------- Mouse
	UFUNCTION(BlueprintCallable)
	void CustomOnLeftMouseButtonUpEvent();
};