#include "ActorEntityBase.h"

#include "LostWorldGameModeBase.h"
#include "LostWorldGameModeBattle.h"
#include "WidgetEntityBillboard.h"


// Sets default values
AActorEntityBase::AActorEntityBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AActorEntityBase::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AActorEntityBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


void AActorEntityBase::ResetEntityBillboardPositionAndRotation() const
{
	if (EntityBillboard) {
		if (EntityBillboard->GetRelativeLocation() != FVector(0.f, 0.f, 150.f)) {
			EntityBillboard->SetRelativeLocation(FVector(0.f, 0.f, 150.f));
		}

		if (EntityBillboard->GetRelativeRotation() != FRotator(10.f, 135.f, 0.f)) {
			EntityBillboard->SetRelativeRotation(FRotator(10.f, 135.f, 0.f));
		}
	}
}


bool AActorEntityBase::OverrideDeck(TArray<FCard> InDeck)
{
	Deck = InDeck;
	
	return IInterfaceBattle::OverrideDeck(InDeck);
}


bool AActorEntityBase::AddCardToDeck(FCard InCard)
{
	Deck.Add(InCard);
	
	return IInterfaceBattle::AddCardToDeck(InCard);
}


TArray<FCard> AActorEntityBase::ShuffleDeck(TArray<FCard> InDeck)
{
	// The Shuffle Deck function doesn't need to have multiple different definitions,
	// so we can just use the default one.
	return IInterfaceBattle::ShuffleDeck(Deck);
}

bool AActorEntityBase::DrawCard()
{
	// Shift the top card of the deck into the hand
	Hand.Add(Deck[0]);
	Deck.RemoveAt(0);
	
	return IInterfaceBattle::DrawCard();
}

bool AActorEntityBase::DiscardCard(int IndexInHand)
{
	Discard.Add(Hand[IndexInHand]);
	Hand.RemoveAt(IndexInHand);
	
	return IInterfaceBattle::DiscardCard(IndexInHand);
}

bool AActorEntityBase::PayCostsForCard(int IndexInHand)
{
	EntityData.Stats.CurrentManaPoints -= Hand[IndexInHand].TotalCost;
	Cast<UWidgetEntityBillboard>(EntityBillboard->GetUserWidgetObject())->UpdateBillboard(EntityData);
	
	return IInterfaceBattle::PayCostsForCard(IndexInHand);
}


bool AActorEntityBase::TakeDamage(float Damage)
{
	// First, any barriers up will absorb damage.
	if (EntityData.Stats.CurrentBarrierPoints > 0) {
		
	}

	// Then, damage will be go to the entity's raw health.
	EntityData.Stats.CurrentHealthPoints -= Damage;

	
	if (EntityData.Stats.CurrentHealthPoints <= 0) {
		EntityDefeated();
	} else {
		Cast<UWidgetEntityBillboard>(EntityBillboard->GetUserWidgetObject())->UpdateBillboard(EntityData);
	}
	
	return IInterfaceBattle::TakeDamage(Damage);
}


bool AActorEntityBase::EntityDefeated()
{
	Destroy();
	
	Cast<ALostWorldGameModeBattle>(GetWorld()->GetAuthGameMode())->EndOfBattleCheck();

	return IInterfaceBattle::EntityDefeated();
}


bool AActorEntityBase::ReceiveHealing(float Healing)
{
	Cast<UWidgetEntityBillboard>(EntityBillboard->GetUserWidgetObject())->UpdateBillboard(EntityData);
	
	return IInterfaceBattle::ReceiveHealing(Healing);
}


bool AActorEntityBase::GainBarrier(int InBarrier)
{
	EntityData.Stats.CurrentBarrierPoints += InBarrier;
	Cast<UWidgetEntityBillboard>(EntityBillboard->GetUserWidgetObject())->UpdateBillboard(EntityData);
	
	return IInterfaceBattle::GainBarrier(InBarrier);
}


bool AActorEntityBase::AddStatusEffect(FStatusEffect StatusEffect)
{
	StatusEffects.Add(StatusEffect);
	
	return IInterfaceBattle::AddStatusEffect(StatusEffect);
}


bool AActorEntityBase::StartTurn()
{
	return IInterfaceBattle::StartTurn();
}


bool AActorEntityBase::EndTurn()
{
	return IInterfaceBattle::EndTurn();
}