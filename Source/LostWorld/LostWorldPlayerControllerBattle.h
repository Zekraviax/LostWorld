#pragma once


#include "CoreMinimal.h"
#include "LostWorldPlayerControllerBase.h"
#include "LostWorldPlayerControllerBattle.generated.h"


UCLASS()
class LOSTWORLD_API ALostWorldPlayerControllerBattle : public ALostWorldPlayerControllerBase
{
	GENERATED_BODY()
	
public:
// ---------------------------------------- Variables ---------------------------------------- //
	// This keeps track of which stack entry the player is manually selecting targets for.
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	int StackEntryIndexForManualTargetSelection = -1;	

// ---------------------------------------- Functions ---------------------------------------- //

// -------------------------------- Player input
protected:
	virtual void SetupInputComponent() override;

public:
// -------------------------------- Basic movement
	void PlayerMoveNorth();
	void PlayerMoveSouth();
	void PlayerMoveEast();
	void PlayerMoveWest();
};