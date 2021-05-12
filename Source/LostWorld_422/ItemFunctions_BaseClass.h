#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ItemFunctions_BaseClass.generated.h"

// Forward Declarations
class ABaseClass_EntityInBattle;


UCLASS()
class LOSTWORLD_422_API AItemFunctions_BaseClass : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AItemFunctions_BaseClass();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;


// Base Variables
// --------------------------------------------------

// ------------------------- Constructors


// ------------------------- Widgets

// Functions
// --------------------------------------------------

// ------------------------- Base Class Functions
	virtual void RunItemAbilityFunction();

// ------------------------- Widget Functions


// ------------------------- Triggered Functions
	virtual void TriggeredFunction_OnItemEquipped(ABaseClass_EntityInBattle* EquippedEntity);
	virtual void TriggeredFunction_StarterOfWearerTurn(ABaseClass_EntityInBattle* EquippedEntity);
};