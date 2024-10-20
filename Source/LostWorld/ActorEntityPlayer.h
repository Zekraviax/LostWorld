#pragma once


#include "CoreMinimal.h"
#include "ActorEntityBase.h"
#include "InterfaceBattle.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "ActorEntityPlayer.generated.h"


UCLASS()
class LOSTWORLD_API AActorEntityPlayer : public AActorEntityBase, public IInterfaceBattle
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

// -------------------------------- Player-exclusive functions
	//void PlayerGetDeckFromGameInstance(TArray<FCard> InDeck);

// -------------------------------- Battle Interface functions
	virtual bool OverrideDeck(TArray<FCard> InDeck) override;
	virtual bool AddCardToDeck(FCard InCard) override;
	virtual TArray<FCard> ShuffleDeck(TArray<FCard> InDeck) override;
	
};