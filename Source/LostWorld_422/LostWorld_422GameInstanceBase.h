#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"

#include "LostWorld_422GameInstanceBase.generated.h"


// Forward Declarations
class ABaseClass_LevelRoom;


UCLASS()
class LOSTWORLD_422_API ULostWorld_422GameInstanceBase : public UGameInstance
{
	GENERATED_BODY()

public:
// Base Variables
// --------------------------------------------------

// ------------------------- Constructors
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<ABaseClass_LevelRoom> TestOne_Room_Class;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	ABaseClass_LevelRoom* Room_Reference;

// ------------------------- Technical Variables
	// Dev Mode
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool DevMode = true;


// Functions
// --------------------------------------------------
	UFUNCTION()
	void SpawnNewRoom(TSubclassOf<ABaseClass_LevelRoom> RoomToSpawnClass, FVector WorldLocation, FRotator WorldRotation);
};
