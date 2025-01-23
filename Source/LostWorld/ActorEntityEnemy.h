#pragma once


#include "CoreMinimal.h"
#include "ActorEntityBase.h"
#include "AiBrainBase.h"
#include "InterfaceBattle.h"
#include "ActorEntityEnemy.generated.h"


UCLASS()
// To-Do: Rename this class to something else, because we're using this actor
// for both enemies and player controlled summons (?)
class LOSTWORLD_API AActorEntityEnemy : public AActorEntityBase
{
	GENERATED_BODY()
	
public:
	AActorEntityEnemy();


// ---------------------------------------- Variables ---------------------------------------- //

// -------------------------------- Enemy-exclusive variables
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	FEnemyEntity EnemyData;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UAiBrainBase* AiBrainComponent;

	
// ---------------------------------------- Functions ---------------------------------------- //

// -------------------------------- Enemy-exclusive functions
	void CreateAiBrainComponent();

// -------------------------------- Battle Interface functions
	virtual bool OverrideDeck(TArray<FCard> InDeck) override;
	virtual bool AddCardToDeck(FCard InCard) override;
	virtual TArray<FCard> ShuffleDeck(TArray<FCard> InDeck) override;
	virtual bool DrawCard() override;
	virtual bool DiscardCard(int IndexInHand) override;
	virtual bool PayCostsForCard(int IndexInHand) override;

	virtual bool TakeDamage(float Damage) override;
	virtual bool EntityDefeated() override;

	virtual bool ReceiveHealing(float Healing) override;
	virtual bool GainMana(int InMana) override;
	virtual bool GainBarrier(int InBarrier) override;

	virtual bool AddStatusEffect(FStatusEffect StatusEffect) override;

	virtual bool StartTurn() override;
	virtual bool EndTurn() override;
};