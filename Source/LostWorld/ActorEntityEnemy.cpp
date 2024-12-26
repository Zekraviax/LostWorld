#include "ActorEntityEnemy.h"


#include "AiBrainBase.h"
#include "AiBrainTestEnemyOne.h"
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


void AActorEntityEnemy::CreateAiBrainComponent()
{
	ALostWorldGameModeBase::DualLog(EnemyData.EnemyType, 4);
	if (EnemyData.EnemyType.Contains("TestEnemyOne")) {
		AiBrainComponent = NewObject<UAiBrainTestEnemyOne>(this);
	}
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
	Discard.Add(Hand[IndexInHand]);
	Hand.RemoveAt(IndexInHand);
	
	return true;
}

bool AActorEntityEnemy::PayCostsForCard(int IndexInHand)
{
	EntityData.Stats.CurrentManaPoints -= Hand[IndexInHand].TotalCost;
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

	ALostWorldGameModeBase::DualLog("Enemy " + EntityData.DisplayName + " takes " +
	FString::FromInt(Damage) + " damage.", 3);
	
	return true;
}


bool AActorEntityEnemy::EntityDefeated()
{
	Destroy();
	
	Cast<ALostWorldGameModeBattle>(GetWorld()->GetAuthGameMode())->EndOfBattleCheck();

	return true;
}


bool AActorEntityEnemy::ReceiveHealing(float Healing)
{
	ALostWorldGameModeBase::DualLog("Enemy " + EntityData.DisplayName + " is healed for " +
		FString::FromInt(Healing) + " health points.", 3);
	
	return IInterfaceBattle::ReceiveHealing(Healing);
}


bool AActorEntityEnemy::GainBarrier(int InBarrier)
{
	EntityData.Stats.CurrentBarrierPoints += InBarrier;

	ALostWorldGameModeBase::DualLog("Enemy " + EntityData.DisplayName + " gains " +
		FString::FromInt(InBarrier) + " barrier.", 3);
	
	return IInterfaceBattle::GainBarrier(InBarrier);
}


bool AActorEntityEnemy::StartTurn()
{
	ALostWorldGameModeBase::DualLog("Enemy " + EntityData.DisplayName + " is taking their turn.", 3);
	
	AiBrainComponent->StartTurn();
	
	return true;
}


bool AActorEntityEnemy::EndTurn()
{
	ALostWorldGameModeBase::DualLog("Enemy " + EntityData.DisplayName + " is ending their turn.", 3);
	
	return IInterfaceBattle::EndTurn();
}