#include "SaveGameLevelData.h"


#include "Runtime/JsonUtilities/Public/JsonObjectConverter.h"
#include "Variables.h"


void USaveGameLevelData::SaveLevelDataToJson()
{
	FLevelDataAsStruct TestLevelData;
	FString SaveGamesFolderPathAppend = "SaveGames/";
	FString SavePath = "C:\\Users\\zekra\\Documents\\UE\\Projects\\Starmark\\Saved\\SaveGames";

	// Get the project's save folder directory.
	SavePath = FPaths::ProjectSavedDir();
	UE_LOG(LogTemp, Warning, TEXT("FilePaths: ProjectSavedDir: %s"), *SavePath);
	SavePath.Append(SaveGamesFolderPathAppend);
	UE_LOG(LogTemp, Warning, TEXT("FilePaths: Level Save Data Folder: %s"), *SavePath);

	FString LevelDataAsJson;
	FJsonObjectConverter::UStructToJsonObjectString(TestLevelData, LevelDataAsJson, 0, 0);

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
		FString FileName = SavePath.Append("TestLevelData.json");
		UE_LOG(LogTemp, Warning, TEXT("FilePaths: Level save data file name: %s"), *FileName);

		if (FFileHelper::SaveStringToFile(LevelDataAsJson, *FileName)) {
			UE_LOG(LogTemp, Warning, TEXT("Level data saves successfully."));
		} else {
			UE_LOG(LogTemp, Error, TEXT("Error: Failed to save Level data."));
		}
	} else {
		UE_LOG(LogTemp, Error, TEXT("Error: Could not save Level data."));
	}
}


void USaveGameLevelData::LoadLevelDataFromJson()
{
	IPlatformFile& FileManager = FPlatformFileManager::Get().GetPlatformFile();
	FString PlayerSaveDataFileName = "SaveGames/TestLevelData.json";

	FString PlayerDataSaveFilePath = FPaths::ProjectSavedDir();
	PlayerDataSaveFilePath.Append(PlayerSaveDataFileName);
	UE_LOG(LogTemp, Warning, TEXT("FilePaths: Save Data Folder: %s"), *PlayerDataSaveFilePath);
	
	if (!FileManager.FileExists(*PlayerDataSaveFilePath)) {
		UE_LOG(LogTemp, Error, TEXT("Error: Could not load data. Attempting to create default data."));

		SaveLevelDataToJson();
	}

	FString PlayerDataAsJson;
	TArray<FLevelDataAsStruct> LevelDataAsStructsArray;
	FLevelDataAsStruct LevelDataAsStruct;

	FFileHelper::LoadFileToString(PlayerDataAsJson, *PlayerDataSaveFilePath);
	FJsonObjectConverter::JsonArrayStringToUStruct(PlayerDataAsJson, &LevelDataAsStructsArray, 0, 0);
	
	// Apply level data.
	// To-Do: Make this function search for a level using a given string
	LevelData = LevelDataAsStructsArray[0];
}