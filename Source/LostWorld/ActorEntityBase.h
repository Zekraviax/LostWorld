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

// -------------------------------- Actor Components
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UStaticMeshComponent* StaticMesh;

// -------------------------------- Cards & Deck
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TArray<FCard> Deck;


// ---------------------------------------- Functions ---------------------------------------- //

// -------------------------------- Child actor functions
// The Enemy entity and Player entity will implement their own versions of the following interface functions separately.
// This is so that the Player entity can receive data from and send data to the Players' GameInstance, which persists
// between battles.
	//virtual void AddCardToDeck(FCard InCard);
};
