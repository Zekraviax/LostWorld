#include "FunctionLibraryCards.h"


#include "ActorEntityEnemy.h"
#include "InterfaceBattle.h"
#include "LostWorldGameInstanceBase.h"
#include "LostWorldGameModeBattle.h"
#include "Kismet/GameplayStatics.h"


void AFunctionLibraryCards::ExecuteFunction(ECardFunctions InFunction) const
{
	switch (InFunction)
	{
	case (ECardFunctions::TestFunctionOne):
		TestCardOne();
		break;
	case (ECardFunctions::TestFunctionTwo):
		TestCardTwo();
		break;
	case (ECardFunctions::TestFunctionThree):
		TestCardThree();
		break;
	case (ECardFunctions::TestFunctionFour):
		TestCardFour();
		break;
	case (ECardFunctions::PoisonDart):
		PoisonDart();
		break;
	case (ECardFunctions::ArmourBreaker):
		ArmourBreaker();
		break;
	case (ECardFunctions::HyperBeam):
		HyperBeam();
		break;
	case (ECardFunctions::TestFunctionFive):
		TestCardFive();
		break;
	case (ECardFunctions::TestFunctionSix):
		TestCardSix();
		break;
	case (ECardFunctions::HowlOfCommand):
		HowlOfCommand();
		break;
	case (ECardFunctions::EnergyAllAround):
		EnergyAllAround();
		break;
	case (ECardFunctions::InfectedBite):
		InfectedBite();
		break;
	case (ECardFunctions::InflictToughnessDown):
		ApplyToughnessDown();
		break;
	case (ECardFunctions::Vomit):
		Vomit();
		break;
	case (ECardFunctions::CasterDrawsOneCard):
		DrawOneCard();
		break;
	default:
		FString ErrorMessage = "Error! Function " + UEnum::GetDisplayValueAsText(InFunction).ToString() +
			" does not have an implementation!";
		ALostWorldGameModeBase::DualLog(ErrorMessage, 2);
		break;
	}
}


AActorEntityBase* AFunctionLibraryCards::GetAttacker() const
{
	return Cast<ALostWorldGameModeBattle>(GetWorld()->GetAuthGameMode())->TheStack[0].Controller;
}


AActorEntityBase* AFunctionLibraryCards::GetDefender() const
{
	return Cast<ALostWorldGameModeBattle>(GetWorld()->GetAuthGameMode())->TheStack[0].SelectedTargets[0];
}


int AFunctionLibraryCards::StandardDamageFormula(const AActorEntityBase* Attacker, const AActorEntityBase* Defender, int AttackBasePower)
{
	// Damage formula
	// Step 1 = ((Strength * Attack) / 2) * Rand(0.95, 1.1)
	// Step 2 = Step1 / (Defence * Rand(0.95 * 1.05))
	// Step 3 = RoundUp(Step2)
	// Step 4 = Apply offensive elemental affinity.
	// Step 5 = Apply defensive elemental affinity.

	// To-Do: Check for status effects that modify total damage and/or base power.
	for (FStatusEffect StatusEffect : Defender->EntityData.StatusEffects) {
		if (StatusEffect.StatusEffect == EStatusEffectFunctions::Howl) {
			AttackBasePower += 2;
		}
	}

	float CalculatedDamage = Attacker->EntityData.TotalStats.Strength * AttackBasePower;
	CalculatedDamage -= 2;
	CalculatedDamage *= FMath::RandRange(0.95f, 1.1f);
	CalculatedDamage /= Defender->EntityData.TotalStats.Toughness;
	CalculatedDamage *= FMath::RandRange(0.95f, 1.1f);

	return FMath::RoundToInt(CalculatedDamage);
}


int AFunctionLibraryCards::ArmourBreakerDamageFormula(const AActorEntityBase* Attacker, const AActorEntityBase* Defender, int AttackBasePower)
{
	// Damage formula is the same as the standard formula, except damage is doubled against barriers.
	// So for each 1 point of barrier the defender has, add 1 point of damage, capping out at 2x the calculated damage.
	int CalculatedDamage = StandardDamageFormula(Attacker, Defender, AttackBasePower);
	int BarrierPoints = Defender->EntityData.TotalStats.CurrentBarrierPoints;
	int BonusDamage = 0;
	
	while (BarrierPoints > 0 && BonusDamage < FMath::RoundToInt(CalculatedDamage)) {
		BarrierPoints--;
		BonusDamage++;
	}

	return FMath::RoundToInt(CalculatedDamage + BonusDamage);
}


void AFunctionLibraryCards::TestCardOne() const
{
	Cast<IInterfaceBattle>(GetDefender())->TakeDamage(StandardDamageFormula(GetAttacker(), GetDefender(),
		Cast<ALostWorldGameModeBattle>(GetWorld()->GetAuthGameMode())->TheStack[0].Card.TotalDamage));
}


void AFunctionLibraryCards::TestCardTwo() const
{
	for (AActorEntityBase* Enemy : Cast<ALostWorldGameModeBattle>(GetWorld()->GetAuthGameMode())->TheStack[0].SelectedTargets) {
		if (Cast<AActorEntityEnemy>(Enemy)) {
			Cast<IInterfaceBattle>(Enemy)->TakeDamage(StandardDamageFormula(GetAttacker(), Enemy,
				Cast<ALostWorldGameModeBattle>(GetWorld()->GetAuthGameMode())->TheStack[0].Card.TotalDamage));
		}
	}
}


void AFunctionLibraryCards::TestCardThree() const
{
	Cast<IInterfaceBattle>(Cast<ALostWorldGameModeBattle>(GetWorld()->GetAuthGameMode())->TheStack[0].Controller)->DrawCard();
}


void AFunctionLibraryCards::TestCardFour() const
{
	Cast<IInterfaceBattle>(Cast<ALostWorldGameModeBattle>(GetWorld()->GetAuthGameMode())->TheStack[0].Controller)->ReceiveHealing(5);
}


void AFunctionLibraryCards::PoisonDart() const
{
	Cast<IInterfaceBattle>(GetDefender())->TakeDamage(StandardDamageFormula(GetAttacker(), GetDefender(),
		Cast<ALostWorldGameModeBattle>(GetWorld()->GetAuthGameMode())->TheStack[0].Card.TotalDamage));

	Cast<IInterfaceBattle>(GetDefender())->AddStatusEffect(Cast<ULostWorldGameInstanceBase>(
		GetWorld()->GetGameInstance())->GetStatusEffectFromJson(EStatusEffectFunctions::Poison));
}


void AFunctionLibraryCards::ArmourBreaker() const
{
	Cast<IInterfaceBattle>(GetDefender())->TakeDamage(StandardDamageFormula(GetAttacker(), GetDefender(),
		Cast<ALostWorldGameModeBattle>(GetWorld()->GetAuthGameMode())->TheStack[0].Card.TotalDamage));
}


void AFunctionLibraryCards::HyperBeam() const
{
	int BasePower = Cast<ALostWorldGameModeBattle>(GetWorld()->GetAuthGameMode())->TheStack[0].Card.TotalCost * 2;

	Cast<IInterfaceBattle>(GetDefender())->TakeDamage(StandardDamageFormula(GetAttacker(), GetDefender(), BasePower));
}


void AFunctionLibraryCards::TestCardFive() const
{
	// Draw cards until your deck is empty, then draw one more.
	while (GetAttacker()->EntityData.Deck.Num() > 0) {
		Cast<IInterfaceBattle>(GetAttacker())->DrawCard();
	}

	Cast<IInterfaceBattle>(GetAttacker())->DrawCard();
}


void AFunctionLibraryCards::TestCardSix() const
{
	FSummonEntity SummonData = Cast<ULostWorldGameInstanceBase>(GetWorld()->GetGameInstance())->
		GetSummonFromJson("Test Summon");

	SummonData.EntityData.Team = GetAttacker()->EntityData.Team;
	
	// Spawn the summon and make it the same team as the entity summoning it
	Cast<ALostWorldGameModeBattle>(GetWorld()->GetAuthGameMode())->SpawnPlayerEntity(SummonData.EntityData);
}


void AFunctionLibraryCards::HowlOfCommand() const
{
	// First, get all Wolf Pack allies and set their target overrides.
	TArray<AActor*> FoundActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AActorEntityBase::StaticClass(), FoundActors);

	// Find each entity that isn't on the same team as this one.
	TArray<AActorEntityBase*> FoundEnemies;
	for (AActor* Actor : FoundActors) {
		if (Cast<AActorEntityBase>(Actor)->EntityData.Team != GetAttacker()->EntityData.Team) {
			FoundEnemies.Add(Cast<AActorEntityBase>(Actor));
			break;
		}
	}

	for (AActor* Actor : FoundActors) {
		if (Cast<AActorEntityBase>(Actor)->EntityData.Team == GetAttacker()->EntityData.Team &&
			Cast<AActorEntityBase>(Actor)->EntityData.EntityTypes.Contains(EEntityTypes::WolfPack) &&
			Cast<AActorEntityBase>(Actor)->FindComponentByClass<UAiBrainBase>()) {
			Cast<AActorEntityBase>(Actor)->FindComponentByClass<UAiBrainBase>()->AttackTargetsOverride.Empty();
			Cast<AActorEntityBase>(Actor)->FindComponentByClass<UAiBrainBase>()->AttackTargetsOverride.Add(FoundEnemies[0]);

			ALostWorldGameModeBase::DualLog(Cast<AActorEntityBase>(Actor)->EntityData.DisplayName +
				" is targeting " + FoundEnemies[0]->EntityData.DisplayName + "!", 2);
		}
	}

	// Second, inflict the target with the Howl status effect that increases the power of cards targeted at them.
	Cast<IInterfaceBattle>(GetDefender())->AddStatusEffect(Cast<ULostWorldGameInstanceBase>(
		GetWorld()->GetGameInstance())->GetStatusEffectFromJson(EStatusEffectFunctions::Howl));
}


void AFunctionLibraryCards::EnergyAllAround() const
{
	int BasePower = Cast<ALostWorldGameModeBattle>(GetWorld()->GetAuthGameMode())->CardsCastThisTurn + 1;

	Cast<IInterfaceBattle>(GetDefender())->
		TakeDamage(ArmourBreakerDamageFormula(GetAttacker(), GetDefender(), BasePower));
}


void AFunctionLibraryCards::CallForFriends() const
{
	bool RandomSuccess = FMath::RandBool();

	ALostWorldGameModeBase::DualLog(Cast<AActorEntityBase>(GetAttacker())->EntityData.DisplayName +
				" tries to call for friends!", 2);
	
	if (RandomSuccess) {
		// Get the entity type and spawn another one.
		FSummonEntity SummonData = Cast<ULostWorldGameInstanceBase>(GetWorld()->GetGameInstance())->
			GetSummonFromJson("Test Summon");

		SummonData.EntityData.Team = GetAttacker()->EntityData.Team;
	
		// Spawn the summon and make it the same team as the entity summoning it.
		if (Cast<AActorEntityEnemy>(this)) {
			// To-Do: Get EnemyData when an enemy uses a summon.
			FEnemyEntity EnemyData = FEnemyEntity();
			Cast<ALostWorldGameModeBattle>(GetWorld()->GetAuthGameMode())->SpawnEnemyEntity(EnemyData, SummonData.EntityData);
		} else {
			Cast<ALostWorldGameModeBattle>(GetWorld()->GetAuthGameMode())->SpawnPlayerEntity(SummonData.EntityData);
		}

		ALostWorldGameModeBase::DualLog("A " + SummonData.EntityData.DisplayName + "appeared!", 2);
	} else {
		ALostWorldGameModeBase::DualLog("But it failed.", 2);
	}
}


void AFunctionLibraryCards::InfectedBite() const
{
	GenericDealDamageToOneTarget();

	if (FMath::RandBool()) {
		Cast<IInterfaceBattle>(GetDefender())->AddStatusEffect(Cast<ULostWorldGameInstanceBase>(
		GetWorld()->GetGameInstance())->GetStatusEffectFromJson(EStatusEffectFunctions::Poison));
	} else {
		Cast<IInterfaceBattle>(GetDefender())->AddStatusEffect(Cast<ULostWorldGameInstanceBase>(
		GetWorld()->GetGameInstance())->GetStatusEffectFromJson(EStatusEffectFunctions::Bleeding));
	}
}


void AFunctionLibraryCards::Vomit() const
{
	FStatusEffect StackedPoison = Cast<ULostWorldGameInstanceBase>(
		GetWorld()->GetGameInstance())->GetStatusEffectFromJson(EStatusEffectFunctions::Poison);
	StackedPoison.CurrentStackCount = 3;

	Cast<IInterfaceBattle>(GetDefender())->AddStatusEffect(StackedPoison);
}


void AFunctionLibraryCards::GenericDealDamageToOneTarget() const
{
	Cast<IInterfaceBattle>(GetDefender())->TakeDamage(StandardDamageFormula(GetAttacker(), GetDefender(),
		Cast<ALostWorldGameModeBattle>(GetWorld()->GetAuthGameMode())->TheStack[0].Card.TotalDamage));
}


void AFunctionLibraryCards::DrawOneCard() const
{
	Cast<IInterfaceBattle>(GetDefender())->DrawCard();
}


void AFunctionLibraryCards::ApplyToughnessDown() const
{
	Cast<IInterfaceBattle>(GetDefender())->AddStatusEffect(Cast<ULostWorldGameInstanceBase>(
		GetWorld()->GetGameInstance())->GetStatusEffectFromJson(EStatusEffectFunctions::ToughnessDown));

	// Tell the defender to re-calculate their stats.
	Cast<IInterfaceEntity>(GetDefender())->CalculateTotalStats();
}
