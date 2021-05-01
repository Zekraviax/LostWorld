#include "WidgetComponent_RoomEncounter.h"

#include "BaseClass_PlayerController.h"


void UWidgetComponent_RoomEncounter::SelectedEncounter()
{
	ABaseClass_PlayerController* LocalPlayerControllerRef = Cast<ABaseClass_PlayerController>(GetWorld()->GetFirstPlayerController());
	FString ContextString;

	// Check if the player has enough cards in deck
	if (LocalPlayerControllerRef->CurrentEntityData.CurrentDeck.Num() >= 10 ) {
		if (EncounterData.EncounterListEntry.DataTable != NULL) {
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Cyan, TEXT("Encounter Type: Enemy"));

			// Set Active Encounter
			for (int i = 0; i < LocalPlayerControllerRef->CurrentRoom->EncountersList.Num(); i++) {
				if (LocalPlayerControllerRef->CurrentRoom->EncountersList[i].DisplayName == EncounterData.DisplayName) {
					LocalPlayerControllerRef->CurrentRoom->EncountersList[i].CurrentlyActiveEncounter = true;
				}
			}

			LocalPlayerControllerRef->BeginBattle();
		}
	}
	else 
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Not Enough Cards In Deck. Minimum 10."));
}