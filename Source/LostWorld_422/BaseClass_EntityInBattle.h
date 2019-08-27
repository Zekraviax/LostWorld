// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "LostWorld_422GameModeBase.h"
#include "Components/StaticMeshComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Components/TextRenderComponent.h"

#include "BaseClass_EntityInBattle.generated.h"

// Forward Declarations
class ABaseClass_EntityInWorld;
class ABaseClass_PlayerController;

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

	// Entity Data
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Entity")
	FEntityBase EntityBaseData;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Technical")
	ABaseClass_EntityInWorld* EntityInWorldRef;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Entity")
	TArray<FCardBase> CardsInDeck;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Entity")
	TArray<FCardBase> CardsInHand;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Entity")
	TArray<FCardBase> CardsInGraveyard;

	// Components
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UStaticMeshComponent* StaticMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	USpringArmComponent* SpringArm;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	UCameraComponent* Camera;

	// UI in World Components
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UTextRenderComponent* HealthText_WorldRender;

	// Player Controller
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Technical")
	ABaseClass_PlayerController* PlayerControllerRef;

	//UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Entity")
	//FEntityBase EntityBaseData;

	// Mouse Events
	UFUNCTION(BlueprintCallable)
	void CustomOnBeginMouseOverEvent(UPrimitiveComponent* TouchedComponent);

	UFUNCTION()
	void Debug_CreateDefaultDeck();

	UFUNCTION(BlueprintImplementableEvent)
	void ShuffleCardsInDeck_BP();

	UFUNCTION()
	void Begin_Battle();

	UFUNCTION()
	void Begin_Turn();

	UFUNCTION()
	void UpdateCardIndicesInAllZones();

	UFUNCTION()
	void AI_CastRandomCard();
};
