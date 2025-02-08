#pragma once


#include "CoreMinimal.h"
#include "SaveGameDeveloperSettings.h"
#include "Engine/GameInstance.h"
#include "Variables.h"
#include "LostWorldGameInstanceBase.generated.h"


// Forward declarations
class USaveGameDeveloperSettings;


UCLASS()
class LOSTWORLD_API ULostWorldGameInstanceBase : public UGameInstance
{
	GENERATED_BODY()

public:
// ---------------------------------------- Variables ---------------------------------------- //
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	USaveGameDeveloperSettings* DeveloperSettingsSaveGame;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	FPlayerSave CurrentPlayerSave;
	

// ---------------------------------------- Functions ---------------------------------------- //
	virtual void Init() override;
	
	void LoadPlayerSaveJson();
	void SavePlayerDataJson() const;
	
	FString LoadFileFromJson(const FString& FileName) const;
	FCard GetCardFromJson(const FString& CardName) const;
	FEnemyEntity GetEnemyFromJson(const FString& EnemyType) const;
	FStatusEffect GetStatusEffectFromJson(const FString& StatusEffectDisplayName) const;
	FSummonEntity GetSummonFromJson(const FString& SummonName) const;
};
