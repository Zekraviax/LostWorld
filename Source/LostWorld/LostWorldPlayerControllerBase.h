#pragma once


#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "Variables.h"
#include "LostWorldPlayerControllerBase.generated.h"


// Forward Declarations
class AActorEntityPlayer;
class UWidgetHudBattle;
class UWidgetHudLevelExploration;


UCLASS()
class LOSTWORLD_API ALostWorldPlayerControllerBase : public APlayerController
{
	GENERATED_BODY()

// ---------------------------------------- Variables ---------------------------------------- //
public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	AActorEntityPlayer* ControlledPlayerEntity;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	EPlayerControlModes ControlMode = EPlayerControlModes::LevelExploration;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<UWidgetHudLevelExploration> LevelHudWidgetBlueprintClass;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UWidgetHudLevelExploration* LevelHudWidget;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<UWidgetHudBattle> BattleHudWidgetBlueprintClass;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UWidgetHudBattle* BattleHudWidget;
	
// ---------------------------------------- Functions ---------------------------------------- //
	void AddBattleHudToViewport();
	void AddLevelHudToViewport();

};
