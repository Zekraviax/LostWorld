#include "AiBrainTestEnemyOne.h"


#include "ActorEntityEnemy.h"
#include "ActorEntityPlayer.h"
#include "LostWorldGameModeBattle.h"
#include "Engine/World.h" 
#include "TimerManager.h"
#include "Kismet/GameplayStatics.h"


void UAiBrainTestEnemyOne::StartTurn()
{
	Super::StartTurn();
}


void UAiBrainTestEnemyOne::SelectCardToCast()
{
	Super::SelectCardToCast();
}


void UAiBrainTestEnemyOne::GetTargetsForCard(int StackEntryIndex)
{
	Super::GetTargetsForCard(StackEntryIndex);
}


void UAiBrainTestEnemyOne::EndTurn()
{
	Super::EndTurn();
}
