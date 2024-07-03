#pragma once

#include "CoreMinimal.h"
#include "LostWorld_422GameModeBase.h"

#include "LostWorld_Variables.generated.h"


// To-Do: Give cards flavour text.
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

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Functions")
	TArray<FCardAbilitiesAndConditions> AbilitiesAndConditions;

	// To-Do: Explain this
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Functions")
	float Delay;

	// Use this to keep track of which items were added to a deck at the start of a fight due to an equipped item
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Functions")
	bool WasGeneratedByEquippedItem;
	
	// To-Do: Add card Traits

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
struct LOSTWORLD_422_API FCardOnStack
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FCardBase Card;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int CardFunctionIndex;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Delay;

	// To-Do: Explain this
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool RunWidgetFunction;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Technical")
	ABaseClass_EntityInBattle* Owner;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Technical")
	ABaseClass_EntityInBattle* Controller;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Technical")
	TArray<AActor*> Targets;

	FCardOnStack(const FCardBase& InCard, const int InCardFunctionIndex, const float InDelay, const bool InRunWidgetFunction,
		ABaseClass_EntityInBattle* InOwner = nullptr, ABaseClass_EntityInBattle* InController = nullptr,
		const TArray<AActor*>& InTargets = {})
	{
		Card = InCard;
		CardFunctionIndex = InCardFunctionIndex;
		Delay = InDelay;
		RunWidgetFunction = InRunWidgetFunction;
		Owner = InOwner;
		Controller = InController;
		Targets = InTargets;
	}

	FCardOnStack()
	{
		CardFunctionIndex = 0;
		Delay = 1.5f;
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
};
