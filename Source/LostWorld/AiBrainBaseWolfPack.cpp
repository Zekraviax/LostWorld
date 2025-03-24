#include "AiBrainBaseWolfPack.h"


#include "AiBrainTestEnemyOne.h"
#include "ActorEntityEnemy.h"
#include "ActorEntityPlayer.h"
#include "LostWorldGameModeBattle.h"
#include "Engine/World.h" 
#include "TimerManager.h"
#include "Kismet/GameplayStatics.h"


void UAiBrainBaseWolfPack::StartTurn()
{
	Super::StartTurn();
}


void UAiBrainBaseWolfPack::SelectCardToCast()
{
	Super::SelectCardToCast();
}


void UAiBrainBaseWolfPack::GetTargetsForCard(int StackEntryIndex)
{
	// If the wolf does not have a target override, then find a random player to be the target.
	if (AttackTargetsOverride.Num() > 0) {
		Cast<ALostWorldGameModeBattle>(GetWorld()->GetAuthGameMode())->FinishedGettingTargetsForCard(StackEntryIndex,
			AttackTargetsOverride);
	} else {
		Super::GetTargetsForCard(StackEntryIndex);
	}
}


void UAiBrainBaseWolfPack::EndTurn()
{
	Super::EndTurn();
}
