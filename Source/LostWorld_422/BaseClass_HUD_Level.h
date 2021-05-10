#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"

#include "Components/ScrollBox.h"
#include "Components/TextBlock.h"
#include "BaseClass_CardUserWidget.h"
#include "BaseClass_Widget_DeckBuilder.h"
#include "BaseClass_Widget_Minimap.h"
#include "LostWorld_422GameModeBase.h"

#include "BaseClass_HUD_Level.generated.h"


UCLASS()
class LOSTWORLD_422_API UBaseClass_HUD_Level : public UUserWidget
{
	GENERATED_BODY()

protected:

public:
// Base Variables
// --------------------------------------------------

// ------------------------- Components
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (BindWidget))
	UBaseClass_Widget_Minimap* Minimap;

// ------------------------- Widgets
	// Deck Builder Class
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<UBaseClass_Widget_DeckBuilder> DeckBuilder_Class;

	// Deck Builder Instance
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UBaseClass_Widget_DeckBuilder* DeckBuilderRef;

// ------------------------- Room Features
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TArray<E_LevelRoom_EncounterTypes> EncounterList;

// Functions
// --------------------------------------------------

// ------------------------- Widgets
	UFUNCTION(BlueprintCallable)
	void OpenDeckBuilder();
};
