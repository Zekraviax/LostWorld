#include "WidgetComponent_RoomEncounter.h"

#include "BaseClass_PlayerController.h"


void UWidgetComponent_RoomEncounter::SelectedEncounter()
{
	ABaseClass_PlayerController* LocalPlayerControllerRef = Cast<ABaseClass_PlayerController>(GetWorld()->GetFirstPlayerController());
	FString ContextString;

	if (EncounterData.EncounterListEntry.DataTable != NULL) {
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Cyan, TEXT("Encounter Type: Enemy"));

		// Set Active Encounter
		for (int i = 0; i < LocalPlayerControllerRef->CurrentRoom->EncountersList.Num(); i++) {
			if (LocalPlayerControllerRef->CurrentRoom->EncountersList[i].DisplayName == EncounterData.DisplayName) {
				LocalPlayerControllerRef->CurrentRoom->EncountersList[i].CurrentlyActiveEncounter = true;
			}
		}

		LocalPlayerControllerRef->CurrentRoom->SpawnEnemyFormation(*EncounterData.EncounterListEntry.DataTable->FindRow<F_LevelRoom_EnemyFormation>(FName(EncounterData.EncounterListEntry.RowName), ContextString));
		LocalPlayerControllerRef->BeginBattle();
	}
}