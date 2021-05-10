#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "GameFramework/SpringArmComponent.h"
#include "Components/WidgetComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/TextRenderComponent.h"
#include "Camera/CameraComponent.h"
#include "EngineUtils.h"
#include "BaseClass_CardFunctionsLibrary.h"
#include "BaseClass_WidgetComponent_Stats.h"
#include "LostWorld_422GameModeBase.h"

#include "BaseClass_EntityInBattle.generated.h"

// Forward Declarations
class ABaseClass_PlayerController;
class ALostWorld_422GameStateBase;

// Entity In Battle:
// A class that handles the functions of an entity in battle.
// Handles entity variables such as health and mana, current cards, etc.
// Represented in the world by an EntityInWorld actor.	

UCLASS()
class LOSTWORLD_422_API ABaseClass_EntityInBattle : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABaseClass_EntityInBattle();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

// Base Variables
// --------------------------------------------------

// ------------------------- Entity
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FEntityBase EntityBaseData;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	int X_Coordinate;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	int Y_Coordinate;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TArray<FCardBase> CardsInDeck;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TArray<FCardBase> CardsInHand;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TArray<FCardBase> CardsInGraveyard;

// ------------------------- Components
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UStaticMeshComponent* StaticMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	USpringArmComponent* SpringArm;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UCameraComponent* Camera;

	// UI in World Component
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UWidgetComponent* EntityStats_WidgetComponent;

// ------------------------- Technical Variables
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	ABaseClass_PlayerController* PlayerControllerRef;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	ALostWorld_422GameModeBase* GameModeRef;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	ALostWorld_422GameStateBase* GameStateRef;

// ------------------------- Widgets
	UPROPERTY(visibleAnywhere, BlueprintReadOnly)
	UBaseClass_WidgetComponent_Stats* EntityStats_WidgetComponent_Reference;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<UBaseClass_WidgetComponent_Stats> EntityStats_WidgetComponent_Class;

// ------------------------- Timers
	UPROPERTY()
	FTimerHandle EndTurn_TimerHandle;

// Functions
// --------------------------------------------------

// ------------------------- Mouse

// ------------------------- Deck
	UFUNCTION()
	void Debug_CreateDefaultDeck();

	UFUNCTION(BlueprintImplementableEvent)
	void ShuffleCardsInDeck_BP();

// ------------------------- Components
	//UFUNCTION()
	//void ResetStatsWidget();

	UFUNCTION()
	void ResetComponentsLocations();

// ------------------------- Battle
	UFUNCTION()
	void Begin_Battle();

	UFUNCTION()
	void Begin_Turn();

	UFUNCTION()
	void UpdateCardWidgets();

	UFUNCTION()
	void UpdateCardIndicesInAllZones();

	UFUNCTION()
	void Event_CardCastOnThis();

	UFUNCTION()
	void Event_DamageIncoming(int IncomingDamage, E_Card_Elements ElementType, E_Card_DamageTypes DamageType);

// ------------------------- AI
	UFUNCTION()
	void AI_CastRandomCard();

	UFUNCTION()
	void AI_EndTurnDelay();
};
