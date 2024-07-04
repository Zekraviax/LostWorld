#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"

#include "Components/ScrollBox.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"
#include "BaseClass_Widget_DeckBuilder.h"
#include "BaseClass_CardUserWidget.h"

#include "BaseClass_HUD_Battle.generated.h"


// Forward Declarations
class ALostWorld_422GameStateBase;
class UWidget_Inventory_Base;
class UWidget_CardsInZoneViewer_Base;


// Class-Specific Enums
UENUM(BlueprintType)
enum class E_ContinueTurnButton_Function : uint8
{
	E_EndTurn,
	E_ContinueTurn,
};


UCLASS()
class LOSTWORLD_422_API UBaseClass_HUD_Battle : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct();

// Variables
// --------------------------------------------------

// ------------------------- Components
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (BindWidget))
	UScrollBox* CardsInHand_ScrollBox;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (BindWidget))
	UButton* GraveyardButton;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (BindWidget))
	UButton* DeckButton;

// ------------------------- Technical Variables
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	ALostWorld_422GameStateBase* GameStateRef;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	ABaseClass_EntityInBattle* CurrentControlledEntityReference;

// ------------------------- Widgets
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<UBaseClass_Widget_DeckBuilder> DeckBuilder_Class;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UBaseClass_Widget_DeckBuilder* DeckBuilderRef;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<UBaseClass_CardUserWidget> Card_Class;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UBaseClass_CardUserWidget* CardWidgetRef;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<UWidget_Inventory_Base> Inventory_Class;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UWidget_Inventory_Base* Inventory_Reference;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<UWidget_CardsInZoneViewer_Base> CardsInZoneViewer_Class;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UWidget_CardsInZoneViewer_Base* CardsInZoneViewer_Reference;


// Functions
// --------------------------------------------------

// ------------------------- Widgets
	UFUNCTION()
	void CreatePlayerCardsInHandWidgets(bool ClearHand, FCard CardInHand);

	UFUNCTION(BlueprintCallable)
	void OpenInventoryWidget();

// ------------------------- Battle
	UFUNCTION(BlueprintCallable)
	void EndTurn_Function();

	UFUNCTION(BlueprintCallable)
	void ViewCardsInZone(E_Card_Zones Zone);
};
