#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "GameFramework/SpringArmComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/TextRenderComponent.h"
#include "Camera/CameraComponent.h"
#include "BaseClass_EntityInBattle.h"
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

// Base Variables
// --------------------------------------------------

// ------------------------- Entity
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	FEntityBase EntityBaseData;

// ------------------------- Technical Variables
	// EntityInBattle reference
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	ABaseClass_EntityInBattle* EntityInBattleRef;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TSubclassOf<ABaseClass_EntityInBattle> EntityInBattle_Class;

	// Player Controller
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	ABaseClass_PlayerController* PlayerControllerRef;

// ------------------------- Components
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UStaticMeshComponent* StaticMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	USpringArmComponent* SpringArm;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UCameraComponent* Camera;

	// UI in World Components
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UTextRenderComponent* HealthText_WorldRender;

// Functions
// --------------------------------------------------

// ------------------------- Mouse
	UFUNCTION(BlueprintCallable)
	void CustomOnBeginMouseOverEvent(UPrimitiveComponent* TouchedComponent);

// ------------------------- Entity
	UFUNCTION()
	void CreateEntityInBattle();
};
