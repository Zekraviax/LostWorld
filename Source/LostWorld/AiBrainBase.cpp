#include "AiBrainBase.h"


#include "ActorEntityEnemy.h"
#include "LostWorldGameModeBattle.h"


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


void UAiBrainBase::BeginTurn()
{
	
}


int UAiBrainBase::FindCardInHand(FString InCardDisplayName)
{
	AActorEntityBase* OwnerAsEnemy = Cast<AActorEntityEnemy>(GetOwner());

	for (int HandCount = 0; HandCount < OwnerAsEnemy->Hand.Num(); HandCount++) {
		if (OwnerAsEnemy->Hand[HandCount].DisplayName.Equals(InCardDisplayName)) {
			return HandCount;
		}
	}
	
	return -1;
}


void UAiBrainBase::SelectCardToCast()
{
}


void UAiBrainBase::CastCardWithDelay()
{
	Cast<ALostWorldGameModeBattle>(GetWorld()->GetAuthGameMode())->FinishedGettingTargetsForCard();
}
