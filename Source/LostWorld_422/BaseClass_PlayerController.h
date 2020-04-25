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


UCLASS()
class LOSTWORLD_422_API ABaseClass_PlayerController : public APlayerController
{
	GENERATED_BODY()

protected:
	virtual void SetupInputComponent() override;

	// BeginPlay function
	virtual void BeginPlay() override;

	ABaseClass_PlayerController();

public:
	virtual void Tick(float DeltaTime) override;

// Base Variables
// --------------------------------------------------

// ------------------------- Entity
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Entity")
	FEntityBase CurrentEntityData;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Entity")
	TArray<FCardBase> CurrentCollection;

// ------------------------- Technical Variables
	// Player EntityInBattle class
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Technical")
	class ABaseClass_EntityInBattle* EntityInBattleRef;

	// Player EntityInBattle instance
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Technical")
	TSubclassOf<ABaseClass_EntityInBattle> EntityInBattle_Class;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Technical")
	ABaseClass_LevelRoom* CurrentRoom;

// ------------------------- Widgets
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Widgets")
	class UBaseClass_HUD_Level* Level_HUD_Widget;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Widgets")
	TSubclassOf<class UBaseClass_HUD_Level> Level_HUD_Class;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Widgets")
	class UBaseClass_HUD_Battle* Battle_HUD_Widget;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Widgets")
	TSubclassOf<class UBaseClass_HUD_Battle> Battle_HUD_Class;

	// The instance of the DeckBuilderCard 
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Widgets")
	UBaseClass_CardUserWidget* Card_Widget;

	// The class that will be used for the DeckBuilderCard
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widgets")
	TSubclassOf<UBaseClass_CardUserWidget> Card_Class;

	// Dragging Card Widget Reference
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Widgets")
	UBaseClass_CardUserWidget* CurrentDragCardRef;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widgets")
	TSubclassOf<UBaseClass_Widget_SpentMana> SpendManaWidget_Class;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Widgets")
	UBaseClass_Widget_SpentMana* SpendManaWidget_Reference;

// Functions
// --------------------------------------------------

// ------------------------- Mouse
	UFUNCTION(BlueprintCallable)
	void CustomOnLeftMouseButtonUpEvent();

// ------------------------- Gameplay
	UFUNCTION(BlueprintCallable)
	void BeginBattle();

	UFUNCTION(BlueprintCallable)
	void ExitBattle();
};