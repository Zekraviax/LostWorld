#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"

#include "Components/Image.h"

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
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "References", meta = (BindWidget))
	UImage* BackgroundImage;

// ------------------------- References
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "References")
	ABaseClass_GridTile* GridTileReference;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "References")
	UBaseClass_Widget_Minimap* MinimapReference;

// ------------------------- Technical Variables
	UPROPERTY()
	int X_Coordinate;

	UPROPERTY()
	int Y_Coordinate;

// Functions
// --------------------------------------------------

// ------------------------- Widget
	UFUNCTION()
	void SetColour();

// ------------------------- Room
	UFUNCTION(BlueprintCallable)
	void OnRoomSelected();
};
