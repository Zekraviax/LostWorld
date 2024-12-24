#pragma once


#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Variables.h"
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
	// Log Levels:
	// 0 - Fatal Fault
	// 1 - Error
	// 2 - Warning
	// 3 - Verbose Log
	// 4 - Very Verbose Log
	static void DualLog(const FString& PreBuiltString, int InLogLevel);

	// Parse sub-variables within written text variables.
	// E.g. ${BasePower} should be replaced with the power of a card.
	static FString ParseVariablesInText(const FCard& InCard, const FString& InString);
};
