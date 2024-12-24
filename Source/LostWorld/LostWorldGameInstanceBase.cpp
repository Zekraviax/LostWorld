#include "LostWorldGameInstanceBase.h"


#include "JsonObjectConverter.h"
#include "Kismet/GameplayStatics.h"
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
	// Automatically lode the players' save data
	LoadPlayerSaveJson();
}


void ULostWorldGameInstanceBase::LoadPlayerSaveJson()
{
	FString PlayerDataAsJson = LoadFileFromJson("PlayerSaveData");
	FPlayerSave PlayerDataAsStruct;
	FJsonObjectConverter::JsonObjectStringToUStruct(PlayerDataAsJson, &PlayerDataAsStruct, 0, 0);
	
	// Apply player data
	CurrentPlayerSave = PlayerDataAsStruct;
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