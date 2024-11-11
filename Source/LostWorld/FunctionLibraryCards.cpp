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
	Cast<AActorEntityEnemy>(Cast<ALostWorldGameModeBattle>(GetWorld()->GetAuthGameMode())->TheStack[0].SelectedTargets[0])->TakeDamage(10);
}


void AFunctionLibraryCards::TestCardTwo() const
{
	for (AActorEntityBase* Enemy : Cast<ALostWorldGameModeBattle>(GetWorld()->GetAuthGameMode())->TheStack[0].SelectedTargets) {
		if (Cast<AActorEntityEnemy>(Enemy)) {
			Cast<AActorEntityEnemy>(Enemy)->TakeDamage(5);
		}
	}
}
