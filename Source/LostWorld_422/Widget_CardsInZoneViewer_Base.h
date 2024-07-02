#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"

#include "Components/UniformGridPanel.h"

#include "Widget_CardsInZoneViewer_Base.generated.h"


// Forward Declarations
class ABaseClass_EntityInBattle;
class ABaseClass_PlayerController;


// Unique Enums


UCLASS()
class LOSTWORLD_422_API UWidget_CardsInZoneViewer_Base : public UUserWidget
{
	GENERATED_BODY()
	
public:
// Variables
// --------------------------------------------------

// ------------------------- Components
	//Grid Panel with scroll?
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UUniformGridPanel* CardsGridPanel;

// Functions
// --------------------------------------------------

// ------------------------- Widget
	UFUNCTION()
	void OnWidgetWOpened();
};
