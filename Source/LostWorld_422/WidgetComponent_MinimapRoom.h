#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "WidgetComponent_MinimapRoom.generated.h"

// Forward Declarations
class ABaseClass_GridTile;


UCLASS()
class LOSTWORLD_422_API UWidgetComponent_MinimapRoom : public UUserWidget
{
	GENERATED_BODY()
	
public:
// Base Variables
// --------------------------------------------------

// ------------------------- References
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "References")
	ABaseClass_GridTile* GridTileReference;

// ------------------------- Technical Variables
	UPROPERTY()
	int X_Coordinate;

	UPROPERTY()
	int Y_Coordinate;

// Functions
// --------------------------------------------------

// ------------------------- Room
	UFUNCTION(BlueprintCallable)
	void OnRoomSelected();
};
