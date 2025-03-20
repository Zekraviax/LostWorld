#pragma once


#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "SaveGameDeveloperSettings.generated.h"


USTRUCT(BlueprintType)
struct LOSTWORLD_API FDeveloperSettingsAsStruct
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool EnableDeveloperSettingsOverride;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString PrintMessageOnGameStart;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool GiveAllEntitiesTestDecks;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int LogLevel = 0;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString OverrideEncounters; // Leave this blank in order to 'turn the setting off'.

	FDeveloperSettingsAsStruct()
	{
		EnableDeveloperSettingsOverride = true;
		PrintMessageOnGameStart = "Developer mode enabled.";
		GiveAllEntitiesTestDecks = false;
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