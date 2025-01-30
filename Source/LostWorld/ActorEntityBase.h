#pragma once


#include "Components/WidgetComponent.h"
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "InterfaceBattle.h"
#include "InterfaceEntity.h"
#include "Variables.h"
#include "ActorEntityBase.generated.h"


class UWidgetEntityBillboard;


// The base Entity class that all subtypes of Entities will inherit from, including the player.
UCLASS()
class LOSTWORLD_API AActorEntityBase : public AActor, public IInterfaceBattle, public IInterfaceEntity
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

// -------------------------------- Other
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TArray<FStatusEffect> StatusEffects;
	

// ---------------------------------------- Functions ---------------------------------------- //
	void ResetEntityBillboardPositionAndRotation() const;

// -------------------------------- Battle Interface functions
// The Enemy entity and Player entity will also override these so they can have additional effects.
// This is so that the Player entity can receive data from and send data to the Players' GameInstance, which persists
// between battles.
	virtual bool OverrideDeck(TArray<FCard> InDeck) override;
	virtual bool AddCardToDeck(FCard InCard) override;
	virtual TArray<FCard> ShuffleDeck(TArray<FCard> InDeck) override;
	virtual bool DrawCard() override;
	virtual bool DiscardCard(int IndexInHand) override;
	virtual bool PayCostsForCard(int IndexInHand) override;
	virtual bool ShuffleDiscardPileIntoDeck() override;

	virtual bool TakeDamage(float Damage) override;
	virtual bool EntityDefeated() override;

	virtual bool ReceiveHealing(float Healing) override;
	virtual bool GainMana(int InMana) override;
	virtual bool GainBarrier(int InBarrier) override;

	virtual bool AddStatusEffect(FStatusEffect StatusEffect) override;

	virtual bool StartTurn() override;
	virtual bool EndTurn() override;

// -------------------------------- Entity Interface functions
	virtual bool CalculateTotalStats() override;
};
