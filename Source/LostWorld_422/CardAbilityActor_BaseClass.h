#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "LostWorld_422GameModeBase.h"

#include "CardAbilityActor_BaseClass.generated.h"

UCLASS()
class LOSTWORLD_422_API ACardAbilityActor_BaseClass : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACardAbilityActor_BaseClass();

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
	virtual void RunCardAbilityFunction(FStackEntry StackEntry);

// ------------------------- Widget Functions
	virtual void WidgetFunction_SpendMana(int ManaSpent, FStackEntry StackEntry);

// ------------------------- Technical Functions
	virtual AActor* TechnicalFunction_SimpleGetTarget();
};