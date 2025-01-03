#include "ActorEntityEnemy.h"


#include "AiBrainBase.h"
#include "AiBrainTestEnemyOne.h"
#include "AiBrainTestEnemyTwo.h"
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
	} else if ("TestEnemyTwo") {
		AiBrainComponent = NewObject<UAiBrainTestEnemyTwo>(this);
	}
}


// -------------------------------- Battle Interface functions
bool AActorEntityEnemy::OverrideDeck(TArray<FCard> InDeck)
{
	return Super::OverrideDeck(InDeck);
}


bool AActorEntityEnemy::AddCardToDeck(FCard InCard)
{
	return Super::AddCardToDeck(InCard);
}


TArray<FCard> AActorEntityEnemy::ShuffleDeck(TArray<FCard> InDeck)
{
	// The Shuffle Deck function doesn't need to have multiple different definitions,
	// so we can just use the default one.
	return Super::ShuffleDeck(Deck);
}

bool AActorEntityEnemy::DrawCard()
{
	// Shift the top card of the deck into the hand
	return Super::DrawCard();
}

bool AActorEntityEnemy::DiscardCard(int IndexInHand)
{
	return Super::DiscardCard(IndexInHand);
}

bool AActorEntityEnemy::PayCostsForCard(int IndexInHand)
{
	return Super::PayCostsForCard(IndexInHand);
}


bool AActorEntityEnemy::TakeDamage(float Damage)
{
	AActorEntityBase::TakeDamage(Damage);

	ALostWorldGameModeBase::DualLog("Enemy " + EntityData.DisplayName + " takes " +
		FString::FromInt(Damage) + " damage.", 3);

	// Note: Bear in mind that this actor could use the IInterface's default implementation, but doesn't
	// in order to avoid any unexpected behaviors from calling the same function twice.
	return IInterfaceBattle::TakeDamage(Damage);
}


bool AActorEntityEnemy::EntityDefeated()
{
	return Super::EntityDefeated();
}


bool AActorEntityEnemy::ReceiveHealing(float Healing)
{
	ALostWorldGameModeBase::DualLog("Enemy " + EntityData.DisplayName + " is healed for " +
		FString::FromInt(Healing) + " health points.", 3);

	Cast<UWidgetEntityBillboard>(EntityBillboard->GetUserWidgetObject())->UpdateBillboard(EntityData);

	// Note: Bear in mind that this actor could use the IInterface's default implementation, but doesn't
	// in order to avoid any unexpected behaviors from calling the same function twice.
	return IInterfaceBattle::ReceiveHealing(Healing);
}


bool AActorEntityEnemy::GainBarrier(int InBarrier)
{
	EntityData.Stats.CurrentBarrierPoints += InBarrier;

	ALostWorldGameModeBase::DualLog("Enemy " + EntityData.DisplayName + " gains " +
		FString::FromInt(InBarrier) + " barrier.", 3);

	Cast<UWidgetEntityBillboard>(EntityBillboard->GetUserWidgetObject())->UpdateBillboard(EntityData);

	// Note: Bear in mind that this actor could use the IInterface's default implementation, but doesn't
	// in order to avoid any unexpected behaviors from calling the same function twice.
	return IInterfaceBattle::GainBarrier(InBarrier);
}


bool AActorEntityEnemy::AddStatusEffect(FStatusEffect StatusEffect)
{
	return Super::AddStatusEffect(StatusEffect);
}


bool AActorEntityEnemy::StartTurn()
{
	ALostWorldGameModeBase::DualLog("Enemy " + EntityData.DisplayName + " is taking their turn.", 3);
	
	AiBrainComponent->StartTurn();
	
	return Super::StartTurn();
}


bool AActorEntityEnemy::EndTurn()
{
	ALostWorldGameModeBase::DualLog("Enemy " + EntityData.DisplayName + " is ending their turn.", 3);
	
	return Super::EndTurn();
}