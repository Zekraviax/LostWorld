#include "LostWorldGameInstanceBase.h"


#include "ActorEntityPlayer.h"
#include "JsonObjectConverter.h"
#include "Kismet/GameplayStatics.h"
#include "LostWorldPlayerControllerBattle.h"
#include "SaveGameDeveloperSettings.h"


void ULostWorldGameInstanceBase::Init()
{
	Super::Init();

	// The developer settings JSON file will always be loaded.
	// But there will be a flag within the JSON file to enable/disable developer settings.
	// If the JSON cannot be found, the file will be created but default settings will be used for the session.
	DeveloperSettingsSaveGame = Cast<USaveGameDeveloperSettings>(UGameplayStatics::CreateSaveGameObject(USaveGameDeveloperSettings::StaticClass()));
	DeveloperSettingsSaveGame->LoadDeveloperSettingsFromJson();

	if (DeveloperSettingsSaveGame->DeveloperSettingsAsStruct.EnableDeveloperSettingsOverride) {
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, DeveloperSettingsSaveGame->DeveloperSettingsAsStruct.PrintMessageOnGameStart);
	}

	// Temporary code:
	// Automatically lode the players' save data.
	LoadPlayerSaveJson();
}


void ULostWorldGameInstanceBase::LoadPlayerSaveJson()
{
	FString PlayerDataAsJson = LoadFileFromJson("PlayerSaveData");
	FPlayerSave PlayerDataSingle;
	TArray<FPlayerSave> PlayerDataArray;

	if (FJsonObjectConverter::JsonArrayStringToUStruct(PlayerDataAsJson, &PlayerDataArray, 0, 0)) {
		CurrentPlayerSave = PlayerDataArray[0];
	} else if (FJsonObjectConverter::JsonObjectStringToUStruct(PlayerDataAsJson, &PlayerDataSingle, 0, 0)) {
		CurrentPlayerSave = PlayerDataSingle;
	}
}


void ULostWorldGameInstanceBase::SavePlayerDataJson()
{
	// Insert the current player save data into the save objects array at the last loaded index,
	// then save the whole array.
	AllPlayerSaves.SaveObjectsArray[LastLoadedPlayerSaveObject] = CurrentPlayerSave;
	
	FString SaveGamesFolderPathAppend = "SaveGames/";
	FString SavePath = "C:\\Users\\zekra\\Documents\\UE\\Projects\\Starmark\\Saved\\SaveGames";

	// Get the project's save folder directory.
	SavePath = FPaths::ProjectSavedDir();
	UE_LOG(LogTemp, Warning, TEXT("FilePaths: ProjectSavedDir: %s"), *SavePath);
	SavePath.Append(SaveGamesFolderPathAppend);
	UE_LOG(LogTemp, Warning, TEXT("FilePaths: Player Save Data Folder: %s"), *SavePath);

	FString PlayerDataAsJson;
	FJsonObjectConverter::UStructToJsonObjectString(AllPlayerSaves, PlayerDataAsJson, 0, 0);
	
	// Before we save the json file, we need to check if the player's save data folder exists.
	// If it doesn't, we make it first.
	// The directory path should be 'SavePath + DeveloperSettings'.
	IPlatformFile& FileManager = FPlatformFileManager::Get().GetPlatformFile();

	if (!FileManager.DirectoryExists(*SavePath)) {
		if (FileManager.CreateDirectory(*SavePath)) {
			UE_LOG(LogTemp, Warning, TEXT("Save data folder did not exist but was created successfully."));
		} else {
			UE_LOG(LogTemp, Error, TEXT("Save data folder does not exist and could not be created."));
		}
	}

	if (FileManager.DirectoryExists(*SavePath)) {
		FString FileName = SavePath.Append("PlayerSaveData.json");
		UE_LOG(LogTemp, Warning, TEXT("FilePaths: Player save data file name: %s"), *FileName);

		if (FFileHelper::SaveStringToFile(PlayerDataAsJson, *FileName)) {
			UE_LOG(LogTemp, Warning, TEXT("Player data saves successfully."));
		} else {
			UE_LOG(LogTemp, Error, TEXT("Error: Failed to save Player data."));
		}
	} else {
		UE_LOG(LogTemp, Error, TEXT("Error: Could not save Player data."));
	}
}


void ULostWorldGameInstanceBase::SavePlayerActorDataToJson() const
{
	FString SaveGamesFolderPathAppend = "SaveGames/";
	FString SavePath = "C:\\Users\\zekra\\Documents\\UE\\Projects\\Starmark\\Saved\\SaveGames";

	// Get the project's save folder directory.
	SavePath = FPaths::ProjectSavedDir();
	UE_LOG(LogTemp, Warning, TEXT("FilePaths: ProjectSavedDir: %s"), *SavePath);
	SavePath.Append(SaveGamesFolderPathAppend);
	UE_LOG(LogTemp, Warning, TEXT("FilePaths: Player Save Data Folder: %s"), *SavePath);

	FString PlayerDataAsJson;
	FJsonObjectConverter::UStructToJsonObjectString(
		Cast<ALostWorldPlayerControllerBattle>(GetWorld()->GetFirstPlayerController())->ControlledPlayerEntity->EntityData, PlayerDataAsJson, 0, 0);

	// Before we save the json file, we need to check if the player's save data folder exists.
	// If it doesn't, we make it first.
	// The directory path should be 'SavePath + DeveloperSettings'.
	IPlatformFile& FileManager = FPlatformFileManager::Get().GetPlatformFile();

	if (!FileManager.DirectoryExists(*SavePath)) {
		if (FileManager.CreateDirectory(*SavePath)) {
			UE_LOG(LogTemp, Warning, TEXT("Save data folder did not exist but was created successfully."));
		} else {
			UE_LOG(LogTemp, Error, TEXT("Save data folder does not exist and could not be created."));
		}
	}

	if (FileManager.DirectoryExists(*SavePath)) {
		FString FileName = SavePath.Append("PlayerSaveData.json");
		UE_LOG(LogTemp, Warning, TEXT("FilePaths: Player save data file name: %s"), *FileName);

		if (FFileHelper::SaveStringToFile(PlayerDataAsJson, *FileName)) {
			UE_LOG(LogTemp, Warning, TEXT("Player data saves successfully."));
		} else {
			UE_LOG(LogTemp, Error, TEXT("Error: Failed to save Player data."));
		}
	} else {
		UE_LOG(LogTemp, Error, TEXT("Error: Could not save Player data."));
	}
}


FString ULostWorldGameInstanceBase::LoadFileFromJson(const FString& FileName) const
{
	FString SaveGamesFilePathAndName = "SaveGames/" + FileName + ".json";
	FString PlayerDataSaveFilePath = FPaths::ProjectSavedDir();
	
	PlayerDataSaveFilePath.Append(SaveGamesFilePathAndName);
	UE_LOG(LogTemp, Warning, TEXT("File Path: %s"), *PlayerDataSaveFilePath);

	FString JsonFileAsString;
	FFileHelper::LoadFileToString(JsonFileAsString, *PlayerDataSaveFilePath);

	return JsonFileAsString;
}


FCard ULostWorldGameInstanceBase::GetCardFromJson(const FString& CardName) const
{
	TArray<FCard> CardsArray;
	FString CardJsonAsString = LoadFileFromJson("CardsData");
	FJsonObjectConverter::JsonArrayStringToUStruct(CardJsonAsString, &CardsArray, 0, 0);

	for (FCard Card : CardsArray) {
		if (Card.DisplayName.Equals(CardName)) {
			return Card;
		}
	}

	return CardsArray[0];
}


FEnemyEntity ULostWorldGameInstanceBase::GetEnemyFromJson(const FString& EnemyType) const
{
	TArray<FEnemyEntity> EnemiesArray;
	FString EnemyJsonAsString = LoadFileFromJson("EnemiesData");
	FJsonObjectConverter::JsonArrayStringToUStruct(EnemyJsonAsString, &EnemiesArray, 0, 0);

	for (FEnemyEntity Enemy : EnemiesArray) {
		if (Enemy.EnemyType.Equals(EnemyType)) {
			return Enemy;
		}
	}

	return EnemiesArray[0];
}


FStatusEffect ULostWorldGameInstanceBase::GetStatusEffectFromJson(const FString& StatusEffectDisplayName) const
{
	TArray<FStatusEffect> StatusEffectsArray;
	FString StatusEffectJsonAsString = LoadFileFromJson("StatusEffectsData");
	FJsonObjectConverter::JsonArrayStringToUStruct(StatusEffectJsonAsString, &StatusEffectsArray, 0, 0);

	for (FStatusEffect StatusEffect : StatusEffectsArray) {
		if (StatusEffect.DisplayName.Equals(StatusEffectDisplayName)) {
			return StatusEffect;
		}
	}

	return StatusEffectsArray[0];
}


FSummonEntity ULostWorldGameInstanceBase::GetSummonFromJson(const FString& SummonName) const
{
	TArray<FSummonEntity> SummonsArray;
	FString SummonJsonAsString = LoadFileFromJson("SummonsData");
	FJsonObjectConverter::JsonArrayStringToUStruct(SummonJsonAsString, &SummonsArray, 0, 0);

	for (FSummonEntity Summon : SummonsArray) {
		if (Summon.EntityData.DisplayName.Equals(SummonName)) {
			return Summon;
		}
	}

	return SummonsArray[0];
}
