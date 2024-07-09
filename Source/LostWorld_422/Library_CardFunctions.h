#pragma once

#include "CoreMinimal.h"

#include "BaseClass_Widget_ZoneSearch.h"
#include "LostWorld_Variables.h"

#include "Library_CardFunctions.generated.h"


// We explicitly define number of static card functions here
#define CARD_FUNCTIONS_COUNT 3


// ReSharper disable once CppUE4CodingStandardNamingViolationWarning
UCLASS()
class LOSTWORLD_422_API ALibrary_CardFunctions : public AActor
{

	GENERATED_BODY()
	
public:
// Variables --------------------------------------------------	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	// ReSharper disable once CppUPropertyMacroCallHasNoEffect
	FStackEntry StackEntry;

// Functions --------------------------------------------------

// -------------------------------------------------- Function Library
	
	// The Functions Pointer Variable Type
	// Functions take 0 parameters and return void
	typedef void(ALibrary_CardFunctions::*FunctionPtrType)();

	// Static Array of X function pointers
	// where X = CARD_FUNCTIONS_COUNT
	FunctionPtrType CardFunctions[CARD_FUNCTIONS_COUNT];

	void BeginPlay();
	
	// Initialize the array
	void InitializeCardFunctions();

	// Executes a function from the CardFunctions Pointer Array
	void ExecuteFunction(const FStackEntry& InStackEntry);

	// The card functions
	void Nothing() const;
	void DrawCards();
	void DealDamage();
};
