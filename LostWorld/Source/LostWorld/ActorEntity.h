#pragma once


#include "CoreMinimal.h"

#include "GameFramework/Actor.h"
#include "Variables.h"

#include "ActorEntity.generated.h"


UCLASS()
class LOSTWORLD_API AActorEntity : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AActorEntity();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

// ---------------------------------------- Variables ---------------------------------------- //

// -------------------------------- Cards & Deck
	UPROPERTY()
	TArray<FCard> Deck;
};
