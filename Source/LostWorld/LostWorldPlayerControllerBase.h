#pragma once


#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "LostWorldPlayerControllerBase.generated.h"


// Forward Declarations
class AActorEntityPlayer;


UCLASS()
class LOSTWORLD_API ALostWorldPlayerControllerBase : public APlayerController
{
	GENERATED_BODY()

// ---------------------------------------- Variables ---------------------------------------- //
public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	AActorEntityPlayer* ControlledPlayerEntity;
	
// ---------------------------------------- Functions ---------------------------------------- //

// -------------------------------- Player input
protected:
	virtual void SetupInputComponent() override;

public:
// -------------------------------- Basic movement
	void PlayerMoveNorth();
	void PlayerMoveSouth();
	void PlayerMoveEast();
	void PlayerMoveWest();
};
