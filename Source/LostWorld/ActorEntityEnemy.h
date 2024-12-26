#pragma once


#include "CoreMinimal.h"
#include "ActorEntityBase.h"
#include "AiBrainBase.h"
#include "InterfaceBattle.h"
#include "ActorEntityEnemy.generated.h"


UCLASS()
class LOSTWORLD_API AActorEntityEnemy : public AActorEntityBase, public IInterfaceBattle
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
	virtual bool GainBarrier(int InBarrier) override;

	virtual bool StartTurn() override;
	virtual bool EndTurn() override;
};