#pragma once


#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
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


// ---------------------------------------- Functions ---------------------------------------- //
	virtual void Init() override;
};
