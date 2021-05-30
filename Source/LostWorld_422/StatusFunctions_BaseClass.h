#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "StatusFunctions_BaseClass.generated.h"


// Forward Declarations
class ABaseClass_EntityInBattle;


UCLASS()
class LOSTWORLD_422_API AStatusFunctions_BaseClass : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AStatusFunctions_BaseClass();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;


// ------------------------- Passive Functions
	virtual void PassiveFunction_OnStatusEffectBegin(ABaseClass_EntityInBattle* AffectedEntity);	// Apply status effect changes
	virtual void PassiveFunction_OnStatusEffectEnd(ABaseClass_EntityInBattle* AffectedEntity);		// Undo status effect changes

// ------------------------- Triggered Functions
	virtual void TriggeredFunction_StarterOfEntityTurn(ABaseClass_EntityInBattle* AffectedEntity);
	virtual int TriggeredFunction_EntityAboutToTakeDamage(ABaseClass_EntityInBattle* AffectedEntity, int IncomingDamate);		// Triggeres when the entity is *about to* take damage
};
