#pragma once


#include "CoreMinimal.h"
#include "ActorEntityBase.h"
#include "InterfaceBattle.h"
#include "ActorEntityEnemy.generated.h"


UCLASS()
class LOSTWORLD_API AActorEntityEnemy : public AActorEntityBase, public IInterfaceBattle
{
	GENERATED_BODY()
	
public:
	AActorEntityEnemy();

// ---------------------------------------- Functions ---------------------------------------- //

// -------------------------------- Enemy-exclusive functions

// -------------------------------- Battle Interface functions
	virtual bool OverrideDeck(TArray<FCard> InDeck) override;
	virtual bool AddCardToDeck(FCard InCard) override;
	virtual TArray<FCard> ShuffleDeck(TArray<FCard> InDeck) override;
	virtual bool DrawCard() override;
	virtual bool DiscardCard(int IndexInHand) override;
	virtual bool PayCostsForCard(int IndexInHand) override;

	virtual bool TakeDamage(float Damage) override;
	virtual bool EntityDefeated() override;
};
