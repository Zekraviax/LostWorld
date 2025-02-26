#include "AiBrainBase.h"


#include "ActorEntityEnemy.h"
#include "ActorEntityPlayer.h"
#include "LostWorldGameModeBattle.h"
#include "Kismet/GameplayStatics.h"


// Sets default values for this component's properties
UAiBrainBase::UAiBrainBase()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;
}


// Called when the game starts
void UAiBrainBase::BeginPlay()
{
	Super::BeginPlay();
}


// Called every frame
void UAiBrainBase::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}


void UAiBrainBase::StartTurn()
{
}


int UAiBrainBase::FindCardInHand(FString InCardDisplayName)
{
	AActorEntityEnemy* OwnerAsEnemy = Cast<AActorEntityEnemy>(GetOwner());

	for (int HandCount = 0; HandCount < OwnerAsEnemy->EntityData.Hand.Num(); HandCount++) {
		if (OwnerAsEnemy->EntityData.Hand[HandCount].DisplayName.Equals(InCardDisplayName, ESearchCase::IgnoreCase)) {
			return HandCount;
		}
	}
	
	return -1;
}


void UAiBrainBase::SelectCardToCast()
{
}


// To-Do: Remove this duplicate code from the AiBrain child classes.
void UAiBrainBase::GetTargetsForCard(int IndexInHand)
{
	AActorEntityEnemy* OwnerAsEnemy = Cast<AActorEntityEnemy>(GetOwner());
	TArray<ECardFunctions> CardFunctions;
	TArray<AActor*> FoundTargets;
	OwnerAsEnemy->EntityData.Hand[IndexInHand].FunctionsAndTargets.GetKeys(CardFunctions);
	
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AActorEntityPlayer::StaticClass(), FoundTargets);
	
	Cast<ALostWorldGameModeBattle>(GetWorld()->GetAuthGameMode())->TempStackEntry.Function = CardFunctions[0];
	Cast<ALostWorldGameModeBattle>(GetWorld()->GetAuthGameMode())->TempStackEntry.TargetingMode =
		*OwnerAsEnemy->EntityData.Hand[IndexInHand].FunctionsAndTargets.Find(CardFunctions[0]);
	Cast<ALostWorldGameModeBattle>(GetWorld()->GetAuthGameMode())->TempStackEntry.Controller = OwnerAsEnemy;
	Cast<ALostWorldGameModeBattle>(GetWorld()->GetAuthGameMode())->TempStackEntry.SelectedTargets.Empty();
	Cast<ALostWorldGameModeBattle>(GetWorld()->GetAuthGameMode())->TempStackEntry.SelectedTargets.
		Add(Cast<AActorEntityBase>(FoundTargets[0]));
	Cast<ALostWorldGameModeBattle>(GetWorld()->GetAuthGameMode())->TempStackEntry.IndexInHandArray = IndexInHand;
	Cast<ALostWorldGameModeBattle>(GetWorld()->GetAuthGameMode())->TempStackEntry.Card = OwnerAsEnemy->EntityData.Hand[IndexInHand];
}


void UAiBrainBase::CastCardWithDelay()
{
	Cast<ALostWorldGameModeBattle>(GetWorld()->GetAuthGameMode())->FinishedGettingTargetsForCard();
}


void UAiBrainBase::EndTurn()
{
	Cast<ALostWorldGameModeBattle>(GetWorld()->GetAuthGameMode())->EndOfTurn();
}
