#pragma once


#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "Variables.h"
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

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	EPlayerControlModes ControlMode = EPlayerControlModes::LevelExploration;
	
// ---------------------------------------- Functions ---------------------------------------- //


};
