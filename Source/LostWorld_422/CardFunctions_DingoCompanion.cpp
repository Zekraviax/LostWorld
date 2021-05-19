#include "CardFunctions_DingoCompanion.h"

#include "BaseClass_EntityInBattle.h"


ACardFunctions_DingoCompanion::ACardFunctions_DingoCompanion()
{
	// Summons DataTable
	static ConstructorHelpers::FObjectFinder<UDataTable> SummonsDataTable_Object(TEXT("DataTable'/Game/DataTables/Summons_List.Summons_List'"));
	if (SummonsDataTable_Object.Succeeded()) {
		SummonsTable = SummonsDataTable_Object.Object;
	}
}


// ------------------------- Base Class Functions
void ACardFunctions_DingoCompanion::RunCardAbilityFunction(FStackEntry StackEntry)
{

}