#pragma once


#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "Variables.h"
#include "SaveGameLevelData.generated.h"


UCLASS()
class LOSTWORLD_API USaveGameLevelData : public USaveGame
{
	GENERATED_BODY()

public:
	// ---------------------------------------- Variables ---------------------------------------- //
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	FLevelDataAsStruct LevelData;
	
	// ---------------------------------------- Functions ---------------------------------------- //
	// Fallback function.
	// Should only be used if the level data JSON cannot be found.
	UFUNCTION(BlueprintCallable)
	void SaveLevelDataToJson();

	UFUNCTION(BlueprintCallable)
	void LoadLevelDataFromJson();
};
