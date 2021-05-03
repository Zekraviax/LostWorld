#include "BaseClass_CardFunctionsLibrary.h"

#include "BaseClass_EntityInBattle.h"
#include "LostWorld_422GameStateBase.h"


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
ABaseClass_CardFunctionsLibrary::ABaseClass_CardFunctionsLibrary()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
}

// Called when the game starts or when spawned
void ABaseClass_CardFunctionsLibrary::BeginPlay()
{
	Super::BeginPlay();
	
	InitializeCardFunctions();
}

// Called every frame
void ABaseClass_CardFunctionsLibrary::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}


//-------------------- Function Initializations --------------------//
void ABaseClass_CardFunctionsLibrary::InitializeCardFunctions()
{
	UE_LOG(LogTemp, Warning, TEXT("Initialize ability functions."));

	CardFunctions[NOTHING] = &ABaseClass_CardFunctionsLibrary::CardFunction_Nothing;
	CardFunctions[DRAW_CARDS] = &ABaseClass_CardFunctionsLibrary::CardFunction_DrawCards;
	CardFunctions[DEAL_DAMAGE] = &ABaseClass_CardFunctionsLibrary::CardFunction_DealDamage;
	//CardFunctions[GUN_DOWN] = &ABaseClass_CardFunctionsLibrary::Gun_Down;
	//CardFunctions[SHOCKWAVE] = &ABaseClass_CardFunctionsLibrary::Shockwave;
	//CardFunctions[SUDDEN_INSPIRATION] = &ABaseClass_CardFunctionsLibrary::Sudden_Inspiration;
	//CardFunctions[ESSENCE_RECYCLING] = &ABaseClass_CardFunctionsLibrary::Essence_Recycling;
	//CardFunctions[RECALL] = &ABaseClass_CardFunctionsLibrary::Recall;
	//CardFunctions[ROLLING_QUAKE] = &ABaseClass_CardFunctionsLibrary::Rolling_Quake;


	UE_LOG(LogTemp, Warning, TEXT("Successfully initialized ability functions."));
}



//-------------------- Card Functions --------------------//
void ABaseClass_CardFunctionsLibrary::CardFunction_Nothing()
{
	UE_LOG(LogTemp, Warning, TEXT("Execute Function: Nothing"));
}

void ABaseClass_CardFunctionsLibrary::CardFunction_DrawCards()
{
	
}

void ABaseClass_CardFunctionsLibrary::CardFunction_DealDamage()
{

}

//-------------------- Execute Functions --------------------//