#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TraitFunctions_BaseClass.generated.h"


// Forward Declarations
class ABaseClass_EntityInBattle;



UCLASS()
class LOSTWORLD_422_API ATraitFunctions_BaseClass : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATraitFunctions_BaseClass();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;


// ------------------------- Triggered Functions
	virtual void TriggeredFunction_StartOfBattle(ABaseClass_EntityInBattle* Entity);
};
