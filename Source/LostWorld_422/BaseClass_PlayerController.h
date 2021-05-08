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

// ------------------------- Entity
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FEntityBase CurrentEntityData;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FCardBase> CurrentCollection;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	ABaseClass_GridTile* CurrentLocationInLevel;

// ------------------------- Technical Variables
	// Player EntityInBattle class
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class ABaseClass_EntityInBattle* EntityInBattleRef;

	// Player EntityInBattle instance
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<ABaseClass_EntityInBattle> EntityInBattle_Class;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	ABaseClass_LevelRoom* CurrentRoom;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UDataTable* CardsTable;

// ------------------------- Widgets
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class UBaseClass_HUD_Level* Level_HUD_Widget;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSubclassOf<class UBaseClass_HUD_Level> Level_HUD_Class;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class UBaseClass_HUD_Battle* Battle_HUD_Widget;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSubclassOf<class UBaseClass_HUD_Battle> Battle_HUD_Class;

	// The instance of the DeckBuilderCard 
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UBaseClass_CardUserWidget* Card_Widget;

	// The class that will be used for the DeckBuilderCard
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<UBaseClass_CardUserWidget> Card_Class;

	// Dragging Card Widget Reference
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UBaseClass_CardUserWidget* CurrentDragCardRef;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<UBaseClass_Widget_SpentMana> SpendManaWidget_Class;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		UBaseClass_Widget_SpentMana* SpendManaWidget_Reference;

// Functions
// --------------------------------------------------
	UFUNCTION()
	void ManualBeginPlay();

// ------------------------- Controls
	UFUNCTION(BlueprintCallable)
	void CustomOnLeftMouseButtonUpEvent();

	UFUNCTION()
	void PlayerMoveNorth();

	UFUNCTION()
	void PlayerMoveEast();

	UFUNCTION()
	void PlayerMoveSouth();

	UFUNCTION()
	void PlayerMoveWest();

// ------------------------- Gameplay
	UFUNCTION(BlueprintCallable)
	void BeginBattle();

	UFUNCTION(BlueprintCallable)
	void ExitBattle();

	UFUNCTION()
	void MoveToTile(ABaseClass_GridTile* TileReference);
};