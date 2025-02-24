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
		default:
			break;
	}
}


int AFunctionLibraryCards::StandardDamageFormula(const AActorEntityBase* Attacker, const AActorEntityBase* Defender, int AttackBasePower)
{
	// Damage formula
	// Step1 = ((Strength * Attack) / 2) * Rand(0.95, 1.1)
	// Step2 = Step1 / (Defence * Rand(0.95 * 1.05))
	// Step3 = RoundUp(Step2)

	// To-Do: Check for status effects that modify damage and/or base power
	for (FStatusEffect StatusEffect : Defender->StatusEffects) {
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
	AActorEntityBase* Attacker = Cast<ALostWorldGameModeBattle>(GetWorld()->GetAuthGameMode())->TheStack[0].Controller;
	AActorEntityBase* Defender = Cast<ALostWorldGameModeBattle>(GetWorld()->GetAuthGameMode())->TheStack[0].SelectedTargets[0];
	
	Cast<IInterfaceBattle>(Defender)->TakeDamage(StandardDamageFormula(Attacker, Defender,
		Cast<ALostWorldGameModeBattle>(GetWorld()->GetAuthGameMode())->TheStack[0].Card.TotalDamage));
}


void AFunctionLibraryCards::TestCardTwo() const
{
	AActorEntityBase* Attacker = Cast<ALostWorldGameModeBattle>(GetWorld()->GetAuthGameMode())->TheStack[0].Controller;
	
	for (AActorEntityBase* Enemy : Cast<ALostWorldGameModeBattle>(GetWorld()->GetAuthGameMode())->TheStack[0].SelectedTargets) {
		if (Cast<AActorEntityEnemy>(Enemy)) {
			Cast<IInterfaceBattle>(Enemy)->TakeDamage(StandardDamageFormula(Attacker, Enemy,
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
	AActorEntityBase* Attacker = Cast<ALostWorldGameModeBattle>(GetWorld()->GetAuthGameMode())->TheStack[0].Controller;
	AActorEntityBase* Defender = Cast<ALostWorldGameModeBattle>(GetWorld()->GetAuthGameMode())->TheStack[0].SelectedTargets[0];

	Cast<IInterfaceBattle>(Defender)->TakeDamage(StandardDamageFormula(Attacker, Defender,
		Cast<ALostWorldGameModeBattle>(GetWorld()->GetAuthGameMode())->TheStack[0].Card.TotalDamage));
}


void AFunctionLibraryCards::ArmourBreaker() const
{
	AActorEntityBase* Attacker = Cast<ALostWorldGameModeBattle>(GetWorld()->GetAuthGameMode())->TheStack[0].Controller;
	AActorEntityBase* Defender = Cast<ALostWorldGameModeBattle>(GetWorld()->GetAuthGameMode())->TheStack[0].SelectedTargets[0];

	Cast<IInterfaceBattle>(Defender)->TakeDamage(StandardDamageFormula(Attacker, Defender,
		Cast<ALostWorldGameModeBattle>(GetWorld()->GetAuthGameMode())->TheStack[0].Card.TotalDamage));
}


void AFunctionLibraryCards::HyperBeam() const
{
	int BasePower = Cast<ALostWorldGameModeBattle>(GetWorld()->GetAuthGameMode())->TheStack[0].Card.TotalCost * 2;
	AActorEntityBase* Attacker = Cast<ALostWorldGameModeBattle>(GetWorld()->GetAuthGameMode())->TheStack[0].Controller;
	AActorEntityBase* Defender = Cast<ALostWorldGameModeBattle>(GetWorld()->GetAuthGameMode())->TheStack[0].SelectedTargets[0];

	Cast<IInterfaceBattle>(Defender)->TakeDamage(StandardDamageFormula(Attacker, Defender, BasePower));
}


void AFunctionLibraryCards::TestCardFive() const
{
	AActorEntityBase* Attacker = Cast<ALostWorldGameModeBattle>(GetWorld()->GetAuthGameMode())->TheStack[0].Controller;
	
	// Draw cards until your deck is empty, then draw one more.
	while (Attacker->Deck.Num() > 0) {
		Cast<IInterfaceBattle>(Attacker)->DrawCard();
	}

	Cast<IInterfaceBattle>(Attacker)->DrawCard();
}


void AFunctionLibraryCards::TestCardSix() const
{
	// To-Do: Clean up these repetitive lines that get the Attacker and Defender
	AActorEntityBase* Attacker = Cast<ALostWorldGameModeBattle>(GetWorld()->GetAuthGameMode())->TheStack[0].Controller;
	FSummonEntity SummonData = Cast<ULostWorldGameInstanceBase>(GetWorld()->GetGameInstance())->GetSummonFromJson("Test Summon");

	SummonData.EntityData.Team = Attacker->EntityData.Team;
	
	// Spawn the summon and make it the same team as the entity summoning it
	Cast<ALostWorldGameModeBattle>(GetWorld()->GetAuthGameMode())->SpawnEntity(SummonData.EntityData);
}


void AFunctionLibraryCards::HowlOfCommand() const
{
	AActorEntityBase* Attacker = Cast<ALostWorldGameModeBattle>(GetWorld()->GetAuthGameMode())->TheStack[0].Controller;
	AActorEntityBase* Defender = Cast<ALostWorldGameModeBattle>(GetWorld()->GetAuthGameMode())->TheStack[0].SelectedTargets[0];
	
	// First, get all Wolf Pack allies and set their target overrides.
	TArray<AActor*> FoundActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AActorEntityBase::StaticClass(), FoundActors);

	// Find each entity that isn't on the same team as this one.
	TArray<AActorEntityBase*> FoundEnemies;
	
	for (AActor* Actor : FoundActors) {
		if (Cast<AActorEntityBase>(Actor)->EntityData.Team != Attacker->EntityData.Team) {
			FoundEnemies.Add(Cast<AActorEntityBase>(Actor));
			break;
		}
	}

	for (AActor* Actor : FoundActors) {
		if (Cast<AActorEntityBase>(Actor)->EntityData.Team == Attacker->EntityData.Team &&
			Cast<AActorEntityBase>(Actor)->EntityData.EntityTypes.Contains(EEntityTypes::WolfPack) &&
			Cast<AActorEntityBase>(Actor)->FindComponentByClass<UAiBrainBase>()) {
			Cast<AActorEntityBase>(Actor)->FindComponentByClass<UAiBrainBase>()->AttackTargetsOverride.Empty();
			Cast<AActorEntityBase>(Actor)->FindComponentByClass<UAiBrainBase>()->AttackTargetsOverride.Add(FoundEnemies[0]);

			ALostWorldGameModeBase::DualLog(Cast<AActorEntityBase>(Actor)->EntityData.DisplayName +
				" is targeting " + FoundEnemies[0]->EntityData.DisplayName + "!", 2);
		}
	}

	// Second, inflict the target with the Howl status effect that increases the power of cards targeted at them.
	Cast<IInterfaceBattle>(Defender)->AddStatusEffect(Cast<ULostWorldGameInstanceBase>(
		GetWorld()->GetGameInstance())->GetStatusEffectFromJson("Howl"));
}


void AFunctionLibraryCards::EnergyAllAround() const
{
	AActorEntityBase* Attacker = Cast<ALostWorldGameModeBattle>(GetWorld()->GetAuthGameMode())->TheStack[0].Controller;
	AActorEntityBase* Defender = Cast<ALostWorldGameModeBattle>(GetWorld()->GetAuthGameMode())->TheStack[0].SelectedTargets[0];
	int BasePower = Cast<ALostWorldGameModeBattle>(GetWorld()->GetAuthGameMode())->CardsCastThisTurn + 1;

	Cast<IInterfaceBattle>(Defender)->TakeDamage(ArmourBreakerDamageFormula(Attacker, Defender, BasePower));
}


void AFunctionLibraryCards::CallForFriends() const
{
	bool RandomSuccess = FMath::RandBool();
	AActorEntityBase* Attacker = Cast<ALostWorldGameModeBattle>(GetWorld()->GetAuthGameMode())->TheStack[0].Controller;

	ALostWorldGameModeBase::DualLog(Cast<AActorEntityBase>(Attacker)->EntityData.DisplayName +
				" tries to call for friends!", 2);
	
	if (RandomSuccess) {
		// Get the entity type and spawn another one.
		FSummonEntity SummonData = Cast<ULostWorldGameInstanceBase>(GetWorld()->GetGameInstance())->GetSummonFromJson("Test Summon");

		SummonData.EntityData.Team = Attacker->EntityData.Team;
	
		// Spawn the summon and make it the same team as the entity summoning it
		Cast<ALostWorldGameModeBattle>(GetWorld()->GetAuthGameMode())->SpawnEntity(SummonData.EntityData);

		ALostWorldGameModeBase::DualLog("A appeared!", 2);
	} else {
		ALostWorldGameModeBase::DualLog("But it failed.", 2);
	}
}


void AFunctionLibraryCards::DealDamageToOneTarget() const
{
	AActorEntityBase* Attacker = Cast<ALostWorldGameModeBattle>(GetWorld()->GetAuthGameMode())->TheStack[0].Controller;
	AActorEntityBase* Defender = Cast<ALostWorldGameModeBattle>(GetWorld()->GetAuthGameMode())->TheStack[0].SelectedTargets[0];

	Cast<IInterfaceBattle>(Defender)->TakeDamage(StandardDamageFormula(Attacker, Defender,
		Cast<ALostWorldGameModeBattle>(GetWorld()->GetAuthGameMode())->TheStack[0].Card.TotalDamage));
}
