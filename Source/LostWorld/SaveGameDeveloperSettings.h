#pragma once


#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "GameFramework/SaveGame.h"
#include "SaveGameDeveloperSettings.generated.h"


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
	FString OverrideEncounters; // Leave this blank in order to 'turn the setting off'.

	FDeveloperSettingsAsStruct()
	{
		EnableDeveloperSettingsOverride = true;
		PrintMessageOnGameStart = "Developer mode enabled.";
		GiveAllEntitiesTestDecks = false;
		LogLevels = { 0, 1, 2 };
		OverrideEncounters = "";
	}
};


UCLASS()
class LOSTWORLD_API USaveGameDeveloperSettings : public USaveGame
{
	GENERATED_BODY()

public:
// ---------------------------------------- Variables ---------------------------------------- //
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	FDeveloperSettingsAsStruct DeveloperSettingsAsStruct;


// ---------------------------------------- Functions ---------------------------------------- //
	UFUNCTION(BlueprintCallable)
	void SaveDeveloperSettingsToJson();

	UFUNCTION(BlueprintCallable)
	void LoadDeveloperSettingsFromJson();
};