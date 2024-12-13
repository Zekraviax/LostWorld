#pragma once


#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "AiBrainBase.generated.h"


class AActorEntityEnemy;


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class LOSTWORLD_API UAiBrainBase : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UAiBrainBase();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	
// ---------------------------------------- Variables ---------------------------------------- //
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	FTimerHandle CastCardTimerHandle;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	FTimerHandle EndTurnTimerHandle;

// ---------------------------------------- Functions ---------------------------------------- //
	virtual void StartTurn();

	// When the enemy finds the card they want to cast,
	// add an image of it to the players' HUD and get the targets for it.
	// After a short delay, cast the card.

	// Returns -1 if the card with the given name can't be found.
	// Otherwise, returns the index of the card in the hand array.
	virtual int FindCardInHand(FString InCardDisplayName);
	virtual void SelectCardToCast();
	virtual void GetTargetsForCard(int IndexInHand);
	virtual void CastCardWithDelay();
	virtual void EndTurn();
};
