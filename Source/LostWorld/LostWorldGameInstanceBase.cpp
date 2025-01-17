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
	FString PlayerDataAsString = LoadFileFromJson("PlayerSaveData");
	TArray<FPlayerSave> PlayerDataArray;
	FJsonObjectConverter::JsonArrayStringToUStruct(PlayerDataAsString, &PlayerDataArray, 0, 0);
	
	// Apply player data
	CurrentPlayerSave = PlayerDataArray[0];
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
