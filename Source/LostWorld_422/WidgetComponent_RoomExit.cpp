#include "WidgetComponent_RoomExit.h"

#include "BaseClass_EntityInBattle.h"
#include "BaseClass_PlayerController.h"


void UWidgetComponent_RoomExit::SelectedExit()
{
	ABaseClass_PlayerController* PlayerControllerRef = Cast<ABaseClass_PlayerController>(GetWorld()->GetFirstPlayerController());
	TArray<USceneComponent*> Components;
	FVector PlayerRestPointLocation;

	// Find the rest point
	RoomData.RoomReference->GetComponents(Components, true);

	for (int i = 0; i < Components.Num(); i++) {
		if (Components[i]->GetName() == "PlayerRestPoint") {
			PlayerRestPointLocation = Components[i]->GetComponentLocation();
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, FString::Printf(TEXT("Player Rest Point Location: %s"), *PlayerRestPointLocation.ToString()));
			break;
		}
	}

	// Move player and components to the room
	PlayerControllerRef->EntityInBattleRef->SetActorLocation(PlayerRestPointLocation);
	PlayerControllerRef->EntityInBattleRef->ResetComponentsLocations();

	RoomData.RoomReference->PlayerEnterRoom();
}