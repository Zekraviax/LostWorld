#include "CardFunctions_SpiderCompanion.h"


#include "BaseClass_EntityInBattle.h"
#include "BaseClass_GridTile.h"


ACardFunctions_SpiderCompanion::ACardFunctions_SpiderCompanion()
{
	// Summons DataTable
	static ConstructorHelpers::FObjectFinder<UDataTable> SummonsDataTable_Object(TEXT("DataTable'/Game/DataTables/Summons_List.Summons_List'"));
	if (SummonsDataTable_Object.Succeeded()) {
		SummonsTable = SummonsDataTable_Object.Object;
	}

	static ConstructorHelpers::FClassFinder<AActor> EntityInBattle_Class(TEXT("/Game/Entity_Battle_Blueprint"));
	if (EntityInBattle_Class.Succeeded()) {
		EntityInBattle_BlueprintClass = EntityInBattle_Class.Class;
	}
}


// ------------------------- Base Class Functions
void ACardFunctions_SpiderCompanion::RunCardAbilityFunction(FStackEntry StackEntry)
{
	if (SummonsTable) {
		if (Cast<ABaseClass_GridTile>(StackEntry.Card.CurrentTargets[0])) {
			FString ContextString;
			FActorSpawnParameters SpawnParameters;

			ABaseClass_EntityInBattle* SpiderCompanionActor_Reference = StackEntry.Card.Controller->GetWorld()->SpawnActor<ABaseClass_EntityInBattle>(EntityInBattle_BlueprintClass, StackEntry.Card.CurrentTargets[0]->GetActorLocation(), FRotator::ZeroRotator, SpawnParameters);
			F_NonPlayerEntity_DatabaseEntry* SpiderData = SummonsTable->FindRow<F_NonPlayerEntity_DatabaseEntry>(FName("SpiderCompanion"), ContextString);
			SpiderCompanionActor_Reference->EntityBaseData = SpiderData->EntityBaseData;

			// Set cards in deck
			SpiderCompanionActor_Reference->CardsInDeck.Empty();
			for (int i = 0; i < SpiderData->Cards.Num(); i++) {
				FCardBase Card = *SpiderData->Cards[i].DataTable->FindRow<FCardBase>(FName(SpiderData->Cards[i].RowName), ContextString);
				SpiderCompanionActor_Reference->CardsInDeck.Add(Card);
			}

			SpiderCompanionActor_Reference->PlayerControllerRef = StackEntry.Card.Controller->PlayerControllerRef;
			SpiderCompanionActor_Reference->Begin_Battle();

			// Add to turn queue
			Cast<ALostWorld_422GameStateBase>(GetWorld()->GetGameState())->SortedTurnOrderList.Add(SpiderCompanionActor_Reference);
		}
	}
}