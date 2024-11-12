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


void AFunctionLibraryCards::TestCardOne() const
{
	// Damage formula
	// Step1 = ((Strength * Attack) / 2) * Rand(0.95, 1.1)
	// Step2 = Step1 / (Defence * Rand(0.95 * 1.05)
	// Step3 = RoundUp(Step2)

	//AActorEntityBase* Attacker;
	AActorEntityBase* Defender = Cast<ALostWorldGameModeBattle>(GetWorld()->GetAuthGameMode())->TheStack[0].SelectedTargets[0];
	
	Cast<AActorEntityEnemy>(Defender)->TakeDamage(10);
}


void AFunctionLibraryCards::TestCardTwo() const
{
	for (AActorEntityBase* Enemy : Cast<ALostWorldGameModeBattle>(GetWorld()->GetAuthGameMode())->TheStack[0].SelectedTargets) {
		if (Cast<AActorEntityEnemy>(Enemy)) {
			Cast<AActorEntityEnemy>(Enemy)->TakeDamage(5);
		}
	}
}
