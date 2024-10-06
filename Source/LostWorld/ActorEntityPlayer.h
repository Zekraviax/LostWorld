#pragma once


#include "CoreMinimal.h"
#include "ActorEntityBase.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "ActorEntityPlayer.generated.h"


UCLASS()
class LOSTWORLD_API AActorEntityPlayer : public AActorEntityBase
{
	GENERATED_BODY()
	
public:
	AActorEntityPlayer();
	
// ---------------------------------------- Variables ---------------------------------------- //

// -------------------------------- Actor Components
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UStaticMeshComponent* StaticMesh;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	USpringArmComponent* SpringArm;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UCameraComponent* Camera;

// ---------------------------------------- Functions ---------------------------------------- //

// -------------------------------- Boiler-plate Code
	
	
};