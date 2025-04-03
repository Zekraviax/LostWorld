#include "AiBrainTestEnemyTwo.h"


#include "ActorEntityEnemy.h"
#include "ActorEntityPlayer.h"
#include "LostWorldGameModeBattle.h"
#include "Engine/World.h" 
#include "TimerManager.h"
#include "Kismet/GameplayStatics.h"


void UAiBrainTestEnemyTwo::StartTurn()
{
	Super::StartTurn();
	
	SelectCardToCast();
}


void UAiBrainTestEnemyTwo::SelectCardToCast()
{
	Super::SelectCardToCast();

	EndTurn();
}

void UAiBrainTestEnemyTwo::GetTargetsForCard(int StackEntryIndex)
{
	Super::GetTargetsForCard(StackEntryIndex);
}


void UAiBrainTestEnemyTwo::EndTurn()
{
	Super::EndTurn();
}
