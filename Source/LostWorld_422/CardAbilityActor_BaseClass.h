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
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Constructors")
	TSubclassOf<ACardAbilityActor_BaseClass> CardAbilityActor_DrawCards_Class;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Constructors")
	ACardAbilityActor_BaseClass* CardAbilityActor_Reference;

// ------------------------- Card
	UPROPERTY()
	FCardBase LocalCardReference;

// ------------------------- The Stack
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Stack")
	TArray<FCardBase> StackArray;

// ------------------------- Timers	
	UPROPERTY()
	FTimerHandle StackTimerHandle;

// Functions
// --------------------------------------------------

// ------------------------- Base Class Functions
	UFUNCTION()
	void CastCard(FCardBase Card);

	UFUNCTION()
	void SpawnCardAbilityActor(TSubclassOf<ACardAbilityActor_BaseClass> CardAbilityActor_Class);

// ------------------------- Sub Class Functions
	UFUNCTION()
	void RunCardAbilityFunction();
};
