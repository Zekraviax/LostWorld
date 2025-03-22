#include "ActorEntityBase.h"

#include "FunctionLibraryStatusEffects.h"
#include "LostWorldGameModeBase.h"
#include "LostWorldGameModeBattle.h"
#include "WidgetEntityBillboard.h"


// Sets default values
AActorEntityBase::AActorEntityBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AActorEntityBase::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AActorEntityBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


void AActorEntityBase::ResetEntityBillboardPositionAndRotation() const
{
	if (EntityBillboard) {
		if (EntityBillboard->GetRelativeLocation() != FVector(0.f, 0.f, 150.f)) {
			EntityBillboard->SetRelativeLocation(FVector(0.f, 0.f, 150.f));
		}

		if (EntityBillboard->GetRelativeRotation() != FRotator(10.f, 135.f, 0.f)) {
			EntityBillboard->SetRelativeRotation(FRotator(10.f, 135.f, 0.f));
		}
	}
}


// -------------------------------- Battle Interface functions
bool AActorEntityBase::AddCardToDeck(FCard InCard)
{
	EntityData.Deck.Add(InCard);
	
	return IInterfaceBattle::AddCardToDeck(InCard);
}


bool AActorEntityBase::AddCardToDrawPile(FCard InCard)
{
	EntityData.DrawPile.Add(InCard);
	
	return IInterfaceBattle::AddCardToDrawPile(InCard);
}


TArray<FCard> AActorEntityBase::ShuffleDrawPile(TArray<FCard> InDeck)
{
	// The Shuffle Deck function doesn't need to have multiple different definitions,
	// so we can just use the default one.
	return IInterfaceBattle::ShuffleDrawPile(EntityData.DrawPile);
}

bool AActorEntityBase::DrawCard()
{
	if (EntityData.DrawPile.Num() < 1) {
		// If there's no cards in the deck, check if there are any cards in the discard pile.
		// If there are, shuffle the discard pile into the deck.
		if (EntityData.DiscardPile.Num() > 0) {
			ShuffleDiscardPileIntoDrawPile();
		} else {
			ALostWorldGameModeBattle::DualLog(EntityData.DisplayName + " can't draw any cards!", 2);
		}
	}
	
	// Shift the top card of the deck into the hand.
	EntityData.Hand.Add(EntityData.DrawPile[0]);
	EntityData.DrawPile.RemoveAt(0);
	
	return IInterfaceBattle::DrawCard();
}


bool AActorEntityBase::DiscardCard(int IndexInHand)
{
	EntityData.DiscardPile.Add(EntityData.Hand[IndexInHand]);
	EntityData.Hand.RemoveAt(IndexInHand);
	
	return IInterfaceBattle::DiscardCard(IndexInHand);
}


bool AActorEntityBase::PayCostsForCard(int IndexInHand)
{
	TArray<ECardFunctions> CardFunctions;
	EntityData.Hand[IndexInHand].FunctionsAndTargets.GetKeys(CardFunctions);
	
	if (CardFunctions.Contains(ECardFunctions::CostsAllMana)) {
		Cast<ALostWorldGameModeBattle>(GetWorld()->GetAuthGameMode())->TempStackEntry.Card.TotalCost =
			EntityData.TotalStats.CurrentManaPoints;
		
		EntityData.TotalStats.CurrentManaPoints = 0;
	} else {
		EntityData.TotalStats.CurrentManaPoints -= EntityData.Hand[IndexInHand].TotalCost;
	}
	Cast<UWidgetEntityBillboard>(EntityBillboard->GetUserWidgetObject())->UpdateBillboard(EntityData);
	
	return IInterfaceBattle::PayCostsForCard(IndexInHand);
}


bool AActorEntityBase::ShuffleDiscardPileIntoDrawPile()
{
	if (EntityData.DiscardPile.Num() > 0) {
		for (int DiscardCount = 0; DiscardCount < EntityData.DiscardPile.Num(); DiscardCount++) {
			EntityData.DrawPile.Add(EntityData.DiscardPile[DiscardCount]);
		}
	}

	EntityData.DiscardPile.Empty();
	ShuffleDrawPile(EntityData.DrawPile);
	
	return IInterfaceBattle::ShuffleDiscardPileIntoDrawPile();
}


bool AActorEntityBase::TakeDamage(float Damage)
{
	// First, any barriers up will absorb damage.
	while (Damage > 0 && EntityData.TotalStats.CurrentBarrierPoints > 0) {
		Damage--;
		EntityData.TotalStats.CurrentBarrierPoints--;
	}

	// Then, damage will be go to the entity's raw health.
	if (Damage > 0) {
		EntityData.TotalStats.CurrentHealthPoints -= Damage;
	
		if (EntityData.TotalStats.CurrentHealthPoints <= 0) {
			EntityDefeated();
		}
	}

	if (EntityBillboard->GetUserWidgetObject()) {
		Cast<UWidgetEntityBillboard>(EntityBillboard->GetUserWidgetObject())->UpdateBillboard(EntityData);
	}
	
	
	return IInterfaceBattle::TakeDamage(Damage);
}


bool AActorEntityBase::EntityDefeated()
{
	ALostWorldGameModeBase::DualLog(EntityData.DisplayName + "has been defeated!", 2);

	// Remove the entity from the EntitiesInBattle array.
	Cast<ALostWorldGameModeBattle>(GetWorld()->GetAuthGameMode())->EntitiesInBattleArray.Remove(this);

	if (Cast<ALostWorldGameModeBattle>(GetWorld()->GetAuthGameMode())->TurnQueue[0] == this) {
		// If the entity died during it's own turn, end the turn.
		EndTurn();
	}

	// Re-calculate the turn queue.
	Cast<ALostWorldGameModeBattle>(GetWorld()->GetAuthGameMode())->RemoveEntityFromTurnQueue(this);

	// Check if there is only one team standing.
	Cast<ALostWorldGameModeBattle>(GetWorld()->GetAuthGameMode())->EndOfBattleCheck();

	// Physically deleting the actor should be the last thing done here.
	Destroy();

	return IInterfaceBattle::EntityDefeated();
}


bool AActorEntityBase::ReceiveHealing(float Healing)
{
	EntityData.TotalStats.CurrentHealthPoints += Healing;
	
	if (EntityData.TotalStats.CurrentHealthPoints > EntityData.TotalStats.MaximumHealthPoints) {
		EntityData.TotalStats.CurrentHealthPoints = EntityData.TotalStats.MaximumHealthPoints;
	}
	
	Cast<UWidgetEntityBillboard>(EntityBillboard->GetUserWidgetObject())->UpdateBillboard(EntityData);
	
	return IInterfaceBattle::ReceiveHealing(Healing);
}


bool AActorEntityBase::GainMana(int InMana)
{
	EntityData.TotalStats.CurrentManaPoints += InMana;
	
	return IInterfaceBattle::GainMana(InMana);
}


bool AActorEntityBase::GainBarrier(int InBarrier)
{
	EntityData.TotalStats.CurrentBarrierPoints += InBarrier;
	Cast<UWidgetEntityBillboard>(EntityBillboard->GetUserWidgetObject())->UpdateBillboard(EntityData);
	
	return IInterfaceBattle::GainBarrier(InBarrier);
}


bool AActorEntityBase::AddStatusEffect(FStatusEffect InStatusEffect)
{
	if (EntityData.TotalStats.CurrentBarrierPoints > 0 && InStatusEffect.BlockedByBarrier) {
		ALostWorldGameModeBase::DualLog("A barrier blocked the status effect from being applied!", 2);
	} else {
		// To-Do: Make status effects add stacks to status effects that the entity already has.

		// Check if the entity already has the status effect.
		// If so, attempt to increment its' stacks.
		bool hasStatus = false;
		for (auto& Status : EntityData.StatusEffects) {
			if (Status.StatusEffect == InStatusEffect.StatusEffect) {
				hasStatus = true;
				if (Status.CurrentStackCount < Status.MaximumStackCount) {
					// Apply stacks until the maximum is reached or there are no more stacks.
					while (InStatusEffect.CurrentStackCount > 0 && Status.CurrentStackCount < Status.MaximumStackCount) {
						InStatusEffect.CurrentStackCount--;
						Status.CurrentStackCount++;
					}
				} else {
					ALostWorldGameModeBase::DualLog(EntityData.DisplayName +
						" already has the maximum stacks of " + InStatusEffect.DisplayName + "!", 2);
				}
			}
		}
		
		if (!hasStatus) {
			EntityData.StatusEffects.Add(InStatusEffect);
		}
		
		switch (InStatusEffect.StatusEffect)
		{
		case (EStatusEffectFunctions::Poison):
			ALostWorldGameModeBase::DualLog(EntityData.DisplayName + " has been poisoned!", 2);
			break;
		case (EStatusEffectFunctions::StrengthUp):
			ALostWorldGameModeBase::DualLog(EntityData.DisplayName + " gained strength!", 2);
			break;
		case (EStatusEffectFunctions::Adrenaline):
			ALostWorldGameModeBase::DualLog(EntityData.DisplayName + "'s adrenaline is flowing!", 2);
			break;
		case (EStatusEffectFunctions::Bleeding):
			ALostWorldGameModeBase::DualLog(EntityData.DisplayName + " is now bleeding!", 2);
			break;
		case (EStatusEffectFunctions::ToughnessDown):
			ALostWorldGameModeBase::DualLog(EntityData.DisplayName + " lost toughness!", 2);
			break;
		default:
			break;
		}
	}
	
	return IInterfaceBattle::AddStatusEffect(InStatusEffect);
}


bool AActorEntityBase::StartTurn()
{
	// Check for status effects that trigger at the start of the owners' turn.
	if (EntityData.StatusEffects.Num() > 0) {
		for (FStatusEffect StatusEffect : EntityData.StatusEffects) {
			if (StatusEffect.TimingTriggers.Contains(ETimingTriggers::StartOfAffectedEntitiesTurn)) {
				AFunctionLibraryStatusEffects::ExecuteFunction(StatusEffect.StatusEffect, this);
			}
		}
	}

	// To-Do: For every entity, check for status effects that trigger at the start of every entity's turns.

	// Start of turn regenerations.
	if (EntityData.TotalStats.HealthRegeneration > 0) {
		ReceiveHealing(EntityData.TotalStats.HealthRegeneration);
	}
	
	if (EntityData.TotalStats.ManaRegeneration > 0) {
		GainMana(EntityData.TotalStats.ManaRegeneration);
	}
	
	return IInterfaceBattle::StartTurn();
}


bool AActorEntityBase::EndTurn()
{
	Cast<ALostWorldGameModeBattle>(GetWorld()->GetAuthGameMode())->CardsCastThisTurn = 0;

	// Decrement end-of-turn status effects here.
	if (EntityData.StatusEffects.Num() > 0) {
		for (int Index = EntityData.StatusEffects.Num() - 1; Index >= 0; Index--) {
			if (EntityData.StatusEffects[Index].DecrementStackTriggers.Contains(ETimingTriggers::EndOfAffectedEntitiesTurn)) {
				EntityData.StatusEffects[Index].CurrentStackCount--;
				ALostWorldGameModeBase::DualLog(EntityData.DisplayName + " has lost 1 stack of " +
						EntityData.StatusEffects[Index].DisplayName + ".", 2);

				if (EntityData.StatusEffects[Index].CurrentStackCount < 1) {
					ALostWorldGameModeBase::DualLog(EntityData.DisplayName + " no longer has " +
						EntityData.StatusEffects[Index].DisplayName + ".", 2);
					
					EntityData.StatusEffects.RemoveAt(Index);
				}
			}
		}
	}

	// To-Do: For every entity, check for status effects that trigger at the end of every entity's turns.
	
	return IInterfaceBattle::EndTurn();
}


bool AActorEntityBase::CalculateTotalStats()
{
	// To-Do: Figure out whether HP and MP values should be ignored when calculating stats.
	EntityData.TotalStats = EntityData.BaseStats;

	for (FEquipment EquippedItem : EntityData.EquippedItems) {
		EntityData.TotalStats.MaximumHealthPoints += EquippedItem.StatModifiers.MaximumHealthPoints;
		EntityData.TotalStats.MaximumManaPoints += EquippedItem.StatModifiers.MaximumManaPoints;
		EntityData.TotalStats.Strength += EquippedItem.StatModifiers.Strength;
		EntityData.TotalStats.Toughness += EquippedItem.StatModifiers.Toughness;
		EntityData.TotalStats.Intelligence += EquippedItem.StatModifiers.Intelligence;
		EntityData.TotalStats.Willpower += EquippedItem.StatModifiers.Willpower;
		EntityData.TotalStats.Agility += EquippedItem.StatModifiers.Agility;
		EntityData.TotalStats.HealthRegeneration += EquippedItem.StatModifiers.HealthRegeneration;
		EntityData.TotalStats.ManaRegeneration += EquippedItem.StatModifiers.ManaRegeneration;
	}

	// Find all status effects that influence an entity's total stats.
	for (auto& Status : EntityData.StatusEffects) {
		switch (Status.StatusEffect)
		{
		case (EStatusEffectFunctions::StrengthUp):
			EntityData.TotalStats.Strength += Status.CurrentStackCount;
		case (EStatusEffectFunctions::ToughnessDown):
			EntityData.TotalStats.Toughness -= Status.CurrentStackCount;
		default:
			break;
		}
	}
	
	return IInterfaceEntity::CalculateTotalStats();
}

bool AActorEntityBase::EquipItem(int IndexInInventoryArray)
{
	EntityData.EquippedItems.Add(EntityData.EquipmentInventory[IndexInInventoryArray]);
	EntityData.EquipmentInventory.RemoveAt(IndexInInventoryArray);
	
	return IInterfaceEntity::EquipItem(IndexInInventoryArray);
}


bool AActorEntityBase::UnequipItem(int IndexInInventoryArray)
{
	EntityData.EquipmentInventory.Add(EntityData.EquippedItems[IndexInInventoryArray]);
	EntityData.EquippedItems.RemoveAt(IndexInInventoryArray);
	
	return IInterfaceEntity::UnequipItem(IndexInInventoryArray);
}
