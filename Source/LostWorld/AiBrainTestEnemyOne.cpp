#include "AiBrainTestEnemyOne.h"


#include "ActorEntityEnemy.h"
#include "LostWorldGameModeBattle.h"
#include "Engine/World.h" 
#include "TimerManager.h"


void UAiBrainTestEnemyOne::StartTurn()
{
	SelectCardToCast();
}


void UAiBrainTestEnemyOne::SelectCardToCast()
{
	Super::SelectCardToCast();

	if (FindCardInHand("Test Card One") != -1) {
		GetTargetsForCard(FindCardInHand("Test Card One"));
	}
}

void UAiBrainTestEnemyOne::GetTargetsForCard(int IndexInHand)
{
	Super::GetTargetsForCard(IndexInHand);

	AActorEntityEnemy* OwnerAsEnemy = Cast<AActorEntityEnemy>(GetOwner());

	Cast<ALostWorldGameModeBattle>(GetWorld()->GetAuthGameMode())->TempStackEntry.Function = ECardFunctions::TestFunctionOne;
	//Cast<ALostWorldGameModeBattle>(GetWorld()->GetAuthGameMode())->TempStackEntry.TargetingMode 
	Cast<ALostWorldGameModeBattle>(GetWorld()->GetAuthGameMode())->TempStackEntry.Controller = OwnerAsEnemy;
	//Cast<ALostWorldGameModeBattle>(GetWorld()->GetAuthGameMode())->TempStackEntry.SelectedTargets
	Cast<ALostWorldGameModeBattle>(GetWorld()->GetAuthGameMode())->TempStackEntry.IndexInHandArray = IndexInHand;

	GetWorld()->GetTimerManager().SetTimer(CastCardTimerHandle, this, &UAiBrainBase::CastCardWithDelay,1.5f, false);
}
