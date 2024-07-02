#pragma once


#include "CoreMinimal.h"
#include "LostWorld_Variables.h"


// We explicitly define number of static card functions here
#define CARD_FUNCTIONS_COUNT 3


class LOSTWORLD_422_API Library_CardFunctions
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
	FCardOnStack CurrentCardOnStack;

// Functions --------------------------------------------------
	// Required set up for the card functions
	void InitializeCardFunctions();

	// Used to execute the card functions
	void ExecuteCardFunction(int CardFunctionIndex, const FCardOnStack& StackEntry);

	// The card functions
	virtual void Nothing();
	virtual void DrawCards();
	virtual void DealDamage();
};
