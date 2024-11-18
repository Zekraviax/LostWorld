#include "FunctionLibraryCards.h"


#include "ActorEntityEnemy.h"
#include "LostWorldGameModeBattle.h"


void AFunctionLibraryCards::ExecuteFunction(ECardFunctions InFunction)
{
	switch (InFunction)
	{
		case (ECardFunctions::TestFunctionOne):
			TestCardOne();
			break;
		case (ECardFunctions::TestFunctionTwo):
			TestCardTwo();
			break;
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
	CalculatedDamage /= 2;
	CalculatedDamage *= FMath::RandRange(0.95f, 1.1f);
	CalculatedDamage /= Defender->EntityData.Stats.Toughness;
	CalculatedDamage *= FMath::RandRange(0.95f, 1.1f);

	return FMath::RoundToInt(CalculatedDamage);
}


void AFunctionLibraryCards::TestCardOne() const
{
	AActorEntityBase* Attacker = Cast<ALostWorldGameModeBattle>(GetWorld()->GetAuthGameMode())->TheStack[0].Controller;
	AActorEntityBase* Defender = Cast<ALostWorldGameModeBattle>(GetWorld()->GetAuthGameMode())->TheStack[0].SelectedTargets[0];
	
	Cast<AActorEntityEnemy>(Defender)->TakeDamage(StandardDamageFormula(Attacker, Defender, 10));
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
