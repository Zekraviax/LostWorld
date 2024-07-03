#pragma once


#include "CoreMinimal.h"
#include "LostWorld_Variables.h"


// We explicitly define number of static card functions here
#define CARD_FUNCTIONS_COUNT 3


// ReSharper disable once CppUE4CodingStandardNamingViolationWarning
class LOSTWORLD_422_API Library_CardFunctions final
{
public:
	Library_CardFunctions();
	~Library_CardFunctions();

// Variables --------------------------------------------------	
	// The Functions Pointer Variable Type
	// Functions take 0 parameters and return void
	typedef void(Library_CardFunctions::*FunctionPtrType)();

	// Array of X library function pointers, where X = CARD_FUNCTIONS_COUNT
	FunctionPtrType CardFunctions[CARD_FUNCTIONS_COUNT];

	UPROPERTY()
	// ReSharper disable once CppUPropertyMacroCallHasNoEffect
	FCardOnStack CurrentCardOnStack;

// Functions --------------------------------------------------
	// Required set up for the card functions
	void InitializeCardFunctions();

	// Used to execute the card functions
	void ExecuteCardFunction(int CardFunctionIndex, const FCardOnStack& StackEntry);

	// The card functions
	void Nothing();
	void DrawCards();
	void DealDamage();
};
