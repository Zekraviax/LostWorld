#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"

#include "Components/UniformGridPanel.h"
#include "Components/GridPanel.h"

#include "BaseClass_Widget_Minimap.generated.h"

// Forward Declarations
class UWidgetComponent_MinimapRoom;
class ABaseClass_GridTile;


UCLASS()
class LOSTWORLD_422_API UBaseClass_Widget_Minimap : public UUserWidget
{
	GENERATED_BODY()
	
public:
// Base Variables
// --------------------------------------------------

// ------------------------- Components
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components", meta = (BindWidget))
	UUniformGridPanel* LevelGrid;

// ------------------------- Widgets
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widgets")
	TSubclassOf<UWidgetComponent_MinimapRoom> MinimapRoom_Class;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Widgets")
	UWidgetComponent_MinimapRoom* MinimapRoom_Widget;

// ------------------------- Actors
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Actors")
	TSubclassOf<ABaseClass_GridTile> GridTile_Class;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Actors")
	ABaseClass_GridTile* GridTile_Actor;

// Functions
// --------------------------------------------------

// ------------------------- Rooms
	UFUNCTION(BlueprintCallable)
	void GenerateLevel();
};
