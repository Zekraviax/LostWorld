#pragma once


#include "CoreMinimal.h"
#include "ActorEntityBase.h"
#include "AiBrainBase.h"
#include "ActorEntityEnemy.generated.h"


UCLASS()
// To-Do: Rename this class to something else, because we're using this actor for both enemies and player controlled summons (?)
class LOSTWORLD_API AActorEntityEnemy : public AActorEntityBase
{
	GENERATED_BODY()
	
public:
	AActorEntityEnemy();


// ---------------------------------------- Variables ---------------------------------------- //
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	FTimerHandle StartTurnTimerHandle;

// -------------------------------- Enemy-exclusive variables
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	FEnemyEntity EnemyData;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UAiBrainBase* AiBrainComponent;

	
// ---------------------------------------- Functions ---------------------------------------- //

// -------------------------------- Enemy-exclusive functions
	void CreateAiBrainComponent();

// -------------------------------- Battle Interface functions
	virtual bool EntityTakeDamage(float Damage) override;

	virtual bool ReceiveHealing(float Healing) override;
	virtual bool GainBarrier(int InBarrier) override;
	
	virtual bool StartTurn() override;
	virtual bool EndTurn() override;
};