#include "LostWorldGameInstanceBase.h"


#include "ActorEntityPlayer.h"
#include "ActorGridTile.h"
#include "JsonObjectConverter.h"
#include "Kismet/GameplayStatics.h"
#include "LostWorldGameModeBase.h"
#include "LostWorldPlayerControllerBattle.h"
#include "SaveGameDeveloperSettings.h"


void ULostWorldGameInstanceBase::Init()
{
	Super::Init();

	// The developer settings JSON file will always be loaded.
	// But there will be a flag within the JSON file to enable/disable developer settings.
	// If the JSON cannot be found, the file will be created but default settings will be used for the session.
	DeveloperSettingsSaveGame = Cast<USaveGameDeveloperSettings>(
		UGameplayStatics::CreateSaveGameObject(USaveGameDeveloperSettings::StaticClass()));
	
	DeveloperSettingsSaveGame->LoadDeveloperSettingsFromJson();
	DeveloperSettingsSaveGame->WorldReference = GetWorld();

	// 'Print message on game start' developer setting.
	if (DeveloperSettingsSaveGame->DeveloperSettingsAsStruct.EnableDeveloperSettingsOverride) {
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, DeveloperSettingsSaveGame->
			DeveloperSettingsAsStruct.PrintMessageOnGameStart);
	}

	// Temporary code:
	// Automatically lode the players' save data.
	LoadPlayerSaveJson();
}


void ULostWorldGameInstanceBase::LoadPlayerSaveJson()
{
	FString PlayerDataAsJson = LoadFileFromJson("PlayerSaveData");
	FPlayerSave PlayerDataSingle;
	TArray<FPlayerSave> PlayerDataArray;

	if (FJsonObjectConverter::JsonArrayStringToUStruct(PlayerDataAsJson, &PlayerDataArray, 0, 0)) {
		UE_LOG(LogTemp, Warning, TEXT("Successfully loaded PlayerData as JsonArrayString."));
		CurrentPlayerSave = PlayerDataArray[0];
	} else if (FJsonObjectConverter::JsonObjectStringToUStruct(PlayerDataAsJson, &PlayerDataSingle, 0, 0)) {
		UE_LOG(LogTemp, Warning, TEXT("Successfully loaded PlayerData as singular JsonObjectString."));
		CurrentPlayerSave = PlayerDataSingle;
	}
}


void ULostWorldGameInstanceBase::SavePlayerDataJson()
{
	// Insert the current player save data into the save objects array at the last loaded index,
	// then save the whole array.
	if (AllPlayerSaves.SaveObjectsArray.Num() > LastLoadedPlayerSaveObject) {
		AllPlayerSaves.SaveObjectsArray[LastLoadedPlayerSaveObject] = CurrentPlayerSave;
	} else {
		AllPlayerSaves.SaveObjectsArray.Add(CurrentPlayerSave);
		LastSavedPlayerSaveObject = AllPlayerSaves.SaveObjectsArray.Num() - 1;
	}
	
	
	FString SaveGamesFolderPathAppend = "SaveGames/";
	FString SavePath = "C:\\Users\\zekra\\Documents\\UE\\Projects\\Starmark\\Saved\\SaveGames";

	// Get the project's save folder directory.
	SavePath = FPaths::ProjectSavedDir();
	UE_LOG(LogTemp, Warning, TEXT("FilePaths: ProjectSavedDir: %s"), *SavePath);
	SavePath.Append(SaveGamesFolderPathAppend);
	UE_LOG(LogTemp, Warning, TEXT("FilePaths: Player Save Data Folder: %s"), *SavePath);

	// To-Do: More testing on saving and loading arrays of player data.
	FString PlayerDataAsJson;
	FJsonObjectConverter::UStructToJsonObjectString(AllPlayerSaves.SaveObjectsArray[LastLoadedPlayerSaveObject],
		PlayerDataAsJson, 0, 0);
	
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
		FString FileName = SavePath.Append("PlayerSaveData.json");
		UE_LOG(LogTemp, Warning, TEXT("FilePaths: Player save data file name: %s"), *FileName);

		if (FFileHelper::SaveStringToFile(PlayerDataAsJson, *FileName)) {
			UE_LOG(LogTemp, Warning, TEXT("Player data saved successfully."));
		} else {
			UE_LOG(LogTemp, Error, TEXT("Error: Failed to save Player data."));
		}
	} else {
		UE_LOG(LogTemp, Error, TEXT("Error: Could not save Player data."));
	}
}


void ULostWorldGameInstanceBase::SavePlayerActorDataToJson() const
{
	FString SaveGamesFolderPathAppend = "SaveGames/";
	FString SavePath = "C:\\Users\\zekra\\Documents\\UE\\Projects\\Starmark\\Saved\\SaveGames";

	// Get the project's save folder directory.
	SavePath = FPaths::ProjectSavedDir();
	UE_LOG(LogTemp, Warning, TEXT("FilePaths: ProjectSavedDir: %s"), *SavePath);
	SavePath.Append(SaveGamesFolderPathAppend);
	UE_LOG(LogTemp, Warning, TEXT("FilePaths: Player Save Data Folder: %s"), *SavePath);

	FString PlayerDataAsJson;
	FJsonObjectConverter::UStructToJsonObjectString(
		Cast<ALostWorldPlayerControllerBattle>(GetWorld()->GetFirstPlayerController())->ControlledPlayerEntity->EntityData, PlayerDataAsJson, 0, 0);

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
		FString FileName = SavePath.Append("PlayerSaveData.json");
		UE_LOG(LogTemp, Warning, TEXT("FilePaths: Player save data file name: %s"), *FileName);

		if (FFileHelper::SaveStringToFile(PlayerDataAsJson, *FileName)) {
			UE_LOG(LogTemp, Warning, TEXT("Player data saved successfully."));
		} else {
			UE_LOG(LogTemp, Error, TEXT("Error: Failed to save Player data."));
		}
	} else {
		UE_LOG(LogTemp, Error, TEXT("Error: Could not save Player data."));
	}
}


FString ULostWorldGameInstanceBase::LoadFileFromJson(const FString& FileName) const
{
	FString SaveGamesFilePathAndName = "SaveGames/" + FileName + ".json";
	FString PlayerDataSaveFilePath = FPaths::ProjectSavedDir();
	FString JsonFileAsString;
	
	PlayerDataSaveFilePath.Append(SaveGamesFilePathAndName);
	UE_LOG(LogTemp, Warning, TEXT("File Path: %s"), *PlayerDataSaveFilePath);

	// Ongoing To-Do: Don't use DualLog when loading JSON files because the DeveloperSettings might not be loaded yet.
	if (!FFileHelper::LoadFileToString(JsonFileAsString, *PlayerDataSaveFilePath)) {
		UE_LOG(LogTemp, Warning, TEXT("Error: Failed to load file: %s"), *PlayerDataSaveFilePath);
	} else {
		UE_LOG(LogTemp, Warning, TEXT("Successfully loaded file: : %s"), *PlayerDataSaveFilePath);
	}

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


FEntity ULostWorldGameInstanceBase::GetEntityFromJson(const EEntityTypes& EntityType) const
{
	TArray<FEntity> EntitiesArray;
	FString EntityJsonAsString = LoadFileFromJson("EntitiesData");
	FJsonObjectConverter::JsonArrayStringToUStruct(EntityJsonAsString, &EntitiesArray, 0, 0);

	for (FEntity Entity : EntitiesArray) {
		if (Entity.EntityTypes.Contains(EntityType)) {
			return Entity;
		}
	}

	ALostWorldGameModeBase::DualLog("Error! Could not find entity data with type: "
		+ UEnum::GetDisplayValueAsText(EntityType).ToString(), 2);
	return EntitiesArray[0];
}


FEnemyEntity ULostWorldGameInstanceBase::GetEnemyFromJson(const EEntityTypes& EnemyType) const
{
	TArray<FEnemyEntity> EnemiesArray;
	FString EnemyJsonAsString = LoadFileFromJson("EnemiesData");
	FJsonObjectConverter::JsonArrayStringToUStruct(EnemyJsonAsString, &EnemiesArray, 0, 0);

	for (FEnemyEntity Enemy : EnemiesArray) {
		if (Enemy.EnemyType == EnemyType) {
			return Enemy;
		}
	}

	ALostWorldGameModeBase::DualLog("Error! Could not find enemy data with type: "
		+ UEnum::GetDisplayValueAsText(EnemyType).ToString(), 2);
	return EnemiesArray[0];
}


FStatusEffect ULostWorldGameInstanceBase::GetStatusEffectFromJson(const EStatusEffectFunctions StatusFunction) const
{
	TArray<FStatusEffect> StatusEffectsArray;
	FString StatusEffectJsonAsString = LoadFileFromJson("StatusEffectsData");
	FJsonObjectConverter::JsonArrayStringToUStruct(StatusEffectJsonAsString, &StatusEffectsArray, 0, 0);

	for (FStatusEffect StatusEffect : StatusEffectsArray) {
		if (StatusEffect.StatusEffect == StatusFunction) {
			return StatusEffect;
		}
	}

	ALostWorldGameModeBase::DualLog("Error! Did not find status effect with function: " +
		UEnum::GetDisplayValueAsText(StatusFunction).ToString(), 2);
	return StatusEffectsArray[0];
}


FSummonEntity ULostWorldGameInstanceBase::GetSummonFromJson(const FString& SummonName) const
{
	TArray<FSummonEntity> SummonsArray;
	FString SummonJsonAsString = LoadFileFromJson("SummonsData");
	FJsonObjectConverter::JsonArrayStringToUStruct(SummonJsonAsString, &SummonsArray, 0, 0);

	for (FSummonEntity Summon : SummonsArray) {
		if (Summon.EntityData.DisplayName.Equals(SummonName)) {
			return Summon;
		}
	}

	return SummonsArray[0];
}


FEncounter ULostWorldGameInstanceBase::GetEncounterFromJson(const FString& EncounterRowName) const
{
	TArray<FEncounter> EncountersArray;
	FString EncounterJsonAsString = LoadFileFromJson("EncounterData");

	//for () {}
	return FEncounter();
}


EEntityTypes ULostWorldGameInstanceBase::EntityTypeStringToEnumValue(const FString& InString)
{
	const UEnum* EntityTypeEnum = FindObject<UEnum>(ANY_PACKAGE, TEXT("EEntityTypes"), true);
	int32 Index = EntityTypeEnum->GetIndexByNameString(InString);

	EEntityTypes ReturnType = static_cast<EEntityTypes>((Index));
	return ReturnType;
}


AActorGridTile* ULostWorldGameInstanceBase::FindGridTileWithVector(FVector InVector) const
{
	TArray<AActor*> FoundGridTiles;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AActorGridTile::StaticClass(), FoundGridTiles);

	for (auto& Tile : FoundGridTiles) {
		if (Tile->GetActorLocation() == InVector && Cast<AActorGridTile>(Tile)) {
			return Cast<AActorGridTile>(Tile);
		}
	}

	ALostWorldGameModeBase::DualLog("Warning! FindGridTileWithVector failed to find a grid tile!", 2);
	return nullptr;
}


int ULostWorldGameInstanceBase::GetPlayerRoom() const
{
	TArray<AActor*> FoundGridTiles, FoundPlayers;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AActorGridTile::StaticClass(), FoundGridTiles);
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AActorEntityPlayer::StaticClass(), FoundPlayers);
	
	AActorEntityPlayer* Player = Cast<AActorEntityPlayer>(FoundPlayers[0]);
	FVector PlayerLocation = Player->GetActorLocation();
	
	for (AActor* GridTile : FoundGridTiles) {
		if (GridTile->GetActorLocation().X == PlayerLocation.X && GridTile->GetActorLocation().Y == PlayerLocation.Y) {
			return Cast<AActorGridTile>(GridTile)->RoomIndex;
		}
	}
	
	return -1;
}


void ULostWorldGameInstanceBase::GetAllEntityLocations(TArray<FVector>& OutLocations) const
{
	TArray<AActor*> FoundActors, FoundGridTiles;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AActorEntityBase::StaticClass(), FoundActors);
	
	for (auto& Actor : FoundActors) {
		OutLocations.Add(Actor->GetActorLocation());
	}
}
