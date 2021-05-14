#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"

#include "Components/Image.h"
#include "Components/Button.h"

#include "WidgetComponent_MinimapRoom.generated.h"

// Forward Declarations
class ABaseClass_GridTile;
class UBaseClass_Widget_Minimap;


UCLASS()
class LOSTWORLD_422_API UWidgetComponent_MinimapRoom : public UUserWidget
{
	GENERATED_BODY()
	
public:
// Base Variables
// --------------------------------------------------

// ------------------------- Components
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (BindWidget))
	UImage* BackgroundImage;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (BindWidget))
	UButton* InteractButton;

// ------------------------- References
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	ABaseClass_GridTile* GridTileReference;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UBaseClass_Widget_Minimap* MinimapReference;

// ------------------------- Technical Variables
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	int X_Coordinate;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	int Y_Coordinate;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	bool PlayerCanMoveTo;

// Functions
// --------------------------------------------------

// ------------------------- Widget
	UFUNCTION()
	void SetColour();

// ------------------------- Room
	UFUNCTION(BlueprintCallable)
	void OnRoomSelected();
};
