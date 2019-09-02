	// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseClass_CardFunctionsLibrary.h"

#include "BaseClass_EntityInBattle.h"
#include "LostWorld_422GameStateBase.h"

// Function index definitions
#define NOTHING 0
#define DEAL_DAMAGE 1
#define DRAW_CARDS 2

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
	UE_LOG(LogTemp, Warning, TEXT("Initialize functions."));

	CardFunctions[NOTHING] = &ABaseClass_CardFunctionsLibrary::CardFunction_Nothing;
	CardFunctions[DEAL_DAMAGE] = &ABaseClass_CardFunctionsLibrary::CardFunction_DealDamage;
	CardFunctions[DRAW_CARDS] = &ABaseClass_CardFunctionsLibrary::CardFunction_DrawCards;

	UE_LOG(LogTemp, Warning, TEXT("Successfully initialized functions."));
}

//-------------------- Card Functions --------------------//

void ABaseClass_CardFunctionsLibrary::CardFunction_Nothing()
{
	UE_LOG(LogTemp, Warning, TEXT("Execute Function: Nothing"));
}

void ABaseClass_CardFunctionsLibrary::CardFunction_DealDamage()
{
	int32 DamageValue = ReturnIntValueFromRules();
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, TEXT("Execute Function: Deal Damage"));

	for (int i = 0; i < LocalCardReference.CurrentTargets.Num(); i++)
	{
		int32 OldHealthValue = LocalCardReference.CurrentTargets[i]->EntityBaseData.HealthValues.X_Value;
		LocalCardReference.CurrentTargets[i]->EntityBaseData.HealthValues.X_Value -= DamageValue;

		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, (TEXT("Target: " + LocalCardReference.CurrentTargets[i]->EntityBaseData.DisplayName)));
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, (TEXT("Damage: " + FString::FromInt(DamageValue) + "  /  New Health Value: " + FString::FromInt(LocalCardReference.CurrentTargets[i]->EntityBaseData.HealthValues.X_Value) + "  /  Old Health Value: " + FString::FromInt(OldHealthValue))));
	}
}

void ABaseClass_CardFunctionsLibrary::CardFunction_DrawCards()
{
	UE_LOG(LogTemp, Warning, TEXT("Execute Function: Draw Cards"));
	int32 DrawValue = ReturnIntValueFromRules();

	for (int i = 0; i < DrawValue; i++)
	{
		if (LocalCardReference.Controller->CardsInDeck.Num() > 0) {
			LocalCardReference.Controller->CardsInHand.Add(LocalCardReference.Controller->CardsInDeck[0]);

			// Set ownership
			//if (!LocalCardReference.Controller->CardsInHand[0].Owner) {
				LocalCardReference.Controller->CardsInHand.Last().Owner = LocalCardReference.Controller;
				GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("Set Card Owner"));
			//}
			//if (!LocalCardReference.Controller->CardsInHand[0].Controller) {
				LocalCardReference.Controller->CardsInHand.Last().Controller = LocalCardReference.Controller;
				GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("Set Card Controller"));
			//}

			LocalCardReference.Controller->CardsInDeck.RemoveAt(0);
		}
	}

	LocalCardReference.Controller->UpdateCardIndicesInAllZones();
	LocalCardReference.Controller->UpdateCardWidgets();
}

//-------------------- Execute Functions --------------------//

void ABaseClass_CardFunctionsLibrary::ExecuteCardFunctions()
{
	int32 CardFunctionIndex;

	// Get GameState
	if (!GameStateRef)
		GameStateRef = GetWorld()->GetGameState<ALostWorld_422GameStateBase>();

	// Set card reference
	LocalCardReference = GameStateRef->TheStack[0].Card;

	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, TEXT("Searching for function to execute."));
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, (TEXT("Card Targets: ") + FString::FromInt(LocalCardReference.CurrentTargets.Num())));

	CardFunctionIndex = (int32)((uint8)LocalCardReference.FunctionsWithRules[0].Function);

	//Valid range check
	if (CardFunctionIndex >= CARD_FUNCTIONS_COUNT || CardFunctionIndex < 0) {
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Cyan, TEXT("Failed Execution"));
		return;
	}

	(this->* (CardFunctions[CardFunctionIndex]))();
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, TEXT("Successful Execution"));

	GameStateRef->TheStack.RemoveAt(0);
	if (GameStateRef->TheStack.Num() > 0) {
		GetWorldTimerManager().SetTimer(StackTimerHandle, this, &ABaseClass_CardFunctionsLibrary::ExecuteCardFunctions, GameStateRef->TheStack[0].Delay);
	}
}


void ABaseClass_CardFunctionsLibrary::AddCardFunctionsToTheStack(FCardBase Card)
{
	FStackEntry NewStackEntry;

	// Get GameState
	if (!GameStateRef)
		GameStateRef = GetWorld()->GetGameState<ALostWorld_422GameStateBase>();

	for (int i = 0; i < Card.FunctionsWithRules.Num(); i++)
	{
		// Add to the stack
		NewStackEntry = FStackEntry(Card, 1.f);

		// Set targets
		// (if target equals CastTarget, do nothing)
		// Self
		if (NewStackEntry.Card.FunctionsWithRules[0].Rules.Contains(E_Card_Rules::E_Rule_Target_Self)) {
			NewStackEntry.Card.CurrentTargets.Empty();
			NewStackEntry.Card.CurrentTargets.Add(NewStackEntry.Card.Controller);
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Cyan, TEXT("Target: Self"));
		}

		// All Enemies
		else if (NewStackEntry.Card.FunctionsWithRules[0].Rules.Contains(E_Card_Rules::E_Rule_Target_AllEnemies)) {
			NewStackEntry.Card.CurrentTargets.Empty();
			for (TActorIterator<ABaseClass_EntityInBattle> ActorItr(GetWorld()); ActorItr; ++ActorItr) {
				ABaseClass_EntityInBattle* FoundEntity = *ActorItr;

				if (FoundEntity->EntityBaseData.IsPlayerControllable == false) {
					NewStackEntry.Card.CurrentTargets.Add(FoundEntity);
					GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Cyan, TEXT("Target: Get All Enemies"));
				}
			}
		}

		GameStateRef->TheStack.Add(NewStackEntry);

		// Remove all functions except one at a time.
		for (int j = 0; j < GameStateRef->TheStack[i].Card.FunctionsWithRules.Num(); j++) {
			if (j != i) {
				GameStateRef->TheStack[i].Card.FunctionsWithRules.RemoveAt(j);
			}
		}
	}

	// Start timer for the stack
	//GetWorldTimerManager().SetTimer(HealthRegenDelayTimerHandle, this, &AEntity_Base::StartHealthRegenTick, CurrentStats.HealthPoints_RegenStartDelay, false);
	GetWorldTimerManager().SetTimer(StackTimerHandle, this, &ABaseClass_CardFunctionsLibrary::ExecuteCardFunctions, GameStateRef->TheStack[0].Delay);
}


void ABaseClass_CardFunctionsLibrary::SetCardTargets()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, TEXT("Set Card Targets"));

	// Clear the targets array if the Target mode is *not* set to CastTarget
	// Otherwise, do nothing
	//if (!LocalCardReference.FunctionsWithRules[0].Rules.Contains(E_Card_Rules::E_Rule_Target_CastTarget))
	//	LocalCardReference.CurrentTargets.Empty();

	//if (LocalCardReference.FunctionsWithRules[0].Rules.Contains(E_Card_Rules::E_Rule_Target_Self))
	//	LocalCardReference.CurrentTargets.Add(LocalCardReference.Controller);
}


int32 ABaseClass_CardFunctionsLibrary::ReturnIntValueFromRules()
{
	// Return Fixed Integers
	if (LocalCardReference.FunctionsWithRules[0].Rules.Contains(E_Card_Rules::E_Rule_FixedInteger_One))
		return 1;
	else if (LocalCardReference.FunctionsWithRules[0].Rules.Contains(E_Card_Rules::E_Rule_FixedInteger_Two))
		return 2;
	else if (LocalCardReference.FunctionsWithRules[0].Rules.Contains(E_Card_Rules::E_Rule_FixedInteger_Three))
		return 3;
	else if (LocalCardReference.FunctionsWithRules[0].Rules.Contains(E_Card_Rules::E_Rule_FixedInteger_Four))
		return 4;
	else if (LocalCardReference.FunctionsWithRules[0].Rules.Contains(E_Card_Rules::E_Rule_FixedInteger_Five))
		return 5;
	else if (LocalCardReference.FunctionsWithRules[0].Rules.Contains(E_Card_Rules::E_Rule_FixedInteger_Six))
		return 6;
	else if (LocalCardReference.FunctionsWithRules[0].Rules.Contains(E_Card_Rules::E_Rule_FixedInteger_Seven))
		return 7;
	else if (LocalCardReference.FunctionsWithRules[0].Rules.Contains(E_Card_Rules::E_Rule_FixedInteger_Eight))
		return 8;
	else if (LocalCardReference.FunctionsWithRules[0].Rules.Contains(E_Card_Rules::E_Rule_FixedInteger_Nine))
		return 9;
	else if (LocalCardReference.FunctionsWithRules[0].Rules.Contains(E_Card_Rules::E_Rule_FixedInteger_Ten))
		return 10;
	// Calculate and return variable integers
	else if (LocalCardReference.FunctionsWithRules[0].Rules.Contains(E_Card_Rules::E_Rule_VariableInteger_Current_Power))
		return LocalCardReference.Controller->EntityBaseData.ManaValues.X_Value;
	else if (LocalCardReference.FunctionsWithRules[0].Rules.Contains(E_Card_Rules::E_Rule_VariableInteger_Random_Number))
		return FMath::RandRange(0, 10);
	else
		return 0;
}