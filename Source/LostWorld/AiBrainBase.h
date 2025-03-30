#pragma once


#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "AiBrainBase.generated.h"


class AActorEntityBase;
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

// -------------------------------- Timers
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	FTimerHandle CastCardTimerHandle;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	FTimerHandle EndTurnTimerHandle;

// -------------------------------- Decision-making
	// If this array has any entities in it, force this entity to attack them.
	// Should be emptied at the end of every turn (?)
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TArray<AActorEntityBase*> AttackTargetsOverride;
	
	// How many turns this entity has taken since the battle begun.
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	int SelfTurnCounter;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TArray<int> CastableCardIndicesInHand;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	int SelectedCardInHandIndex;

// ---------------------------------------- Functions ---------------------------------------- //
	// When the enemy finds the card they want to cast,
	// add an image of it to the players' HUD and get the targets for it.
	// After a short delay, cast the card.

	// Returns -1 if the card with the given name can't be found.
	// Otherwise, returns the index of the card in the hand array.

	// To-Do: Write a function that the AI can use to check for all cards that they can cast:
	// Cards they have the MP to cast.
	// Shouts if they haven't used one this turn.
	// etc,
	virtual void StartTurn();
	virtual void GetAllCastableCards();
	virtual void SelectCardToCast();
	virtual void GetTargetsForCard(int StackEntryIndex);
	virtual void EndTurn();

	// Helper functions
	virtual int FindCardInHand(FString InCardDisplayName);
};
