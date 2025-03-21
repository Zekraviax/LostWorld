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
	
	SelectCardToCast();
}


void UAiBrainBaseWolfPackAlpha::SelectCardToCast()
{
	Super::SelectCardToCast();

	if (FindCardInHand("Howl Of Command") != -1 && SelfTurnCounter < 1) {
		GetTargetsForCard(FindCardInHand("Howl of Command"));
		SelfTurnCounter++;
	} else if (FindCardInHand("Test Card One") != -1) {
		GetTargetsForCard(FindCardInHand("Test Card One"));
	} else {
		GetWorld()->GetTimerManager().SetTimer(EndTurnTimerHandle, this, &UAiBrainBase::EndTurn,3.f, false);
	}
}


void UAiBrainBaseWolfPackAlpha::GetTargetsForCard(int IndexInHand)
{
	Super::GetTargetsForCard(IndexInHand);
	
	// If the wolf does not have a target override, then find a random player to be the target.
	if (AttackTargetsOverride.Num() > 0) {
		TArray<AActor*> FoundTargets;
		
		for (auto& Target : AttackTargetsOverride) {
			FoundTargets.Add(Target);
		}

		Cast<ALostWorldGameModeBattle>(GetWorld()->GetAuthGameMode())->TempStackEntry.SelectedTargets.Empty();

		for (AActor* Actor : FoundTargets) {
			Cast<ALostWorldGameModeBattle>(GetWorld()->GetAuthGameMode())->
				TempStackEntry.SelectedTargets.Add(Cast<AActorEntityBase>(Actor));
		}
	}

	GetWorld()->GetTimerManager().SetTimer(CastCardTimerHandle, this, &UAiBrainBase::CastCardWithDelay,2.5f, false);
	GetWorld()->GetTimerManager().SetTimer(EndTurnTimerHandle, this, &UAiBrainBase::EndTurn,3.f, false);
}


void UAiBrainBaseWolfPackAlpha::EndTurn()
{
	Super::EndTurn();
}
