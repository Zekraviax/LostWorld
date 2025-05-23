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
	// 0 - Error
	// 1 - Warning
	// 2 - Log
	// 3 - Verbose Log
	// 4 - Very Verbose Log
	// To-Do: Improve the LogLevel developer setting to allow for multiple log levels to be enabled at a time.
	// To-Do: Implement an option to save the text to a combat log.
	// To-Do: Add colours!
	static void DualLog(const FString& PreBuiltString, int InLogLevel);

	// Parse sub-variables within written text variables.
	// E.g. ${BasePower} should be replaced with the power of a card.
	static FString ParseVariablesInText(const FCard& InCard, const FString& InString);
};
