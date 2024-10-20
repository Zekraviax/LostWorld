#include "ActorEntityPlayer.h"


// Sets default values
AActorEntityPlayer::AActorEntityPlayer()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Initialize actors components
	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>("StaticMesh");
	SpringArm = CreateDefaultSubobject<USpringArmComponent>("SpringArm");
	Camera = CreateDefaultSubobject<UCameraComponent>("Camera");

	SetRootComponent(StaticMesh);
	SpringArm->SetupAttachment(RootComponent);
	Camera->SetupAttachment(SpringArm);
}


bool AActorEntityPlayer::OverrideDeck(TArray<FCard> InDeck)
{
	Deck = InDeck;
	return true;
}

bool AActorEntityPlayer::AddCardToDeck(FCard InCard)
{
	Deck.Add(InCard);
	return true;
}


TArray<FCard> AActorEntityPlayer::ShuffleDeck(TArray<FCard> InDeck)
{
	return IInterfaceBattle::ShuffleDeck(Deck);
}

