#include "CardFunctions_DingoCompanion.h"

#include "BaseClass_EntityInBattle.h"
#include "BaseClass_GridTile.h"
#include "LostWorld_422GameModeBase.h"


ACardFunctions_DingoCompanion::ACardFunctions_DingoCompanion()
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
void ACardFunctions_DingoCompanion::RunCardAbilityFunction(FStackEntry StackEntry)
{
	if (SummonsTable) {
		if (Cast<ABaseClass_GridTile>(StackEntry.Card.CurrentTargets[0])) {
			FString ContextString;
			FActorSpawnParameters SpawnParameters;

			ABaseClass_EntityInBattle* DingoCompanionActor_Reference = StackEntry.Card.Controller->GetWorld()->SpawnActor<ABaseClass_EntityInBattle>(EntityInBattle_BlueprintClass, StackEntry.Card.CurrentTargets[0]->GetActorLocation(), FRotator::ZeroRotator, SpawnParameters);
			F_NonPlayerEntity_DatabaseEntry* DingoData = SummonsTable->FindRow<F_NonPlayerEntity_DatabaseEntry>(FName("DingoCompanion"), ContextString);
			DingoCompanionActor_Reference->EntityBaseData = DingoData->EntityBaseData;

			// Set cards in deck
			DingoCompanionActor_Reference->CardsInDeck.Empty();
			for (int i = 0; i < DingoData->Cards.Num(); i++) {
				FCardBase Card = *DingoData->Cards[i].DataTable->FindRow<FCardBase>(FName(DingoData->Cards[i].RowName), ContextString);
				DingoCompanionActor_Reference->CardsInDeck.Add(Card);
			}

			DingoCompanionActor_Reference->PlayerControllerRef = StackEntry.Card.Controller->PlayerControllerRef;

			DingoCompanionActor_Reference->Event_EntitySpawnedInWorld();
			DingoCompanionActor_Reference->Begin_Battle();

			// Add to turn queue
			Cast<ALostWorld_422GameStateBase>(GetWorld()->GetGameState())->SortedTurnOrderList.Add(DingoCompanionActor_Reference);
		}
	}
}