#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"

#include "Components/UniformGridPanel.h"
#include "Components/GridPanel.h"
#include "Engine/DataTable.h"

#include "BaseClass_Widget_Minimap.generated.h"

// Forward Declarations
class UWidgetComponent_MinimapRoom;
class ABaseClass_GridTile;
class ABaseClass_EntityInBattle;


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

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Actors")
	TSubclassOf<ABaseClass_EntityInBattle> EntityInBattle_Class;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Actors")
	ABaseClass_EntityInBattle* EntityInBattle_Actor;

// ------------------------- References
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "References")
	UDataTable* EnemyFormationsTable;

// ------------------------- Map
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Map")
	TArray<ABaseClass_GridTile*> GridTilesArray;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Map")
	TArray<UWidgetComponent_MinimapRoom*> PlayerNeighbouringRoomWidgets;

	// Generic Arrays for Groups of MinimapTiles (e.g. Rooms and Corridors)
	UPROPERTY()
	TArray<UWidgetComponent_MinimapRoom*> MinimapRoomArrayOne;
	UPROPERTY()
	TArray<UWidgetComponent_MinimapRoom*> MinimapRoomArrayTwo;
	UPROPERTY()
	TArray<UWidgetComponent_MinimapRoom*> MinimapRoomArrayThree;
	UPROPERTY()
	TArray<UWidgetComponent_MinimapRoom*> MinimapRoomArrayFour;
	UPROPERTY()
	TArray<UWidgetComponent_MinimapRoom*> MinimapRoomArrayFive;
	UPROPERTY()
	TArray<UWidgetComponent_MinimapRoom*> MinimapRoomArraySix;
	UPROPERTY()
	TArray<UWidgetComponent_MinimapRoom*> MinimapRoomArraySeven;
	UPROPERTY()
	TArray<UWidgetComponent_MinimapRoom*> MinimapRoomArrayEight;
	UPROPERTY()
	TArray<UWidgetComponent_MinimapRoom*> FullMinimapRoomArray;

	// Generic MinimapTiles
	UPROPERTY()
	UWidgetComponent_MinimapRoom* MinimapTileOne;

// Functions
// --------------------------------------------------

// ------------------------- Map
	UFUNCTION(BlueprintCallable)
	void GenerateLevel();

	UFUNCTION()
	void GetPlayerNeighbouringTiles(UWidgetComponent_MinimapRoom* CurrentRoomWidget);
};
