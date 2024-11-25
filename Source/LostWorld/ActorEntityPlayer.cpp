#include "ActorEntityPlayer.h"


#include "Kismet/GameplayStatics.h"
#include "LostWorldGameModeBase.h"
#include "LostWorldPlayerControllerBattle.h"
#include "WidgetCard.h"
#include "WidgetEntityBillboard.h"
#include "WidgetHudBattle.h"


// Sets default values
AActorEntityPlayer::AActorEntityPlayer()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Initialize actors components
	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>("StaticMesh");
	SpringArm = CreateDefaultSubobject<USpringArmComponent>("SpringArm");
	Camera = CreateDefaultSubobject<UCameraComponent>("Camera");
	EntityBillboard = CreateDefaultSubobject<UWidgetComponent>("EntityBillboard");

	SetRootComponent(StaticMesh);
	SpringArm->SetupAttachment(RootComponent);
	Camera->SetupAttachment(SpringArm);
	EntityBillboard->SetupAttachment(StaticMesh);
	EntityBillboard->SetPivot(FVector2D(0.1f, 0.f));
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


bool AActorEntityPlayer::DrawCard()
{
	// Shift the top card of the deck into the hand
	Hand.Add(Deck[0]);

	// Create a card widget for the card and add it to the players' HUD.
	UWidgetCard* LocalCardReference = Cast<ALostWorldPlayerControllerBattle>(
		GetWorld()->GetFirstPlayerController())->BattleHudWidget->CreateCardWidgetInHand(Hand.Last());
	
	LocalCardReference->IndexInHandArray = Hand.Num();
	
	Deck.RemoveAt(0);
	return true;
}


bool AActorEntityPlayer::DiscardCard(int IndexInHand)
{
	Discard.Add(Hand[IndexInHand - 1]);
	Hand.RemoveAt(IndexInHand - 1);

	Cast<ALostWorldPlayerControllerBattle>(UGameplayStatics::GetPlayerController(GetWorld(), 0))->
		BattleHudWidget->PlayerFinishCastingCard(IndexInHand);
	
	return true;
}


bool AActorEntityPlayer::PayCostsForCard(int IndexInHand)
{
	EntityData.Stats.CurrentManaPoints -= Hand[IndexInHand - 1].TotalCost;
	Cast<UWidgetEntityBillboard>(EntityBillboard->GetUserWidgetObject())->UpdateBillboard(EntityData);
	
	return true;
}


bool AActorEntityPlayer::TakeDamage(float Damage)
{
	EntityData.Stats.CurrentHealthPoints -= Damage;

	if (EntityData.Stats.CurrentHealthPoints <= 0) {
		EntityDefeated();
	} else {
		Cast<UWidgetEntityBillboard>(EntityBillboard->GetUserWidgetObject())->UpdateBillboard(EntityData);
	}
	
	return true;
}


bool AActorEntityPlayer::EntityDefeated()
{
	ALostWorldGameModeBase::DualLog("Game Over");
	
	return true;
}

