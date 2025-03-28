#include "InterfaceBattle.h"


// Add default functionality here for any IInterfaceBattle functions that are not pure virtual.
bool IInterfaceBattle::AddCardToDeck(FCard InCard)
{
	return true;
}


bool IInterfaceBattle::AddCardToDrawPile(FCard Card)
{
	return true;
}


TArray<FCard> IInterfaceBattle::ShuffleDrawPile(TArray<FCard> InDeck)
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


bool IInterfaceBattle::DiscardCard(int IndexInHand)
{
	return true;
}


bool IInterfaceBattle::PayCostsForCard(int IndexInHand)
{
	return true;
}


bool IInterfaceBattle::ShuffleDiscardPileIntoDrawPile()
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


bool IInterfaceBattle::ReceiveHealing(float Healing)
{
	return true;
}


bool IInterfaceBattle::GainMana(int InMana)
{
	return true;
}


bool IInterfaceBattle::GainBarrier(int InBarrier)
{
	return true;
}


bool IInterfaceBattle::AddStatusEffect(FStatusEffect StatusEffect)
{
	return true;
}


bool IInterfaceBattle::HasStatusEffect(EStatusEffectFunctions Function)
{
	return true;
}


bool IInterfaceBattle::GetStatusEffectStacks(EStatusEffectFunctions Function, int& OutStacks)
{
	return true;
}


bool IInterfaceBattle::ReturnOffensiveElementalAffinity(ECardElements Element, int& OutAffinity)
{
	return true;
}


bool IInterfaceBattle::ReturnDefensiveElementalAffinity(ECardElements Element, int& OutAffinity)
{
	return true;
}


bool IInterfaceBattle::StartTurn()
{
	return true;
}


bool IInterfaceBattle::EndTurn()
{
	return true;
}