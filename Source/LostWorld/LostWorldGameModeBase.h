#pragma once


#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "LostWorldGameModeBase.generated.h"


UCLASS()
class LOSTWORLD_API ALostWorldGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:
// ---------------------------------------- Functions ---------------------------------------- //
	// Logging function that prints to both the in-game display and saves to the text files.
	// Since it's in the GameModeBase, it can be accessed via any child GameMode, and therefore
	// from anywhere in the game.
	static void DualLog(const FString& PreBuiltString);
};
