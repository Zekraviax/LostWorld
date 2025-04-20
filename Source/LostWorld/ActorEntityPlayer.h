#pragma once


#include "ActorEntityBase.h"
#include "Camera/CameraComponent.h"
#include "CoreMinimal.h"
#include "GameFramework/SpringArmComponent.h"
#include "ActorEntityPlayer.generated.h"


class ALostWorldPlayerControllerBase;


UCLASS()
class LOSTWORLD_API AActorEntityPlayer : public AActorEntityBase
{
	GENERATED_BODY()
	
public:
	AActorEntityPlayer();
	
// ---------------------------------------- Variables ---------------------------------------- //

// -------------------------------- Actor Components
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	USpringArmComponent* SpringArm;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UCameraComponent* Camera;
	
// ---------------------------------------- Functions ---------------------------------------- //

// -------------------------------- Battle Interface functions
	virtual bool DrawCard() override;
	virtual bool DiscardCard(int IndexInHand) override;
	virtual bool BottomCard(FCard InCard) override;

	virtual bool ExileCardFromZone(FString InZoneName, FCard InCard) override;

	virtual bool TakeDamage(float Damage) override;
	virtual bool EntityDefeated() override;

	virtual bool ReceiveHealing(float Healing) override;

	virtual bool StartTurn() override;
	virtual bool EndTurn() override;

// -------------------------------- Other
	ALostWorldPlayerControllerBase* ReturnThisPlayersController();
};
