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
	const AActorEntityEnemy* OwnerAsEnemy = Cast<AActorEntityEnemy>(GetOwner());
	ALostWorldGameModeBase::DualLog(OwnerAsEnemy->EntityData.DisplayName +
		" is taking their turn.", 2);

	GetWorld()->GetTimerManager().SetTimer(CastCardTimerHandle, this,
		&UAiBrainBase::SelectCardToCast,1.5f, false);
}


void UAiBrainBase::GetAllCastableCards()
{
	AActorEntityEnemy* OwnerAsEnemy = Cast<AActorEntityEnemy>(GetOwner());
	CastableCardIndicesInHand.Empty();
	
	for (int Index = 0; Index < OwnerAsEnemy->EntityData.Hand.Num(); Index++) {
		// Check for enough MP.
		if (OwnerAsEnemy->EntityData.TotalStats.CurrentManaPoints >= OwnerAsEnemy->EntityData.Hand[Index].TotalCost) {
			CastableCardIndicesInHand.Add(Index);
		}
	}
}


void UAiBrainBase::SelectCardToCast()
{
	// Default implementation. Get a random card, then create a stack entry.
	SelectedCardInHandIndex = FMath::RandRange(0, CastableCardIndicesInHand.Num() - 1);
	
	Cast<ALostWorldGameModeBattle>(GetWorld()->GetAuthGameMode())->PayCostsAndDiscardCardEntity =
		Cast<AActorEntityEnemy>(GetOwner());

	Cast<ALostWorldGameModeBattle>(GetWorld()->GetAuthGameMode())->PayCostsAndDiscardCardHandIndex =
		SelectedCardInHandIndex;
	
	Cast<ALostWorldGameModeBattle>(GetWorld()->GetAuthGameMode())->CreateStackEntry(SelectedCardInHandIndex);
}


void UAiBrainBase::GetTargetsForCard(const int StackEntryIndex)
{
	// Default implementation: Get a random enemy.
	TArray<AActor*> FoundTargetsAsActors;
	TArray<AActorEntityBase*> FoundTargetsAsEntities;
	
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AActorEntityPlayer::StaticClass(), FoundTargetsAsActors);
	FoundTargetsAsEntities.Add(Cast<AActorEntityBase>(FoundTargetsAsActors[FMath::RandRange(0,
		FoundTargetsAsActors.Num() - 1)]));

	Cast<ALostWorldGameModeBattle>(GetWorld()->GetAuthGameMode())->FinishedGettingTargetsForCard(StackEntryIndex,
		FoundTargetsAsEntities);
}


void UAiBrainBase::EndTurn()
{
	SelfTurnCounter++;
	
	AActorEntityEnemy* OwnerAsEnemy = Cast<AActorEntityEnemy>(GetOwner());
	ALostWorldGameModeBase::DualLog(
		OwnerAsEnemy->EntityData.DisplayName + " is ending their turn.", 2);
	
	Cast<ALostWorldGameModeBattle>(GetWorld()->GetAuthGameMode())->EndOfTurn();
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
