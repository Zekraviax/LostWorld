#include "TraitFunctions_IronShellAutomaton.h"

#include "BaseClass_EntityInBattle.h"


// ------------------------- Triggered Functions
void ATraitFunctions_IronShellAutomaton::TriggeredFunction_StartOfBattle(ABaseClass_EntityInBattle* Self)
{
	Self->EntityBaseData.Barrier += 90;
}