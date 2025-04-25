#pragma once


#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "SaveGameDeveloperSettings.h"
#include "Variables.h"
#include "LostWorldGameInstanceBase.generated.h"


// Forward declarations
class USaveGameDeveloperSettings;


// Local enums/structs
USTRUCT(BlueprintType)
struct LOSTWORLD_API FPlayerSavesAsStruct
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FPlayerSave> SaveObjectsArray;
};


UCLASS()
class LOSTWORLD_API ULostWorldGameInstanceBase : public UGameInstance
{
	GENERATED_BODY()

public:
// ---------------------------------------- Variables ---------------------------------------- //
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	USaveGameDeveloperSettings* DeveloperSettingsSaveGame;

	// To-Do: Make this into an array of Saves.
	// Create one variable for tracking the index of the last loaded object,
	// and one for tracking the index of the last saved object.
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	FPlayerSavesAsStruct AllPlayerSaves;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	FPlayerSave CurrentPlayerSave;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	int LastLoadedPlayerSaveObject;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	int LastSavedPlayerSaveObject;

	// Ongoing To-Do: These two UProperties can be mixed-and-matched.
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UDataTable* CardsDataTable;
	

// ---------------------------------------- Functions ---------------------------------------- //
	virtual void Init() override;
	
	void LoadPlayerSaveJson();
	// This function saves the data from the GameInstance CurrentPlayerSave to the JSON file.
	void SavePlayerDataJson();
	// This function saves the data from the ActorEntityPlayer to the JSON file.
	void SavePlayerActorDataToJson() const;
	
	FString LoadFileFromJson(const FString& FileName) const;
	FCard GetCardFromJson(const FString& CardName) const;
	FEntity GetEntityFromJson(const EEntityTypes& EntityType) const;
	FEnemyEntity GetEnemyFromJson(const EEntityTypes& EnemyType) const;
	FStatusEffect GetStatusEffectFromJson(const EStatusEffectFunctions StatusFunction) const;
	FSummonEntity GetSummonFromJson(const FString& SummonName) const;
	FEncounter GetEncounterFromJson(const FString& EncounterRowName) const;

	// Helper functions,
	static EEntityTypes EntityTypeStringToEnumValue(const FString& InString);
	AActorGridTile* FindGridTileWithVector(FVector InVector) const;
	int GetPlayerRoom() const;
	void GetAllEntityLocations(TArray<FVector>& OutLocations) const;
};
