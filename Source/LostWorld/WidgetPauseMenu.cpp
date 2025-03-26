#include "WidgetPauseMenu.h"

#include "ActorEntityPlayer.h"
#include "LostWorldGameInstanceBase.h"
#include "Kismet/GameplayStatics.h"


void UWidgetPauseMenu::SaveGame()
{
	TArray<AActor*> FoundPlayers;

	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AActorEntityPlayer::StaticClass(), FoundPlayers);
	
	// To-Do: Implement a pop-up prompt system that can warn the player when they're about to override their save.
	Cast<ULostWorldGameInstanceBase>(GetWorld()->GetGameInstance())->CurrentPlayerSave.EntityData =
		Cast<AActorEntityPlayer>(FoundPlayers[0])->EntityData;
		
	Cast<ULostWorldGameInstanceBase>(GetWorld()->GetGameInstance())->SavePlayerDataJson();
}

void UWidgetPauseMenu::LoadGame()
{
}

void UWidgetPauseMenu::ExitMenu()
{
	RemoveFromViewport();
}
