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
		default:
			break;
	}
}


void AFunctionLibraryCards::TestCardOne()
{
	Cast<AActorEntityEnemy>(Cast<ALostWorldGameModeBattle>(GetWorld()->GetAuthGameMode())->TheStack[0].SelectedTargets[0])->TakeDamage(1);
}
