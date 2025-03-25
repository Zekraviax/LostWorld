#include "AiBrainRabidRat.h"


#include "ActorEntityEnemy.h"
#include "LostWorldGameModeBattle.h"


void UAiBrainRabidRat::StartTurn()
{
	Super::StartTurn();
}


void UAiBrainRabidRat::SelectCardToCast()
{
	
	// Each card in this enemy's deck is assigned a weight, which is used to randomly decide which card to cast,
	// except for the first turn, where it will always use Screech.
	
	// The higher the weight, the more likely the card is to be selected.
	// Weights:
	// Infected Bite - 3
	// Screech - 2
	// Vomit - 1

	AActorEntityEnemy* OwnerAsEnemy = Cast<AActorEntityEnemy>(GetOwner());
	TArray<FCard> WeightedCardArray;

	if (FindCardInHand("Infected Bite") != -1) {
		WeightedCardArray.Add(OwnerAsEnemy->EntityData.Hand[FindCardInHand("Infected Bite")]);
		WeightedCardArray.Add(OwnerAsEnemy->EntityData.Hand[FindCardInHand("Infected Bite")]);
		WeightedCardArray.Add(OwnerAsEnemy->EntityData.Hand[FindCardInHand("Infected Bite")]);
	}
	
	if (FindCardInHand("Screech") != -1) {
		WeightedCardArray.Add(OwnerAsEnemy->EntityData.Hand[FindCardInHand("Screech")]);
		WeightedCardArray.Add(OwnerAsEnemy->EntityData.Hand[FindCardInHand("Screech")]);
	}

	if (FindCardInHand("Vomit") != -1) {
		WeightedCardArray.Add(OwnerAsEnemy->EntityData.Hand[FindCardInHand("Vomit")]);
	}

	if (SelfTurnCounter == 0 && FindCardInHand("Screech") != -1) {
		SelectedCardInHandIndex = FindCardInHand("Screech");
			
		Cast<ALostWorldGameModeBattle>(GetWorld()->GetAuthGameMode())->PayCostsAndDiscardCardEntity =
			Cast<AActorEntityEnemy>(GetOwner());
		
		Cast<ALostWorldGameModeBattle>(GetWorld()->GetAuthGameMode())->PayCostsAndDiscardCardHandIndex =
			SelectedCardInHandIndex;
	
		Cast<ALostWorldGameModeBattle>(GetWorld()->GetAuthGameMode())->CreateStackEntry(SelectedCardInHandIndex);
	} else if (WeightedCardArray.Num() > 0) {
		SelectedCardInHandIndex = FMath::RandRange(0, WeightedCardArray.Num() - 1);
		FCard RandomCard = WeightedCardArray[SelectedCardInHandIndex];
		
		Cast<ALostWorldGameModeBattle>(GetWorld()->GetAuthGameMode())->PayCostsAndDiscardCardEntity =
			Cast<AActorEntityEnemy>(GetOwner());

		Cast<ALostWorldGameModeBattle>(GetWorld()->GetAuthGameMode())->PayCostsAndDiscardCardHandIndex =
			SelectedCardInHandIndex;
	
		Cast<ALostWorldGameModeBattle>(GetWorld()->GetAuthGameMode())->CreateStackEntry(SelectedCardInHandIndex);
	} else {
		Super::SelectCardToCast();
	}
}


void UAiBrainRabidRat::GetTargetsForCard(int StackEntryIndex)
{
	Super::GetTargetsForCard(StackEntryIndex);
}


void UAiBrainRabidRat::EndTurn()
{
	Super::EndTurn();
}
