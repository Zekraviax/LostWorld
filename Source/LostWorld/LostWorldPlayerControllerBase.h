#pragma once


#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "Variables.h"
#include "LostWorldPlayerControllerBase.generated.h"


// Forward Declarations
class AActorEntityPlayer;
class UWidgetDeckEditor;
class UWidgetDevTestMenu;
class UWidgetEquipment;
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
	EPlayerControlModes PreviousControlMode = EPlayerControlModes::LevelExploration;

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

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<UWidgetDeckEditor> DeckEditorWidgetBlueprintClass;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UWidgetDeckEditor* DeckEditorWidget;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<UWidgetEquipment> EquipmentWidgetBlueprintClass;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UWidgetEquipment* EquipmentWidget;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<UWidgetDevTestMenu> DevTestWidgetBlueprintClass;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UWidgetDevTestMenu* DevTestWidget;
	
	
// ---------------------------------------- Functions ---------------------------------------- //

// -------------------------------- Player input
protected:
	virtual void SetupInputComponent() override;

// -------------------------------- Player controls
public:
	void OnLeftMouseButtonClick();
	void SetControlMode(EPlayerControlModes InControlMode);

// -------------------------------- Widgets
	void CloseAllWidgets() const;
	void AddBattleHudToViewport();
	void AddLevelHudToViewport();
	void AddDeckEditorToViewport();
	void AddDevTestMenuToViewport();
	void AddEquipmentToViewport();
};
