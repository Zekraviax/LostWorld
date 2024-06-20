#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"

#include "Engine/DataTable.h"
#include "Widget_Inventory_Base.h"

#include "LostWorld_422GameInstanceBase.generated.h"


// Forward Declarations
class ABaseClass_LevelRoom;


UCLASS()
class LOSTWORLD_422_API ULostWorld_422GameInstanceBase : public UGameInstance
{
	GENERATED_BODY()

// Keep a reference to things like blueprints and databases here


public:
// Base Variables
// --------------------------------------------------

// ------------------------- Constructors
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<ABaseClass_LevelRoom> TestOne_Room_Class;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	ABaseClass_LevelRoom* Room_Reference;


// ------------------------- Persistent Variables and Blueprints
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UDataTable* CardsTable;


// ------------------------- Technical Variables
	// Dev Mode
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool DevMode = true;


// Functions
// --------------------------------------------------
	UFUNCTION()
	void SpawnNewRoom(TSubclassOf<ABaseClass_LevelRoom> RoomToSpawnClass, FVector WorldLocation, FRotator WorldRotation);

	UDataTable* ReturnCardsTable();


// Inventory
// --------------------------------------------------
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<UWidget_Inventory_Base> Inventory_Class;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UWidget_Inventory_Base* Inventory_Reference;

	UFUNCTION(BlueprintCallable)
	UWidget_Inventory_Base* GetInventory();
};
