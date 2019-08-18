// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "Components/StaticMeshComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "BaseClass_EntityInBattle.h"
#include "Components/TextRenderComponent.h"
#include "LostWorld_422GameModeBase.h"

#include "BaseClass_EntityInWorld.generated.h"

// Forward Declarations
class ABaseClass_PlayerController;

// Entity In World:
// A physical actor that can interact with the world.
// Mostly a physical representation of an EntityInBattle.
// Doesn't do much on it's own.
// (Attached to a grid tile for the most part)

UCLASS()
class LOSTWORLD_422_API ABaseClass_EntityInWorld : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABaseClass_EntityInWorld();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// EntityInBattle reference
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Data - Technical")
	ABaseClass_EntityInBattle* EntityInBattleRef;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Data - Technical")
	TSubclassOf<ABaseClass_EntityInBattle> EntityInBattle_Class;

	// Components
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Data - Components")
	UStaticMeshComponent* StaticMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Data - Components")
	USpringArmComponent* SpringArm;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data - Components")
	UCameraComponent* Camera;

	// UI in World Components
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Data - Components")
	UTextRenderComponent* HealthText_WorldRender;

	// Player Controller
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Data - Technical")
	ABaseClass_PlayerController* PlayerControllerRef;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Data - Entity")
	FEntityBase EntityBaseData;

	// Mouse Events
	UFUNCTION(BlueprintCallable)
	void CustomOnBeginMouseOverEvent(UPrimitiveComponent* TouchedComponent);

	UFUNCTION()
	void CreateEntityInBattle();
};
