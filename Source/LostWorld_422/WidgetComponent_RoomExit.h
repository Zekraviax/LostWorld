#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"

#include "LostWorld_422GameModeBase.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"

#include "WidgetComponent_RoomExit.generated.h"

UCLASS()
class LOSTWORLD_422_API UWidgetComponent_RoomExit : public UUserWidget
{
	GENERATED_BODY()
	
public:
// Base Variables
// --------------------------------------------------

// ------------------------- Components
	UPROPERTY(meta = (BindWidget))
	UButton* InteractButton;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* EncounterLabel;

// ------------------------- Room
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	F_LevelRoom_Exit RoomData;

// Functions
// --------------------------------------------------

// ------------------------- Room
	UFUNCTION(BlueprintCallable)
	void SelectedExit();
};
