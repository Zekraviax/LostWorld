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

// Base Variables
// --------------------------------------------------

// ------------------------- References
	UPROPERTY()
	FCardBase LocalCardReference;

	UPROPERTY()
	ALostWorld_422GameStateBase* GameStateRef;

// ------------------------- Timers	
	UPROPERTY()
	FTimerHandle StackTimerHandle;

// ------------------------- Constructors
	//UPROPERTY(EditAnywhere, BlueprintReadWrite)
	//TSubclassOf<ACardAbilityActor_DrawCards> DrawCards_Class;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	ACardAbilityActor_BaseClass* CardAbilityActor_Reference;


// Functions
// --------------------------------------------------

// ------------------------- Card

// ------------------------- Function Library
	// The Functions Pointer Variable Type
	// Functions take 0 parameters and return void
	typedef void(ABaseClass_CardFunctionsLibrary::*FunctionPtrType)();

	// Static Array of X function pointers
	FunctionPtrType CardFunctions[CARD_FUNCTIONS_COUNT];

	// Executes a function from the CardFuntions Pointer Array
	// Implementation does not vary in subclasses, so no virtual

	// Initialize the array
	void InitializeCardFunctions();

	// The Actual Functions which are implemented in subclasses by this class.
	virtual void CardFunction_Nothing();
	virtual void CardFunction_DrawCards();
	virtual void CardFunction_DealDamage();
	//virtual void Gun_Down();
	//virtual void Shockwave();
	//virtual void Sudden_Inspiration();
	//virtual void Essence_Recycling();
	//virtual void Recall();
	//virtual void Rolling_Quake();
};