#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"

#include "LostWorld_422GameModeBase.h"
#include "BaseClass_HUD_Battle.h"
#include "BaseClass_HUD_Level.h"
#include "BaseClass_EntityInBattle.h"
#include "BaseClass_CardUserWidget.h"
#include "BaseClass_LevelRoom.h"
#include "BaseClass_Widget_SpentMana.h"

#include "BaseClass_PlayerController.generated.h"


// Forward Declarations
class ABaseClass_GridTile;
class UWidget_CustomConsole_Base;


// Class-Specific Enums
UENUM(BlueprintType)
enum class E_Player_ControlMode: uint8
{
	E_Move,
	E_Battle,
	E_None,
};


UCLASS()
class LOSTWORLD_422_API ABaseClass_PlayerController : public APlayerController
{
	GENERATED_BODY()

protected:
	virtual void SetupInputComponent() override;

	// BeginPlay function
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

// Base Variables
// --------------------------------------------------

// ------------------------- Player
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	E_Player_ControlMode ControlMode;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int CurrentExperiencePoints;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TArray<F_Item_Base> PlayerInventory;

// ------------------------- Entity
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FEntityBase CurrentEntityData;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FCard> CurrentCollection;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	ABaseClass_GridTile* CurrentLocationInLevel;

// ------------------------- Technical Variables
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	ABaseClass_EntityInBattle* EntityInBattleRef;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<ABaseClass_EntityInBattle> EntityInBattle_Class;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	ABaseClass_LevelRoom* CurrentRoom;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UDataTable* CardsTable;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UDataTable* ItemsTable;

// ------------------------- Widgets
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UBaseClass_HUD_Level* Level_HUD_Widget;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSubclassOf<UBaseClass_HUD_Level> Level_HUD_Class;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UBaseClass_HUD_Battle* Battle_HUD_Widget;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSubclassOf<UBaseClass_HUD_Battle> Battle_HUD_Class;

	// The instance of the DeckBuilderCard 
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UBaseClass_CardUserWidget* Card_Widget;

	// The class that will be used for the DeckBuilderCard
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<UBaseClass_CardUserWidget> Card_Class;

	// Dragging Card Widget Reference
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UBaseClass_CardUserWidget* CurrentDragCardRef;

	// Custom Console
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<UWidget_CustomConsole_Base> CustomConsole_Class;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UWidget_CustomConsole_Base* CustomConsole_Reference;

// Functions
// --------------------------------------------------
	void ManualBeginPlay();

// ------------------------- Controls
	UFUNCTION(BlueprintCallable)
	void CustomOnLeftMouseButtonUpEvent();
	
	void PlayerMoveNorth();
	void PlayerMoveEast();
	void PlayerMoveSouth();
	void PlayerMoveWest();

// ------------------------- Gameplay
	UFUNCTION(BlueprintCallable)
	void BeginBattle();

	UFUNCTION(BlueprintCallable)
	void ExitBattle();

	void MoveToTile(ABaseClass_GridTile* TileReference);
	bool ValidDeckCheck();
};