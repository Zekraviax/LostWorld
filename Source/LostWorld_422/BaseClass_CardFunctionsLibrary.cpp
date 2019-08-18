	// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseClass_CardFunctionsLibrary.h"

#include "BaseClass_EntityInBattle.h"

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
		//FCardBase FirstCardInDeck = LocalCardReference.Controller->CardsInDeck[]
		if (LocalCardReference.Controller->CardsInDeck.Num() > 0)
		{
			LocalCardReference.Controller->CardsInHand.Add(LocalCardReference.Controller->CardsInDeck[0]);
			LocalCardReference.Controller->CardsInDeck.RemoveAt(0);
		}
	}

	LocalCardReference.Controller->UpdateCardIndicesInAllZones();
}

//-------------------- Execute Functions --------------------//

void ABaseClass_CardFunctionsLibrary::ExecuteCardFunctions(FCardBase CardReference)
{
	LocalCardReference = CardReference;
	int32 CardFunctionIndex;

	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, TEXT("Searching for function to execute."));
	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, (TEXT("Card Targets: ") + FString::FromInt(CardReference.CurrentTargets.Num())));
	
	//for (int i = 0; i < LocalCardReference.FunctionsWithRules.Num(); i++)
	//{
	CardFunctionIndex = (int32)((uint8)LocalCardReference.FunctionsWithRules[0].Function);
	SetCardTargets();

	//Valid range check
	if (CardFunctionIndex >= CARD_FUNCTIONS_COUNT || CardFunctionIndex < 0)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Cyan, TEXT("Failed Execution"));
		return;
	}

	(this->* (CardFunctions[CardFunctionIndex]))();
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, TEXT("Successful Execution"));

	LocalCardReference.FunctionsWithRules.RemoveAt(0);
	if (LocalCardReference.FunctionsWithRules.Num() > 0)
		ExecuteCardFunctions(LocalCardReference);
}


void ABaseClass_CardFunctionsLibrary::SetCardTargets()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, TEXT("Set Card Targets"));

	// Clear the targets array if the Target mode is *not* set to CastTarget
	// Otherwise, do nothing
	if (!LocalCardReference.FunctionsWithRules[0].Rules.Contains(E_Card_Rules::E_Rule_Target_CastTarget))
		LocalCardReference.CurrentTargets.Empty();

	if (LocalCardReference.FunctionsWithRules[0].Rules.Contains(E_Card_Rules::E_Rule_Target_Self))
		LocalCardReference.CurrentTargets.Add(LocalCardReference.Controller);
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