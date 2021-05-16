#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "StatusFunctions_BaseClass.generated.h"


UCLASS()
class LOSTWORLD_422_API AStatusFunctions_BaseClass : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AStatusFunctions_BaseClass();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
