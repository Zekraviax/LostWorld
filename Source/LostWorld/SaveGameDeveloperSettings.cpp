#include "SaveGameDeveloperSettings.h"


#include "LostWorldGameInstanceBase.h"
#include "Runtime/JsonUtilities/Public/JsonObjectConverter.h"


void USaveGameDeveloperSettings::SaveDeveloperSettingsToJson()
{
	FString SaveGamesFolderPathAppend = "SaveGames/";
	FString SavePath = "C:\\Users\\zekra\\Documents\\UE\\Projects\\Starmark\\Saved\\SaveGames";

	// Get the project's save folder directory.
	SavePath = FPaths::ProjectSavedDir();
	UE_LOG(LogTemp, Warning, TEXT("FilePaths: ProjectSavedDir: %s"), *SavePath);
	SavePath.Append(SaveGamesFolderPathAppend);
	UE_LOG(LogTemp, Warning, TEXT("FilePaths: Developer Settings Data Folder: %s"), *SavePath);

	FString DeveloperSettingsAsJson;
	FJsonObjectConverter::UStructToJsonObjectString(DeveloperSettingsAsStruct, DeveloperSettingsAsJson, 0, 0);

	// Before we save the json file, we need to check if the player's save data folder exists.
	// If it doesn't, we make it first.
	// The directory path should be 'SavePath + DeveloperSettings'.
	IPlatformFile& FileManager = FPlatformFileManager::Get().GetPlatformFile();

	if (!FileManager.DirectoryExists(*SavePath)) {
		if (FileManager.CreateDirectory(*SavePath)) {
			UE_LOG(LogTemp, Warning, TEXT("Developer Settings save data folder did not exist but was created successfully."));
		} else {
			UE_LOG(LogTemp, Warning, TEXT("Developer Settings save data folder does not exist and could not be created."));
		}
	}

	if (FileManager.DirectoryExists(*SavePath)) {
		FString FileName = SavePath.Append("DeveloperSettings.json");
		UE_LOG(LogTemp, Warning, TEXT("FilePaths: Developer Settings save data file name: %s"), *FileName);

		if (FFileHelper::SaveStringToFile(DeveloperSettingsAsJson, *FileName)) {
			UE_LOG(LogTemp, Warning, TEXT("Developer Settings saved successfully."));
		} else {
			UE_LOG(LogTemp, Warning, TEXT("Error: Failed to save Developer Settings."));
		}
	} else {
		UE_LOG(LogTemp, Warning, TEXT("Error: Could not save Developer Settings."));
	}
}


void USaveGameDeveloperSettings::LoadDeveloperSettingsFromJson()
{
	IPlatformFile& FileManager = FPlatformFileManager::Get().GetPlatformFile();
	FString PlayerSaveDataFileName = "SaveGames/DeveloperSettings.json";

	FString PlayerDataSaveFilePath = FPaths::ProjectSavedDir();
	PlayerDataSaveFilePath.Append(PlayerSaveDataFileName);
	UE_LOG(LogTemp, Warning, TEXT("FilePaths: Save Data Folder: %s"), *PlayerDataSaveFilePath);
	
	if (!FileManager.FileExists(*PlayerDataSaveFilePath)) {
		UE_LOG(LogTemp, Warning, TEXT("Error: Could not find Developer Settings. Attempting to create data now."));
		SaveDeveloperSettingsToJson();
	}

	FString PlayerDataAsJson;
	FDeveloperSettingsAsStruct PlayerDataAsStruct;

	FFileHelper::LoadFileToString(PlayerDataAsJson, *PlayerDataSaveFilePath);
	if (FJsonObjectConverter::JsonObjectStringToUStruct(PlayerDataAsJson, &PlayerDataAsStruct, 0, 0)) {
		UE_LOG(LogTemp, Warning, TEXT("Successfully converted DeveloperSettings json to UStruct."));
	} else {
		UE_LOG(LogTemp, Warning, TEXT("Error: Failed to convert DeveloperSettings json to UStruct!"));
	}

	// Apply player data.
	DeveloperSettingsAsStruct = PlayerDataAsStruct;
}


void USaveGameDeveloperSettings::ValidateJson(FString InJsonAsString, FString InDataTableFileName, const FString& InDataTableRowName)
{
	// First, get the json file.
	//FString CardJsonAsString = Cast<ULostWorldGameInstanceBase>(GetWorld()->GetGameInstance())->LoadFileFromJson("CardsData");
	FCard Card = Cast<ULostWorldGameInstanceBase>(GetWorld()->GetGameInstance())->GetCardFromJson(InDataTableRowName);

	// Second, get the data table row.
	FString ContextString;
	TArray<FName> RowNames = Cast<ULostWorldGameInstanceBase>(GetWorld()->GetGameInstance())->CardsDataTable->GetRowNames();
	FCard* Row = Cast<ULostWorldGameInstanceBase>(GetWorld()->GetGameInstance())->CardsDataTable->FindRow<FCard>(
		FName(*InDataTableRowName), ContextString);

	if (Row != &Card) {
		
	}
}
