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
	AActorEntityEnemy* OwnerAsEnemy = Cast<AActorEntityEnemy>(GetOwner());
	ALostWorldGameModeBase::DualLog("Enemy " + OwnerAsEnemy->EntityData.DisplayName +
		" is taking their turn.", 2);
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
	Cast<ALostWorldGameModeBattle>(GetWorld()->GetAuthGameMode())->TempStackEntry.Card =
		OwnerAsEnemy->EntityData.Hand[IndexInHand];
}


void UAiBrainBase::CastCardWithDelay()
{
	// To-Do: Make this a variable in the .h file and write a function that can return this variable.
	AActorEntityEnemy* OwnerAsEnemy = Cast<AActorEntityEnemy>(GetOwner());
	FCard CardCopy = Cast<ALostWorldGameModeBattle>(GetWorld()->GetAuthGameMode())->TempStackEntry.Card;
	
	ALostWorldGameModeBase::DualLog(OwnerAsEnemy->EntityData.DisplayName + " casts "
		+ CardCopy.DisplayName + "!", 2);
	
	Cast<ALostWorldGameModeBattle>(GetWorld()->GetAuthGameMode())->FinishedGettingTargetsForCard();
}


void UAiBrainBase::EndTurn()
{
	AActorEntityEnemy* OwnerAsEnemy = Cast<AActorEntityEnemy>(GetOwner());
	ALostWorldGameModeBase::DualLog("Enemy " +
		OwnerAsEnemy->EntityData.DisplayName + " is ending their turn.", 2);
	
	Cast<ALostWorldGameModeBattle>(GetWorld()->GetAuthGameMode())->EndOfTurn();
}
