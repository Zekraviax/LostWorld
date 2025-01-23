#include "ActorEntityBase.h"

#include "FunctionLibraryStatusEffects.h"
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


// -------------------------------- Battle Interface functions
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
	if (Deck.Num() < 1) {
		// If there's no cards in the deck, check if there are any cards in the discard pile.
		// If there are, shuffle the discard pile into the deck.
		if (Discard.Num() > 0) {
			ShuffleDiscardPileIntoDeck();
		} else {
			ALostWorldGameModeBattle::DualLog(EntityData.DisplayName + " can't draw any cards!", 2);
		}
	}
	
	// Shift the top card of the deck into the hand
	Hand.Add(Deck[0]);
	Deck.RemoveAt(0);

	// Calculate card variables such as total cost here.
	Hand.Last().TotalCost = Hand.Last().BaseCost;
	Hand.Last().TotalDamage = Hand.Last().BaseDamage;
	Hand.Last().TotalHealing = Hand.Last().BaseHealing;
	
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


bool AActorEntityBase::ShuffleDiscardPileIntoDeck()
{
	if (Discard.Num() > 0) {
		for (int DiscardCount = 0; DiscardCount < Discard.Num(); DiscardCount++) {
			Deck.Add(Discard[DiscardCount]);
		}
	}

	Discard.Empty();
	ShuffleDeck(Deck);
	
	return IInterfaceBattle::ShuffleDiscardPileIntoDeck();
}


bool AActorEntityBase::TakeDamage(float Damage)
{
	// First, any barriers up will absorb damage.
	while (Damage > 0 && EntityData.Stats.CurrentBarrierPoints > 0) {
		Damage--;
		EntityData.Stats.CurrentBarrierPoints--;
	}

	// Then, damage will be go to the entity's raw health.
	if (Damage > 0) {
		EntityData.Stats.CurrentHealthPoints -= Damage;
	
		if (EntityData.Stats.CurrentHealthPoints <= 0) {
			EntityDefeated();
		}
	}

	if (EntityBillboard->GetUserWidgetObject()) {
		Cast<UWidgetEntityBillboard>(EntityBillboard->GetUserWidgetObject())->UpdateBillboard(EntityData);
	}
	
	
	return IInterfaceBattle::TakeDamage(Damage);
}


bool AActorEntityBase::EntityDefeated()
{
	Destroy();

	// To-Do: Remove the entity from the turn order, if the battle isn't over.
	Cast<ALostWorldGameModeBattle>(GetWorld()->GetAuthGameMode())->EndOfBattleCheck();

	return IInterfaceBattle::EntityDefeated();
}


bool AActorEntityBase::ReceiveHealing(float Healing)
{
	EntityData.Stats.CurrentHealthPoints += Healing;
	
	if (EntityData.Stats.CurrentHealthPoints > EntityData.Stats.MaximumHealthPoints) {
		EntityData.Stats.CurrentHealthPoints = EntityData.Stats.MaximumHealthPoints;
	}
	
	Cast<UWidgetEntityBillboard>(EntityBillboard->GetUserWidgetObject())->UpdateBillboard(EntityData);
	
	return IInterfaceBattle::ReceiveHealing(Healing);
}


bool AActorEntityBase::GainMana(int InMana)
{
	EntityData.Stats.CurrentManaPoints += InMana;
	
	return IInterfaceBattle::GainMana(InMana);
}


bool AActorEntityBase::GainBarrier(int InBarrier)
{
	EntityData.Stats.CurrentBarrierPoints += InBarrier;
	Cast<UWidgetEntityBillboard>(EntityBillboard->GetUserWidgetObject())->UpdateBillboard(EntityData);
	
	return IInterfaceBattle::GainBarrier(InBarrier);
}


bool AActorEntityBase::AddStatusEffect(FStatusEffect StatusEffect)
{
	if (EntityData.Stats.CurrentBarrierPoints > 0 && StatusEffect.BlockedByBarrier) {
		ALostWorldGameModeBase::DualLog("A barrier blocked the status effect from being applied!", 2);
	} else {
		// To-Do: Make status effects add stacks to status effects that the entity already has.
		StatusEffects.Add(StatusEffect);
	}
	
	
	return IInterfaceBattle::AddStatusEffect(StatusEffect);
}


bool AActorEntityBase::StartTurn()
{
	// Check for status effects that trigger at the start of the owners' turn.
	for (FStatusEffect StatusEffect : StatusEffects) {
		if (StatusEffect.TimingTriggers.Contains(ETimingTriggers::StartOfAffectedEntitysTurn)) {
			AFunctionLibraryStatusEffects::ExecuteFunction(StatusEffect.StatusEffect, this);
		}
	}

	// To-Do: For every entity, check for status effects that trigger at the start of every entity's turns.

	// Start of turn regenerations
	if (EntityData.Stats.ManaRegeneration > 0) {
		GainMana(EntityData.Stats.ManaRegeneration);
	}
	
	return IInterfaceBattle::StartTurn();
}


bool AActorEntityBase::EndTurn()
{
	return IInterfaceBattle::EndTurn();
}