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

	/*if (FindCardInHand("Test Card Three") != -1) {
		GetTargetsForCard();
	}

	if (FindCardInHand("Test Card One") != -1) {
		GetTargetsForCard();
	} */

	EndTurn();
}

void UAiBrainTestEnemyTwo::GetTargetsForCard(int StackEntryIndex)
{
	Super::GetTargetsForCard(StackEntryIndex);
	/*AActorEntityEnemy* OwnerAsEnemy = Cast<AActorEntityEnemy>(GetOwner());

	// Find a random player to be the target.
	TArray<AActor*> FoundPlayers;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AActorEntityPlayer::StaticClass(), FoundPlayers);

	TArray<ECardFunctions> CardFunctions;
	OwnerAsEnemy->EntityData.Hand[IndexInHand].FunctionsAndTargets.GetKeys(CardFunctions);

	Cast<ALostWorldGameModeBattle>(GetWorld()->GetAuthGameMode())->TempStackEntry.Function = CardFunctions[0];
	Cast<ALostWorldGameModeBattle>(GetWorld()->GetAuthGameMode())->TempStackEntry.TargetingMode =
		*OwnerAsEnemy->EntityData.Hand[IndexInHand].FunctionsAndTargets.Find(CardFunctions[0]);
	Cast<ALostWorldGameModeBattle>(GetWorld()->GetAuthGameMode())->TempStackEntry.Controller = OwnerAsEnemy;
	Cast<ALostWorldGameModeBattle>(GetWorld()->GetAuthGameMode())->TempStackEntry.SelectedTargets.Empty();
	Cast<ALostWorldGameModeBattle>(GetWorld()->GetAuthGameMode())->TempStackEntry.SelectedTargets.
		Add(Cast<AActorEntityBase>(FoundPlayers[0]));
	Cast<ALostWorldGameModeBattle>(GetWorld()->GetAuthGameMode())->TempStackEntry.IndexInHandArray = IndexInHand;

	GetWorld()->GetTimerManager().SetTimer(CastCardTimerHandle, this, &UAiBrainBase::CastCardWithDelay,2.5f, false);
	GetWorld()->GetTimerManager().SetTimer(EndTurnTimerHandle, this, &UAiBrainBase::EndTurn,3.f, false);*/
}


void UAiBrainTestEnemyTwo::EndTurn()
{
	Super::EndTurn();
}
