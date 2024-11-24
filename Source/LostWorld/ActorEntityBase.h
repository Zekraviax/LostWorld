#pragma once


#include "Components/WidgetComponent.h"
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Variables.h"
#include "ActorEntityBase.generated.h"


class UWidgetEntityBillboard;


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

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<UWidgetEntityBillboard> EntityBillboardWidgetClass;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UWidgetComponent* EntityBillboard;


// -------------------------------- Cards & Deck
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	FEntity EntityData;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TArray<FCard> Deck;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TArray<FCard> Hand;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TArray<FCard> Discard;
	

// ---------------------------------------- Functions ---------------------------------------- //
	void ResetEntityBillboardPositionAndRotation() const;

// -------------------------------- Child actor functions
// The Enemy entity and Player entity will implement their own versions of the following interface functions separately.
// This is so that the Player entity can receive data from and send data to the Players' GameInstance, which persists
// between battles.
	//virtual void AddCardToDeck(FCard InCard);
};
