#include "Library_CardFunctions.h"

#include "GameFramework/Actor.h"
#include "BaseClass_EntityInBattle.h"


// Function index definitions
#define NOTHING 0
#define DRAW_CARDS 1
#define DEAL_DAMAGE 2
//#define GUN_DOWN 0
//#define SHOCKWAVE 1
//#define SUDDEN_INSPIRATION 2
//#define ESSENCE_RECYCLING 2
//#define RECALL 4
//#define ROLLING_QUAKE 5


//-------------------- Base Functions --------------------//
// Sets default values
ALibrary_CardFunctions::ALibrary_CardFunctions(): CardFunctions{}
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
}

// Called when the game starts or when spawned
void ALibrary_CardFunctions::BeginPlay()
{
	Super::BeginPlay();
	
	InitializeCardFunctions();
}

// Called every frame
void ALibrary_CardFunctions::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}


//-------------------- Function Initializations --------------------//
void ALibrary_CardFunctions::InitializeCardFunctions()
{
	UE_LOG(LogTemp, Warning, TEXT("Initialize ability functions."));

	CardFunctions[NOTHING] = &ALibrary_CardFunctions::Nothing;
	CardFunctions[DRAW_CARDS] = &ALibrary_CardFunctions::DrawCards;
	CardFunctions[DEAL_DAMAGE] = &ALibrary_CardFunctions::DealDamage;
	//CardFunctions[GUN_DOWN] = &ABaseClass_CardFunctionsLibrary::Gun_Down;
	//CardFunctions[SHOCKWAVE] = &ABaseClass_CardFunctionsLibrary::Shockwave;
	//CardFunctions[SUDDEN_INSPIRATION] = &ABaseClass_CardFunctionsLibrary::Sudden_Inspiration;
	//CardFunctions[ESSENCE_RECYCLING] = &ABaseClass_CardFunctionsLibrary::Essence_Recycling;
	//CardFunctions[RECALL] = &ABaseClass_CardFunctionsLibrary::Recall;
	//CardFunctions[ROLLING_QUAKE] = &ABaseClass_CardFunctionsLibrary::Rolling_Quake;


	UE_LOG(LogTemp, Warning, TEXT("Successfully initialized ability functions."));
}


//-------------------- Execute Functions --------------------//
void ALibrary_CardFunctions::ExecuteFunction(const FStackEntry& InStackEntry)
{
	StackEntry = InStackEntry;
	(this->* (CardFunctions[StackEntry.Card.CardFunctionsAndValues[0].CardFunctionIndex]))();
}


//-------------------- Card Functions --------------------//
void ALibrary_CardFunctions::Nothing() const
{
	UE_LOG(LogTemp, Warning, TEXT("Execute Function: Nothing"));
}

void ALibrary_CardFunctions::DrawCards()
{
	UE_LOG(LogTemp, Warning, TEXT("Execute Function: Draw Cards"));

	// To-Do: Make this use the StackEntry's target, rather than the controller.
	for (int i = 0; i < StackEntry.Card.CardFunctionsAndValues[0].FunctionBaseValue; i++) {
		StackEntry.Controller->Event_DrawCard();
	}
}

void ALibrary_CardFunctions::DealDamage()
{
	UE_LOG(LogTemp, Warning, TEXT("Execute Function: Deal Damage"));
	int32 DamageValue = StackEntry.Card.CardFunctionsAndValues[0].FunctionBaseValue;

	for (int i = 0; i < StackEntry.Targets.Num(); i++) {
		Cast<ABaseClass_EntityInBattle>(StackEntry.Targets[i])->Event_DamageIncoming(DamageValue, StackEntry.Card.Elements[0], E_Card_DamageTypes::E_Other);
	}
}