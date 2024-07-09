#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "LostWorld_422GameModeBase.h"
#include "EngineUtils.h"
#include "BaseClass_Widget_ZoneSearch.h"
#include "CardAbilityActor_BaseClass.h"

#include "BaseClass_CardFunctionsLibrary.generated.h"

// Forward Declarations
class ALostWorld_422GameStateBase;

// Explicitly define number of static card functions
#define CARD_FUNCTIONS_COUNT 3
//#define CARD_ABILITY_CONDITIONS 0


UCLASS()
class LOSTWORLD_422_API ABaseClass_CardFunctionsLibrary : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABaseClass_CardFunctionsLibrary();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	FStackEntry StackEntry;


// Functions --------------------------------------------------

// -------------------------------------------------- Function Library
	// The Functions Pointer Variable Type
	// Functions take 0 parameters and return void
	typedef void(ABaseClass_CardFunctionsLibrary::*FunctionPtrType)();

	// Static Array of X function pointers
	// where X = CARD_FUNCTIONS_COUNT
	FunctionPtrType CardFunctions[CARD_FUNCTIONS_COUNT];

	// Initialize the array
	void InitializeCardFunctions();

	// Executes a function from the CardFunctions Pointer Array
	void ExecuteFunction(const FStackEntry& InStackEntry);

	// The Actual Functions which are implemented in subclasses of this class.
	virtual void Nothing();
	virtual void DrawCards();
	virtual void DealDamage();
	//virtual void Gun_Down();
	//virtual void Shockwave();
	//virtual void Sudden_Inspiration();
	//virtual void Essence_Recycling();
	//virtual void Recall();
	//virtual void Rolling_Quake();
};