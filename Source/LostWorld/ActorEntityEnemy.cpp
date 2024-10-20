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
