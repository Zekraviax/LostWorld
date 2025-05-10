#pragma once


#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "GameFramework/SaveGame.h"
#include "SaveGameDeveloperSettings.generated.h"


struct FCard;


USTRUCT(BlueprintType)
struct LOSTWORLD_API FDeveloperSettingsAsStruct : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool EnableDeveloperSettingsOverride;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString PrintMessageOnGameStart;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool GiveAllEntitiesTestDecks;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<int> LogLevels;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString OverrideEncounters; // Leave this blank in order to turn the setting 'off'.

	// If true, then run a 'Json Validation' function whenever a Json file is loaded.
	// If the Json file does not match the corresponding DataTable, then this function should fix that.
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool ValidateAllJson;

	FDeveloperSettingsAsStruct()
	{
		EnableDeveloperSettingsOverride = true;
		PrintMessageOnGameStart = "Developer mode enabled?";
		GiveAllEntitiesTestDecks = false;
		LogLevels = { 0, 1, 2 };
		OverrideEncounters = "";
		ValidateAllJson = false;
	}
};


USTRUCT(BlueprintType)
struct LOSTWORLD_API FCardsArrayWrapper
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FCard> Cards;
};


UCLASS()
class LOSTWORLD_API USaveGameDeveloperSettings : public USaveGame
{
	GENERATED_BODY()

public:
// ---------------------------------------- Variables ---------------------------------------- //
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	FDeveloperSettingsAsStruct DeveloperSettingsAsStruct;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UWorld* WorldReference;

// ---------------------------------------- Functions ---------------------------------------- //
	UFUNCTION(BlueprintCallable)
	void SaveDeveloperSettingsToJson();

	UFUNCTION(BlueprintCallable)
	void LoadDeveloperSettingsFromJson();

	void SaveJsonAsStringToFile(const FString& InFileName, const FString& InJsonAsString) const;

	/** To-Do: Complete this function and test with every DataTable.

	UE DataTables automatically handle UStruct formatting. When DataTables are exported into Json files,
	they also handle the formatting for the file.

	So this function should compare a Json item with the relevant DataTable row. If the Json does not
	match the DataTable row, the Json should be overriden with the DataTable row.*/
	//void ValidateJson(FString InJsonAsString, FString InDataTableFileName, const FString& InDataTableRowName);
	void ValidateAllCardsJson() const;
};