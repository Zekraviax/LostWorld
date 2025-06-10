#include "SaveGameDeveloperSettings.h"


#include "CustomJsonParser.h"
#include "LostWorldGameInstanceBase.h"
#include "LostWorldGameModeBase.h"
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
		UE_LOG(LogTemp, Error, TEXT("Error: Could not find Developer Settings. Attempting to create data now."));
		SaveDeveloperSettingsToJson();
	}

	FString PlayerDataAsJson;
	TArray<FDeveloperSettingsAsStruct> PlayerDataAsStructArray;

	FFileHelper::LoadFileToString(PlayerDataAsJson, *PlayerDataSaveFilePath);
	if (FJsonObjectConverter::JsonArrayStringToUStruct(PlayerDataAsJson, &PlayerDataAsStructArray, 0, 0)) {
		UE_LOG(LogTemp, Warning, TEXT("Successfully converted DeveloperSettings json to UStruct."));
	} else {
		UE_LOG(LogTemp, Error, TEXT("Error: Failed to convert DeveloperSettings json to UStruct!"));
	}

	// Apply developer settings.
	DeveloperSettingsAsStruct = PlayerDataAsStructArray[0];
}


/*void USaveGameDeveloperSettings::ValidateJson(FString InJsonAsString, FString InDataTableFileName, const FString& InDataTableRowName)
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
}*/


void USaveGameDeveloperSettings::SaveJsonAsStringToFile(const FString& InFileName, const FString& InJsonAsString) const
{
	FString SaveGamesFolderPathAppend = "SaveGames/";
	FString SavePath = "C:\\Users\\zekra\\Documents\\UE\\Projects\\Starmark\\Saved\\SaveGames";

	// Get the project's save folder directory.
	SavePath = FPaths::ProjectSavedDir();
	UE_LOG(LogTemp, Warning, TEXT("FilePaths: ProjectSavedDir: %s"), *SavePath);
	SavePath.Append(SaveGamesFolderPathAppend);
	UE_LOG(LogTemp, Warning, TEXT("FilePaths: Developer Settings Data Folder: %s"), *SavePath);

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
		FString FileName = SavePath.Append(InFileName + ".json");
		UE_LOG(LogTemp, Warning, TEXT("FilePaths: Developer Settings save data file name: %s"), *FileName);

		if (FFileHelper::SaveStringToFile(InJsonAsString, *FileName)) {
			UE_LOG(LogTemp, Warning, TEXT("Developer Settings saved successfully."));
		} else {
			UE_LOG(LogTemp, Warning, TEXT("Error: Failed to save Developer Settings."));
		}
	} else {
		UE_LOG(LogTemp, Warning, TEXT("Error: Could not save Developer Settings."));
	}
}


void USaveGameDeveloperSettings::ValidateAllCardsJson() const
{
	// Search through each and every Json file for each and every instance of a Card.
	// First file: CardsData.json
	bool ValidationPartOneSuccessful = true;
	bool OverrideCurrentJsonFile = false;
	TArray<FCard> JsonCardsArray, DataTableCardsArray;
	const FString CardsJsonAsString = Cast<ULostWorldGameInstanceBase>(WorldReference->GetGameInstance())->LoadFileFromJson("CardsData");
	TArray<FName> RowNames = Cast<ULostWorldGameInstanceBase>(WorldReference->GetGameInstance())->CardsDataTable->GetRowNames();

	// Validation part 1: Ensure that the file can be loaded and parsed into unreal engine data formats.
	for (FName RowName : RowNames) {
		FString ContextString;
		DataTableCardsArray.Add(*Cast<ULostWorldGameInstanceBase>(WorldReference->GetGameInstance())->CardsDataTable->
			FindRow<FCard>(FName(RowName), ContextString));
	}
	
	if (FJsonObjectConverter::JsonArrayStringToUStruct(CardsJsonAsString, &JsonCardsArray, 0, 0)) {
		ValidationPartOneSuccessful = true;
		ALostWorldGameModeBase::DualLog("CardsData.json file validation part 1 was successful. No action necessary.", 2);
	} else {
		ValidationPartOneSuccessful = false;
		ALostWorldGameModeBase::DualLog("CardsData.json file failed validation part 1.\nCards data must be fixed.", 2);
	}

	// Validation part 2: Compare the data from the json file and the data from the data table.
	if (!ValidationPartOneSuccessful)
	{
		for (int Index = 0; Index < JsonCardsArray.Num(); Index++) {
			if (JsonCardsArray[Index] == DataTableCardsArray[Index]) {
				// To-Do: Make a viable != operator for FCards.
			} else {
				// One time check to set a flag to overwrite the Json file.
				if (!OverrideCurrentJsonFile) {
					OverrideCurrentJsonFile = true;

					// In the FCards array, override the incorrect data with the correct DataTable row.
					JsonCardsArray[Index] = DataTableCardsArray[Index];
					ALostWorldGameModeBase::DualLog("Card " + DataTableCardsArray[Index].DisplayName + " failed validation part 2.", 2);
					ALostWorldGameModeBase::DualLog("CardsData.json requires overwriting.", 2);
				}
			}
		}

		// Validation part 3: Overwrite the json file if necessary.
		// The FCards array should have been overriden with the correct data by this point.
		if (OverrideCurrentJsonFile) {
			// Since this is only a developer tool, we're going to do minimal defensive coding here.
			FString OutJsonAsString;

			// UStruct wrapper for an array of FCards.
			FCardsArrayWrapper CardsArrayWrapper;
			CardsArrayWrapper.Cards = DataTableCardsArray;
			
			CustomJsonParser* JsonSerializer = new CustomJsonParser();
			JsonSerializer->BeginCreationOfStructuredJsonString(JsonCardsArray, RowNames, OutJsonAsString);

			// To-Do: Move the following line to the end of the function.
			JsonSerializer = nullptr;
			SaveJsonAsStringToFile("CardsData", OutJsonAsString);
		}
	}

	// Validation part 4: Repeat parts 1, 2, and 3 for all other instances of a Card in all other Json files.
	// We process the files in alphabetical order.
	ValidationPartOneSuccessful = true;
	OverrideCurrentJsonFile = false;
	TArray<FEntity> JsonEntitiesArray;
	const FString EntitiesJsonAsString = Cast<ULostWorldGameInstanceBase>(WorldReference->GetGameInstance())->LoadFileFromJson("EntitiesData");
	if (FJsonObjectConverter::JsonArrayStringToUStruct(EntitiesJsonAsString, &JsonEntitiesArray, 0, 0)) {
		ALostWorldGameModeBase::DualLog("EntitiesData.json file validation part 1 was successful. No action necessary.", 2);
	} else {
		ALostWorldGameModeBase::DualLog("EntitiesData.json file failed validation part 1.\nEnemies data must be fixed.", 2);
	}

	for (int EntityIndex = 0; EntityIndex < JsonEntitiesArray.Num(); EntityIndex++) {
		for (int DeckIndex = 0; DeckIndex < JsonEntitiesArray[EntityIndex].Deck.Num(); DeckIndex++) {
			
		}
	}
}