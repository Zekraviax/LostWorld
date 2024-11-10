#include "ActorEntityEnemy.h"


AActorEntityEnemy::AActorEntityEnemy()
{
	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>("StaticMesh");
}


bool AActorEntityEnemy::OverrideDeck(TArray<FCard> InDeck)
{
	Deck = InDeck;
	return true;
}


bool AActorEntityEnemy::AddCardToDeck(FCard InCard)
{
	Deck.Add(InCard);
	return true;
}


TArray<FCard> AActorEntityEnemy::ShuffleDeck(TArray<FCard> InDeck)
{
	// The Shuffle Deck function doesn't need to have multiple different definitions,
	// so we can just use the default one.
	return IInterfaceBattle::ShuffleDeck(Deck);
}

bool AActorEntityEnemy::DrawCard()
{
	// Shift the top card of the deck into the hand
	Hand.Add(Deck[0]);
	Deck.RemoveAt(0);
	return true;
}

bool AActorEntityEnemy::TakeDamage(float Damage)
{
	EntityData.Stats.CurrentHealthPoints -= Damage;

	if (EntityData.Stats.CurrentHealthPoints <= 0) {
		EntityDefeated();
	}
	
	return true;
}


bool AActorEntityEnemy::EntityDefeated()
{
	BeginDestroy();

	return true;
}
