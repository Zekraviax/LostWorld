#include "InterfaceBattle.h"


// Add default functionality here for any IInterfaceBattle functions that are not pure virtual.
bool IInterfaceBattle::OverrideDeck(TArray<FCard> InDeck)
{
	return true;
}


bool IInterfaceBattle::AddCardToDeck(FCard Card)
{
	return true;
}


TArray<FCard> IInterfaceBattle::ShuffleDeck(TArray<FCard> InDeck)
{
	TArray<FCard> ShuffledDeck;

	// For each card in the InDeck array, pick one at random and add it to the ShuffledDeck.
	for (int DeckCount = InDeck.Num() - 1; DeckCount >= 0; DeckCount--) {
		int RandomIndex = FMath::RandRange(0, InDeck.Num() - 1);

		ShuffledDeck.Add(InDeck[RandomIndex]);
		InDeck.RemoveAt(RandomIndex);
	}
	
	return ShuffledDeck;
}


bool IInterfaceBattle::DrawCard()
{
	return true;
}


bool IInterfaceBattle::TakeDamage(float Damage)
{
	return true;
}


bool IInterfaceBattle::EntityDefeated()
{
	return true;
}
