#include "AiBrainRabidRat.h"


#include "ActorEntityEnemy.h"


void UAiBrainRabidRat::StartTurn()
{
	Super::StartTurn();
	
	SelectCardToCast();
}


void UAiBrainRabidRat::SelectCardToCast()
{
	Super::SelectCardToCast();
	
	AActorEntityEnemy* OwnerAsEnemy = Cast<AActorEntityEnemy>(GetOwner());

	if (TurnCount == 0 && FindCardInHand("Screech") != -1) {
		GetTargetsForCard(FindCardInHand("Screech"));
	} else if (OwnerAsEnemy->EntityData.Hand.Num() > 0) {
		GetTargetsForCard(FMath::RandRange(0, OwnerAsEnemy->EntityData.Hand.Num() - 1));
	} else {
		GetWorld()->GetTimerManager().SetTimer(EndTurnTimerHandle, this, &UAiBrainBase::EndTurn,3.f, false);
	}

	TurnCount++;
}


void UAiBrainRabidRat::GetTargetsForCard(int IndexInHand)
{
	Super::GetTargetsForCard(IndexInHand);

	GetWorld()->GetTimerManager().SetTimer(CastCardTimerHandle, this, &UAiBrainBase::CastCardWithDelay,2.5f, false);
	GetWorld()->GetTimerManager().SetTimer(EndTurnTimerHandle, this, &UAiBrainBase::EndTurn,3.f, false);
}


void UAiBrainRabidRat::EndTurn()
{
	Super::EndTurn();
}
