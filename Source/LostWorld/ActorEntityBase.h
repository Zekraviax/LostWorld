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

// To-Do: Consider overhauling all of the AActorEntities classes so that only one class is needed.
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
	
// -------------------------------- Data
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	FEntity EntityData;

// -------------------------------- Other
	FTimerDelegate EndTurnTimerDelegate;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	FTimerHandle EndTurnTimerHandle;
	

// ---------------------------------------- Functions ---------------------------------------- //
	void ResetEntityBillboardPositionAndRotation() const;

// -------------------------------- Battle Interface functions
// The Enemy entity and Player entity will also override these so they can have additional effects.
// This is so that the Player entity can receive data from and send data to the Players' GameInstance, which persists
// between battles.
	virtual bool AddCardToDeck(FCard InCard) override;
	virtual bool AddCardToDrawPile(FCard InCard) override;
	virtual TArray<FCard> ShuffleDrawPile(TArray<FCard> InDeck) override;
	virtual bool DrawCard() override;
	virtual bool DiscardCard(int IndexInHand) override;
	virtual bool PayCostsForCard(int IndexInHand) override;
	virtual bool ShuffleDiscardPileIntoDrawPile() override;
	virtual bool BottomCard(FCard InCard) override;
	virtual bool DrawCreatedCard(FCard InCard) override;
	
	virtual bool ExileCardFromZone(FString InZoneName, FCard InCard) override;
	
	virtual bool TakeDamage(float Damage) override;
	virtual bool EntityDefeated() override;

	virtual bool ReceiveHealing(float Healing) override;
	virtual bool GainMana(int InMana) override;
	virtual bool GainBarrier(int InBarrier) override;

	virtual bool AddStatusEffect(FStatusEffect InStatusEffect) override;
	virtual bool HasStatusEffect(EStatusEffectFunctions Function) override;
	virtual bool GetStatusEffectStacks(EStatusEffectFunctions Function, int& OutStacks) override;

	virtual bool ReturnOffensiveElementalAffinity(ECardElements Element, int& OutAffinity) override;
	virtual bool ReturnDefensiveElementalAffinity(ECardElements Element, int& OutAffinity) override;

	virtual bool StartTurn() override;
	virtual bool EndTurn() override;

// -------------------------------- Entity Interface functions
	virtual bool OverrideHp(int InHp) override;
	
	virtual bool CalculateTotalStats() override;

	virtual bool EquipItem(int IndexInInventoryArray) override;
	virtual bool UnequipItem(int IndexInInventoryArray) override;
};
