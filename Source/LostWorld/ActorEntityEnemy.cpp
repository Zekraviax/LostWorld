#include "ActorEntityEnemy.h"


#include "AiBrainBase.h"
#include "AiBrainTestEnemyOne.h"
#include "AiBrainTestEnemyTwo.h"
#include "AiBrainBaseWolfPack.h"
#include "AiBrainBaseWolfPackAlpha.h"
#include "AiBrainRabidRat.h"
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
	if (EntityData.EntityTypes.Contains(EEntityTypes::TestEnemyOne)) {
		AiBrainComponent = NewObject<UAiBrainTestEnemyOne>(this);
	} else if (EntityData.EntityTypes.Contains(EEntityTypes::TestEnemyTwo)) {
		AiBrainComponent = NewObject<UAiBrainTestEnemyTwo>(this);
	} else if (EntityData.EntityTypes.Contains(EEntityTypes::WolfPack)) {
		AiBrainComponent = NewObject<UAiBrainBaseWolfPack>(this);
	} else if (EntityData.EntityTypes.Contains(EEntityTypes::WolfPackAlpha)) {
		AiBrainComponent = NewObject<UAiBrainBaseWolfPackAlpha>(this);
	} else if (EntityData.EntityTypes.Contains(EEntityTypes::RabidRat)) {
		AiBrainComponent = NewObject<UAiBrainRabidRat>(this);
	} else {
		// Default brain.
		AiBrainComponent = NewObject<UAiBrainTestEnemyOne>(this);
	}
}


// -------------------------------- Battle Interface functions
bool AActorEntityEnemy::EntityTakeDamage(float Damage)
{
	AActorEntityBase::EntityTakeDamage(Damage);

	ALostWorldGameModeBase::DualLog("Enemy " + EntityData.DisplayName + " takes " +
		FString::FromInt(Damage) + " damage.", 2);

	// Note: Bear in mind that this actor could use the IInterface's default implementation, but doesn't
	// in order to avoid any unexpected behaviors from calling the same function twice.
	return IInterfaceBattle::EntityTakeDamage(Damage);
}


bool AActorEntityEnemy::ReceiveHealing(float Healing)
{
	Cast<UWidgetEntityBillboard>(EntityBillboard->GetUserWidgetObject())->UpdateBillboard(EntityData);

	// Note: Bear in mind that this actor could use the IInterface's default implementation, but doesn't
	// in order to avoid any unexpected behaviors from calling the same function twice.
	return IInterfaceBattle::ReceiveHealing(Healing);
}


bool AActorEntityEnemy::GainBarrier(int InBarrier)
{
	EntityData.TotalStats.CurrentBarrierPoints += InBarrier;

	ALostWorldGameModeBase::DualLog("Enemy " + EntityData.DisplayName + " gains " +
		FString::FromInt(InBarrier) + " barrier.", 2);

	Cast<UWidgetEntityBillboard>(EntityBillboard->GetUserWidgetObject())->UpdateBillboard(EntityData);

	// Note: Bear in mind that this actor could use the IInterface's default implementation, but doesn't
	// in order to avoid any unexpected behaviors from calling the same function twice.
	return IInterfaceBattle::GainBarrier(InBarrier);
}


bool AActorEntityEnemy::StartTurn()
{
	Super::StartTurn();
	
	if (HasStatusEffect(EStatusEffectFunctions::Stun)) {
		EndTurnTimerDelegate.BindUFunction(this, FName("EndTurn"));
		
		GetWorld()->GetTimerManager().SetTimer(EndTurnTimerHandle, EndTurnTimerDelegate, 1.5f, false);
	} else {
		AiBrainComponent->StartTurn();
	}

	return true;
}


bool AActorEntityEnemy::EndTurn()
{
	return Super::EndTurn();
}