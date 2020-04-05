#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "LostWorld_422GameModeBase.h"

#include "BaseClass_CardInstanceActor.generated.h"

UCLASS()
class LOSTWORLD_422_API ABaseClass_CardInstanceActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABaseClass_CardInstanceActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

// Base Variables
// --------------------------------------------------

// Functions
// --------------------------------------------------
	UFUNCTION()
	void ExecuteCardAbility(FCardAbilitiesAndConditions AbilityAndConditions);

};
