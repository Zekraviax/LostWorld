#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BaseClass_LevelController.generated.h"


UCLASS()
class LOSTWORLD_422_API ABaseClass_LevelController : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABaseClass_LevelController();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
