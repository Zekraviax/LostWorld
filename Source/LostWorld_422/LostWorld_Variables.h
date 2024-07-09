#pragma once

#include "CoreMinimal.h"
#include "LostWorld_422GameModeBase.h"

#include "Engine/DataTable.h"

#include "LostWorld_Variables.generated.h"


// Enums --------------------------------------------------
UENUM(BlueprintType)
enum class E_Card_Types : uint8
{
	E_Summon				UMETA(DisplayName = "Summon"),
	E_Spell					UMETA(DisplayName = "Spell"),
	E_Technique				UMETA(DisplayName = "Technique"),
	E_Command				UMETA(DisplayName = "Command"),
	E_Shout					UMETA(DisplayName = "Shout"),
};


UENUM(BlueprintType)
enum class E_Card_Elements : uint8
{
	E_NonElemental			UMETA(DisplayName = "Non-Elemental"),
	E_Fire					UMETA(DisplayName = "Fire"),
	E_Water					UMETA(DisplayName = "Water"),
	E_Air					UMETA(DisplayName = "Air"),
	E_Earth					UMETA(DisplayName = "Earth"),
	E_Light					UMETA(DisplayName = "Light"),
	E_Arcane				UMETA(DisplayName = "Arcane"),
	E_Cosmic				UMETA(DisplayName = "Cosmic"),
	E_Divine				UMETA(DisplayName = "Divine")
};


UENUM(BlueprintType)
enum class E_Card_DamageTypes : uint8
{
	E_Physical,
	E_Magical,
	E_LifeLoss,	// Use this for cards that require health as a cost or payment, so things like resistances are not factored in
	E_Other,
	E_NotApplicable,
};


UENUM(BlueprintType)
enum class E_Card_SetTargets : uint8
{
	E_None,
	E_Self,
	E_AnyAlly,
	E_AllAllies,
	E_AnyEnemy,
	E_AllEnemies,
	E_AnyTarget,
	E_CastTarget,
	E_AllTargets,
	E_UnoccupiedGridTile,
	E_Special,	// Use this when the targetting is too complex, and write a function in the Cards Class file.
};


// Structs --------------------------------------------------
USTRUCT(BlueprintType)
struct LOSTWORLD_422_API FCardFunction : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int CardFunctionIndex;

	// The base value of functions like damage dealt.
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int FunctionBaseValue;

	// Use the N/A value for functions that don't deal damage (e.g. card draw.)
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<E_Card_DamageTypes> DamageTypesOverride;

	// Use this for things like cards that deal multiple different damage instances.
	// Otherwise, leave blank.
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<E_Card_Elements> ElementsOverride;

	// Use this for cards that affect different targets with different functions.
	// E.g. a card that damages an enemy and draws you a card.
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	E_Card_SetTargets TargetsOverride;

	// To-Do: Add a description variable here, and make a function that
	// combines all descriptions in order.
	
	FCardFunction(): CardFunctionIndex(0), FunctionBaseValue(0), TargetsOverride()
	{
	}
};


USTRUCT(BlueprintType)
struct LOSTWORLD_422_API FCard : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Base")
	FString DisplayName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Base")
	int32 ManaCost;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Base")
	E_Card_Types Type;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Base")
	TArray<E_Card_Elements> Elements;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Display")
	UTexture2D* Art;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Display")
	FString Description;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Display")
	FString FlavourText;

	// The functions should be added to the array in the intended order of execution
	// Left int for the function, right int for its value. (e.g. base damage dealt)
	// Some functions will ignore the value.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Functions")
	TArray<FCardFunction> CardFunctionsAndValues;

	// To-Do: Explain this
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Functions")
	float Delay;

	// Use this to keep track of which items were added to a deck at the start of a fight due to an equipped item.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Functions")
	bool WasGeneratedByEquippedItem;
	
	// To-Do: Add card Traits

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Technical")
	ABaseClass_EntityInBattle* Owner;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Technical")
	ABaseClass_EntityInBattle* Controller;

	// Use this for spells that only have one target or set of targets.
	// For complicated spells, the target(s) must be found using code.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Functions")
	E_Card_SetTargets SimpleTargetsOverride;

	// Every single copy of a card should have a UniqueID.
	// These IDs should be generated when a deck is created or saved.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Technical")
	int32 UniqueID;

	// To-Do: List each zone index
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Technical")
	int32 ZoneIndex;

	FCard()
	{
		DisplayName = "Default";
		ManaCost = 1;
		Type = E_Card_Types::E_Spell;
		Elements.Add(E_Card_Elements::E_Fire);
		Art = nullptr;
		Description = "Blank.";
		Delay = 1.5f;
		WasGeneratedByEquippedItem = false;
		Owner = nullptr;
		Controller = nullptr;
		SimpleTargetsOverride = E_Card_SetTargets::E_None;
		UniqueID = -1;
		ZoneIndex = -1;
	}

	FORCEINLINE bool operator==(const FCard& OtherCard) const
	{
		if (DisplayName == OtherCard.DisplayName && 
			ManaCost == OtherCard.ManaCost &&
			Type == OtherCard.Type &&
			Elements == OtherCard.Elements) {
			return true;
			//&& Functions == OtherCard.Functions
		}
		
		return false;
	}
};



// ------------------------- The Stack
USTRUCT(BlueprintType)
struct LOSTWORLD_422_API FStackEntry
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FCard Card;

	// Use this as the 'key' to fetch the value.
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int CardFunctionIndex;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float DelayBeforeExecution;

	// To-Do: Explain this
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool RunWidgetFunction;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Technical")
	ABaseClass_EntityInBattle* Owner;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Technical")
	ABaseClass_EntityInBattle* Controller;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Technical")
	TArray<AActor*> Targets;

	FStackEntry(const FCard& InCard, const int InCardFunctionIndex, const float InDelayBeforeExecution, const bool InRunWidgetFunction,
		ABaseClass_EntityInBattle* InOwner = nullptr, ABaseClass_EntityInBattle* InController = nullptr,
		const TArray<AActor*>& InTargets = {})
	{
		Card = InCard;
		CardFunctionIndex = InCardFunctionIndex;
		DelayBeforeExecution = InDelayBeforeExecution;
		RunWidgetFunction = InRunWidgetFunction;
		Owner = InOwner;
		Controller = InController;
		Targets = InTargets;
	}

	FStackEntry()
	{
		CardFunctionIndex = 0;
		DelayBeforeExecution = 1.5f;
		RunWidgetFunction = true;
		Owner = nullptr;
		Controller = nullptr;
	}
};


class LOSTWORLD_422_API LostWorld_Variables
{
public:
	LostWorld_Variables();
	~LostWorld_Variables();

public:
	// Global variables
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UDataTable* CardsTable;
	
};
