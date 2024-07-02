#include "Library_CardFunctions.h"


// Assign each library function its own unique index
#define NOTHING 0
#define DRAW_CARDS 1
#define DEAL_DAMAGE 2
//#define GUN_DOWN 0
//#define SHOCKWAVE 1
//#define SUDDEN_INSPIRATION 2
//#define ESSENCE_RECYCLING 2
//#define RECALL 4
//#define ROLLING_QUAKE 5


Library_CardFunctions::Library_CardFunctions()
{
}


Library_CardFunctions::~Library_CardFunctions()
{
}


//-------------------- Initialization --------------------//
void Library_CardFunctions::InitializeCardFunctions()
{
	UE_LOG(LogTemp, Warning, TEXT("Initialize ability functions."));

	CardFunctions[NOTHING] = &Library_CardFunctions::Nothing;
	CardFunctions[DRAW_CARDS] = &Library_CardFunctions::DrawCards;
	CardFunctions[DEAL_DAMAGE] = &Library_CardFunctions::DealDamage;
	//CardFunctions[GUN_DOWN] = &ABaseClass_CardFunctionsLibrary::Gun_Down;
	//CardFunctions[SHOCKWAVE] = &ABaseClass_CardFunctionsLibrary::Shockwave;
	//CardFunctions[SUDDEN_INSPIRATION] = &ABaseClass_CardFunctionsLibrary::Sudden_Inspiration;
	//CardFunctions[ESSENCE_RECYCLING] = &ABaseClass_CardFunctionsLibrary::Essence_Recycling;
	//CardFunctions[RECALL] = &ABaseClass_CardFunctionsLibrary::Recall;
	//CardFunctions[ROLLING_QUAKE] = &ABaseClass_CardFunctionsLibrary::Rolling_Quake;
	
	UE_LOG(LogTemp, Warning, TEXT("Successfully initialized ability functions."));
}


void Library_CardFunctions::ExecuteCardFunction(int CardFunctionIndex, const FCardOnStack& StackEntry)
{
	if (CardFunctionIndex < 0 || CardFunctionIndex > CARD_FUNCTIONS_COUNT) {
		return;
	}
	
	CurrentCardOnStack = StackEntry;
	
	// This is the simple, 1-line way of executing a card function
	// but this method of executing functions means we can't pass any arguments
	(this->* (CardFunctions[CardFunctionIndex]))();

	// The other way is many more lines of code but offers more flexibility
	// This method also means we don't have to #DEFINE each function's index
	/* if (CardFunctionIndex == 0) {
		Nothing();
	} else if (CardFunctionIndex == 1) {
		DrawCards();
	} */
}


//-------------------- Library --------------------//
void Library_CardFunctions::Nothing()
{
	UE_LOG(LogTemp, Warning, TEXT("Execute Function: Nothing"));
}

void Library_CardFunctions::DrawCards()
{

}

void Library_CardFunctions::DealDamage()
{

}