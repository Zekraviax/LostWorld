#include "AiBrainTestEnemyOne.h"


#include "Engine/World.h" 
#include "TimerManager.h"


void UAiBrainTestEnemyOne::BeginTurn()
{
	SelectCardToCast();
}


void UAiBrainTestEnemyOne::SelectCardToCast()
{
	Super::SelectCardToCast();

	if (FindCardInHand("Test Card One") != -1) {
		GetWorld()->GetTimerManager().SetTimer(CastCardTimerHandle, this, &UAiBrainBase::CastCardWithDelay,1.5f, false);
	}
}
