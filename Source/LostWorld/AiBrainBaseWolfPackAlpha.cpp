#include "AiBrainBaseWolfPackAlpha.h"


#include "AiBrainTestEnemyOne.h"
#include "ActorEntityEnemy.h"
#include "ActorEntityPlayer.h"
#include "LostWorldGameModeBattle.h"
#include "Engine/World.h" 
#include "TimerManager.h"
#include "Kismet/GameplayStatics.h"


void UAiBrainBaseWolfPackAlpha::StartTurn()
{
	Super::StartTurn();
}


void UAiBrainBaseWolfPackAlpha::SelectCardToCast()
{
	if (SelfTurnCounter == 0 && FindCardInHand("Howl") != -1) {
		Cast<ALostWorldGameModeBattle>(GetWorld()->GetAuthGameMode())->PayCostsAndDiscardCardEntity =
			Cast<AActorEntityEnemy>(GetOwner());

		Cast<ALostWorldGameModeBattle>(GetWorld()->GetAuthGameMode())->PayCostsAndDiscardCardHandIndex =
			FindCardInHand("Howl");
	
		Cast<ALostWorldGameModeBattle>(GetWorld()->GetAuthGameMode())->CreateStackEntry(SelectedCardInHandIndex);
	} else {
		Super::SelectCardToCast();
	}
}


void UAiBrainBaseWolfPackAlpha::GetTargetsForCard(int StackEntryIndex)
{
	// If the wolf does not have a target override, then find a random player to be the target.
	if (AttackTargetsOverride.Num() > 0) {
		Cast<ALostWorldGameModeBattle>(GetWorld()->GetAuthGameMode())->FinishedGettingTargetsForCard(StackEntryIndex,
			AttackTargetsOverride);
	} else {
		Super::GetTargetsForCard(StackEntryIndex);
	}
}


void UAiBrainBaseWolfPackAlpha::EndTurn()
{
	Super::EndTurn();
}
