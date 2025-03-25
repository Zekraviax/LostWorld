#include "AiBrainIronShellAutomaton.h"

#include "ActorEntityEnemy.h"


void UAiBrainIronShellAutomaton::StartTurn()
{
	Super::StartTurn();
	
	SelectCardToCast();
}


void UAiBrainIronShellAutomaton::SelectCardToCast()
{
	Super::SelectCardToCast();
	
	AActorEntityEnemy* OwnerAsEnemy = Cast<AActorEntityEnemy>(GetOwner());
	
	// Weights:
	// Armour Breaker - 2
	// Hammer Blow - 3
	// Demi - 2

	// If the automation chooses to use Demi, it needs to have enough mana to cast it at least a few times.
	if (OwnerAsEnemy->EntityData.TotalStats.CurrentManaPoints >= 4) {
		// For every 4 MP it has, it will spend 1 MP on a Demi spell.
		int DemiCastCount = OwnerAsEnemy->EntityData.TotalStats.CurrentManaPoints % 4;

		// Enemies can override the total cost of X spells, because they can't use a UI to set how much MP
		// they use like Players can.
	}
}


void UAiBrainIronShellAutomaton::GetTargetsForCard(int StackEntryIndex)
{
	Super::GetTargetsForCard(StackEntryIndex);
}


void UAiBrainIronShellAutomaton::EndTurn()
{
	Super::EndTurn();
}