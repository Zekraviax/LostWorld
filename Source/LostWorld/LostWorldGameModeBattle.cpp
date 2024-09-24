#include "LostWorldGameModeBattle.h"


#include "Kismet/GameplayStatics.h"
#include "SaveGameLevelData.h"


// -------------------------------- Battle 
void ALostWorldGameModeBattle::PreBattleShuffleDecks()
{
	
}


// -------------------------------- Level Generation
void ALostWorldGameModeBattle::LoadLevelData()
{
	if (!LevelDataSaveGameReference) {
		LevelDataSaveGameReference = Cast<USaveGameLevelData>(UGameplayStatics::CreateSaveGameObject(USaveGameLevelData::StaticClass()));
	}

	// If the LevelData var is equal to the default, that means it hasn't been loaded.
	if (LevelDataSaveGameReference->LevelData == FLevelDataAsStruct()) {
		LevelDataSaveGameReference->LoadLevelDataFromJson();
	}

	
}
