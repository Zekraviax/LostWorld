#include "AiBrainIronShellAutomaton.h"

#include "ActorEntityEnemy.h"
#include "LostWorldGameModeBattle.h"


void UAiBrainIronShellAutomaton::StartTurn()
{
	Super::StartTurn();
	
	SelectCardToCast();
}


//To-Do: Finish this big boy.
void UAiBrainIronShellAutomaton::SelectCardToCast()
{
	Super::SelectCardToCast();
	
	AActorEntityEnemy* OwnerAsEnemy = Cast<AActorEntityEnemy>(GetOwner());
	TArray<FCard> WeightedCardArray;
	// Weights:
	// Hammer Blow - 3
	// Armour Breaker - 2
	// Demi - 2
	if (FindCardInHand("Hammer Blow") != -1) {
		WeightedCardArray.Add(OwnerAsEnemy->EntityData.Hand[FindCardInHand("Hammer Blow")]);
		WeightedCardArray.Add(OwnerAsEnemy->EntityData.Hand[FindCardInHand("Hammer Blow")]);
		WeightedCardArray.Add(OwnerAsEnemy->EntityData.Hand[FindCardInHand("Hammer Blow")]);
	}
	
	if (FindCardInHand("Armour Breaker") != -1) {
		WeightedCardArray.Add(OwnerAsEnemy->EntityData.Hand[FindCardInHand("Armour Breaker")]);
		WeightedCardArray.Add(OwnerAsEnemy->EntityData.Hand[FindCardInHand("Armour Breaker")]);
	}

	if (FindCardInHand("Demi") != -1 && OwnerAsEnemy->EntityData.TotalStats.CurrentManaPoints >= 4) {
		WeightedCardArray.Add(OwnerAsEnemy->EntityData.Hand[FindCardInHand("Demi")]);
		WeightedCardArray.Add(OwnerAsEnemy->EntityData.Hand[FindCardInHand("Demi")]);
	}

	SelectedCardInHandIndex = FMath::RandRange(0, WeightedCardArray.Num() - 1);
	FCard RandomCard = WeightedCardArray[SelectedCardInHandIndex];

	// If the automation chooses to use Demi, it needs to have enough mana to cast it at least a few times.
	if (RandomCard.DisplayName.Equals("Demi")) {
		// For every 4 MP it has, it will spend 1 MP on a Demi spell.
		int DemiCastCount = OwnerAsEnemy->EntityData.TotalStats.CurrentManaPoints % 4;

		// Enemies can override the total cost of X spells while they're on the stack,
		// because they can't use a UI to set how much MP they use like Players can.
		Cast<ALostWorldGameModeBattle>(GetWorld()->GetAuthGameMode())->PayCostsAndDiscardCardEntity =
			Cast<AActorEntityEnemy>(GetOwner());

		Cast<ALostWorldGameModeBattle>(GetWorld()->GetAuthGameMode())->PayCostsAndDiscardCardHandIndex =
			SelectedCardInHandIndex;

		OwnerAsEnemy->EntityData.Hand[SelectedCardInHandIndex].TotalCost = DemiCastCount;
		Cast<ALostWorldGameModeBattle>(GetWorld()->GetAuthGameMode())->CreateStackEntry(SelectedCardInHandIndex);
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