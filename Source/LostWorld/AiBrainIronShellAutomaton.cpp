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

	/*if (TurnCount == 0 && FindCardInHand("Screech") != -1) {
		GetTargetsForCard(FindCardInHand("Screech"));
	} else if (OwnerAsEnemy->EntityData.Hand.Num() > 0) {
		GetTargetsForCard(FMath::RandRange(0, OwnerAsEnemy->EntityData.Hand.Num() - 1));
	} else {
		GetWorld()->GetTimerManager().SetTimer(EndTurnTimerHandle, this, &UAiBrainBase::EndTurn,3.f, false);
	}*/

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