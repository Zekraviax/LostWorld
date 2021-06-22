#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TraitsFunctions_BaseClass.generated.h"


// Forward Declarations
class ABaseClass_EntityInBattle;



UCLASS()
class LOSTWORLD_422_API ATraitsFunctions_BaseClass : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATraitsFunctions_BaseClass();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;


// ------------------------- Triggered Functions
	virtual void TriggeredFunction_StartOfBattle(ABaseClass_EntityInBattle* Entity);
};
