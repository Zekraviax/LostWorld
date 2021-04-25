#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"

#include "LostWorld_422GameModeBase.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"

#include "WidgetComponent_RoomEncounter.generated.h"


UCLASS()
class LOSTWORLD_422_API UWidgetComponent_RoomEncounter : public UUserWidget
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

// ------------------------- Encounter
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	F_LevelRoom_Encounter EncounterData;

// Base Variables
// --------------------------------------------------

// ------------------------- Encounter
	UFUNCTION(BlueprintCallable)
	void SelectedEncounter();
};
