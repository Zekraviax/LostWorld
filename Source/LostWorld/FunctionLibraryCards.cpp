#include "FunctionLibraryCards.h"


#include "ActorEntityEnemy.h"
#include "InterfaceBattle.h"
#include "LostWorldGameInstanceBase.h"
#include "LostWorldGameModeBattle.h"


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
		case (ECardFunctions::TestFunctionFive):
			TestCardFive();
		default:
			break;
	}
}


int AFunctionLibraryCards::StandardDamageFormula(AActorEntityBase* Attacker, AActorEntityBase* Defender, const int AttackBasePower)
{
	// Damage formula
	// Step1 = ((Strength * Attack) / 2) * Rand(0.95, 1.1)
	// Step2 = Step1 / (Defence * Rand(0.95 * 1.05))
	// Step3 = RoundUp(Step2)

	float CalculatedDamage = Attacker->EntityData.Stats.Strength * AttackBasePower;
	CalculatedDamage -= 2;
	CalculatedDamage *= FMath::RandRange(0.95f, 1.1f);
	CalculatedDamage /= Defender->EntityData.Stats.Toughness;
	CalculatedDamage *= FMath::RandRange(0.95f, 1.1f);

	return FMath::RoundToInt(CalculatedDamage);
}


int AFunctionLibraryCards::ArmourBreakerDamageFormula(const AActorEntityBase* Attacker, const AActorEntityBase* Defender, int AttackBasePower)
{
	// Damage formula is the same as the standard formula, except damage is doubled against barriers.
	// So for each 1 point of barrier the defender has, add 1 point of damage, capping out at 2x the calculated damage.
	float CalculatedDamage = Attacker->EntityData.Stats.Strength * AttackBasePower;
	CalculatedDamage -= 2;
	CalculatedDamage *= FMath::RandRange(0.95f, 1.1f);
	CalculatedDamage /= Defender->EntityData.Stats.Toughness;
	CalculatedDamage *= FMath::RandRange(0.95f, 1.1f);
	
	int BarrierPoints = Defender->EntityData.Stats.CurrentBarrierPoints;
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
	
	Cast<IInterfaceBattle>(Defender)->TakeDamage(StandardDamageFormula(Attacker, Defender, 10));
}


void AFunctionLibraryCards::TestCardTwo() const
{
	AActorEntityBase* Attacker = Cast<ALostWorldGameModeBattle>(GetWorld()->GetAuthGameMode())->TheStack[0].Controller;
	
	for (AActorEntityBase* Enemy : Cast<ALostWorldGameModeBattle>(GetWorld()->GetAuthGameMode())->TheStack[0].SelectedTargets) {
		if (Cast<AActorEntityEnemy>(Enemy)) {
			Cast<AActorEntityEnemy>(Enemy)->TakeDamage(StandardDamageFormula(Attacker, Cast<AActorEntityEnemy>(Enemy), 5));
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

	Cast<IInterfaceBattle>(Defender)->TakeDamage(StandardDamageFormula(Attacker, Defender, 2));
	Cast<IInterfaceBattle>(Defender)->AddStatusEffect(Cast<ULostWorldGameInstanceBase>(GetWorld()->GetGameInstance())->
		GetStatusEffectFromJson("Poison Test"));
}


void AFunctionLibraryCards::ArmourBreaker() const
{
	AActorEntityBase* Attacker = Cast<ALostWorldGameModeBattle>(GetWorld()->GetAuthGameMode())->TheStack[0].Controller;
	AActorEntityBase* Defender = Cast<ALostWorldGameModeBattle>(GetWorld()->GetAuthGameMode())->TheStack[0].SelectedTargets[0];

	Cast<IInterfaceBattle>(Defender)->TakeDamage(ArmourBreakerDamageFormula(Attacker, Defender, 12));
}


void AFunctionLibraryCards::HyperBeam() const
{
	int BasePower = 1;
	AActorEntityBase* Attacker = Cast<ALostWorldGameModeBattle>(GetWorld()->GetAuthGameMode())->TheStack[0].Controller;
	AActorEntityBase* Defender = Cast<ALostWorldGameModeBattle>(GetWorld()->GetAuthGameMode())->TheStack[0].SelectedTargets[0];

	Cast<IInterfaceBattle>(Defender)->TakeDamage(ArmourBreakerDamageFormula(Attacker, Defender, BasePower));
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