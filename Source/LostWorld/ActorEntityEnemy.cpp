#include "ActorEntityEnemy.h"


#include "LostWorldGameModeBattle.h"
#include "WidgetEntityBillboard.h"


AActorEntityEnemy::AActorEntityEnemy()
{
	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>("StaticMesh");
	EntityBillboard = CreateDefaultSubobject<UWidgetComponent>("EntityBillboard");

	EntityBillboard->SetupAttachment(StaticMesh);
	EntityBillboard->SetPivot(FVector2D(0.1f, 0.f));
	EntityBillboard->SetWorldLocation(GetActorLocation());
}


bool AActorEntityEnemy::OverrideDeck(TArray<FCard> InDeck)
{
	Deck = InDeck;
	return true;
}


bool AActorEntityEnemy::AddCardToDeck(FCard InCard)
{
	Deck.Add(InCard);
	return true;
}


TArray<FCard> AActorEntityEnemy::ShuffleDeck(TArray<FCard> InDeck)
{
	// The Shuffle Deck function doesn't need to have multiple different definitions,
	// so we can just use the default one.
	return IInterfaceBattle::ShuffleDeck(Deck);
}

bool AActorEntityEnemy::DrawCard()
{
	// Shift the top card of the deck into the hand
	Hand.Add(Deck[0]);
	Deck.RemoveAt(0);
	return true;
}

bool AActorEntityEnemy::DiscardCard(int IndexInHand)
{
	Discard.Add(Hand[IndexInHand - 1]);
	Hand.RemoveAt(IndexInHand - 1);
	
	return true;
}

bool AActorEntityEnemy::PayCostsForCard(int IndexInHand)
{
	EntityData.Stats.CurrentManaPoints -= Hand[IndexInHand - 1].TotalCost;
	Cast<UWidgetEntityBillboard>(EntityBillboard->GetUserWidgetObject())->UpdateBillboard(EntityData);
	
	return true;
}


bool AActorEntityEnemy::TakeDamage(float Damage)
{
	EntityData.Stats.CurrentHealthPoints -= Damage;

	if (EntityData.Stats.CurrentHealthPoints <= 0) {
		EntityDefeated();
	} else {
		Cast<UWidgetEntityBillboard>(EntityBillboard->GetUserWidgetObject())->UpdateBillboard(EntityData);
	}
	
	return true;
}


bool AActorEntityEnemy::EntityDefeated()
{
	Destroy();
	
	Cast<ALostWorldGameModeBattle>(GetWorld()->GetAuthGameMode())->EndOfBattleCheck();

	return true;
}
