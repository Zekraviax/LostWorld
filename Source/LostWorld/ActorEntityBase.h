#pragma once


#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Variables.h"
#include "ActorEntityBase.generated.h"


// The base Entity class that all subtypes of Entities will inherit from, including the player.
UCLASS()
class LOSTWORLD_API AActorEntityBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AActorEntityBase();

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
