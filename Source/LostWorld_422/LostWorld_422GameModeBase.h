#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"

#include "Engine/UserDefinedStruct.h"
#include "Engine/DataTable.h"

#include "LostWorld_422GameModeBase.generated.h"

// Forward Declarations
class ABaseClass_EntityInBattle;
class ABaseClass_CardFunctionsLibrary;
class ABaseClass_LevelRoom;
class UBaseClass_Widget_ZoneSearch;
class ACardAbilityActor_BaseClass;


// Enums
//--------------------------------------------------

// Card Base Variables
UENUM(BlueprintType)
enum class E_Card_Types : uint8
{
	E_Summon			UMETA(DisplayName = "Summon"),
	E_Spell				UMETA(DisplayName = "Spell"),
	E_Technique			UMETA(DisplayName = "Technique"),
};

UENUM(BlueprintType)
enum class E_Card_Elements : uint8
{
	E_Fire				UMETA(DisplayName = "Fire"),
	E_Water				UMETA(DisplayName = "Water"),
	E_Air				UMETA(DisplayName = "Air"),
	E_Earth				UMETA(DisplayName = "Earth"),
	E_Light				UMETA(DisplayName = "Light"),
	E_Arcane			UMETA(DisplayName = "Arcane"),
	E_Cosmic			UMETA(DisplayName = "Cosmic"),
	E_Divine			UMETA(DisplayName = "Divine")
};

// Card Abilities
//UENUM(BlueprintType)
//enum class E_Card_PassiveAbilities : uint8
//{
//
//};
//
//UENUM(BlueprintType)
//enum class E_Card_TriggeredAbilities : uint8
//{
//
//};
//
//UENUM(BlueprintType)
//enum class E_Card_ActivatedAbilities : uint8
//{
//	E_A_ChangeZone			UMETA(DisplayName = "A: Change Zone"),
//};

// Card Passive, Triggered, and Active Functions
//UENUM(BlueprintType)
//enum class E_Card_Abilities : uint8
//{
//	E_Default					UMETA(DisplayName = "Default"),
//	E_A_DrawCards				UMETA(DisplayName = "Active: Draw Cards"),
//	E_A_ChangeZone				UMETA(DisplayName = "Active: Change Zone"),
//};

UENUM(BlueprintType)
enum class E_Card_AbilityConditions : uint8
{
	E_Default								UMETA(DisplayName = "Default"),
// Basic Functions
	E_ManaCost								UMETA(DisplayName = "Mana Cost: X"),
	E_Damage								UMETA(DisplayName = "Damage: X"),
	E_NumberOfCards							UMETA(DisplayName = "Number of Cards: X"),
// Keywords
	E_Repeat								UMETA(DisplayName = "Repeat: X"),
// Alternate Card Cost
	E_CastingCost_X							UMETA(DisplayName = "Casting Cost: X"),
// Target Overrides
	//E_ValidTargets_Monsters				UMETA(DisplayName = "ValidTargets: Monsters"),
	E_TargetOverride_SingleEnemy_Random		UMETA(DisplayName = "Target Override: Random Single Enemy"),
// Alter Other Abilities' Values
	E_NextAbility_CastingCost				UMETA(DisplayName = "Next Ability Equals Casting Cost"),
};

//UENUM(BlueprintType)
//enum class E_Card_Functions : uint8
//{
//	E_Nothing									UMETA(DisplayName = "Nothing"),
//	E_Deal_X_Damage								UMETA(DisplayName = "Deal X Damage"),
//	E_Draw_X_Cards								UMETA(DisplayName = "Draw X Cards"),
//	E_Add_Status_Effect							UMETA(DisplayName = "Add Status Effect To Targets"),
//	E_Change_Current_Mana						UMETA(DisplayName = "Change Target's Current Mana"),
//	E_Change_Maximum_Mana						UMETA(DisplayName = "Change Target's Maximum Mana"),
//	E_Change_Current_Health						UMETA(DisplayName = "Change Target's Current Health"),
//	E_Change_Maximum_Health						UMETA(DisplayName = "Change Target's Maximum Health"),
//	E_Create_Card								UMETA(DisplayName = "Create A Card"),
//	E_Search_Zone								UMETA(DisplayName = "Search Zone (Hand/Deck/Graveyard)"),
//	E_Modal_Choose_X							UMETA(DisplayName = "Choose-X Effect"),
//	E_Copy_Card_Function						UMETA(DisplayName = "Copy Card Function"),
//};

//UENUM(BlueprintType)
//enum class E_Card_Rules : uint8
//{
//	// Card Types
//	E_Rule_CardType_Spell						UMETA(DisplayName = "Card Type: Spells"),
//	E_Rule_CartType_Summon						UMETA(DisplayName = "Card Type: Summons"),
//	E_Rule_CardType_Technique					UMETA(DisplayName = "Card Type: Techniques"),
//	E_Rule_CardType_All							UMETA(DisplayName = "Card Type: All"),
//	// Card Zones
//	E_Rule_Zone_Hand							UMETA(DisplayName = "Zone: Hand"),
//	E_Rule_Zone_Deck							UMETA(DisplayName = "Zone: Deck"),
//	E_Rule_Zone_Graveyard						UMETA(DisplayName = "Zone: Graveyard"),
//	// Set Numbers
//	E_Rule_FixedInteger_Zero					UMETA(DisplayName = "Fixed Integer: 0"),
//	E_Rule_FixedInteger_One						UMETA(DisplayName = "Fixed Integer: 1"),
//	E_Rule_FixedInteger_Two						UMETA(DisplayName = "Fixed Integer: 2"),
//	E_Rule_FixedInteger_Three					UMETA(DisplayName = "Fixed Integer: 3"),
//	E_Rule_FixedInteger_Four					UMETA(DisplayName = "Fixed Integer: 4"),
//	E_Rule_FixedInteger_Five					UMETA(DisplayName = "Fixed Integer: 5"),
//	E_Rule_FixedInteger_Six						UMETA(DisplayName = "Fixed Integer: 6"),
//	E_Rule_FixedInteger_Seven					UMETA(DisplayName = "Fixed Integer: 7"),
//	E_Rule_FixedInteger_Eight					UMETA(DisplayName = "Fixed Integer: 8"),
//	E_Rule_FixedInteger_Nine					UMETA(DisplayName = "Fixed Integer: 9"),
//	E_Rule_FixedInteger_Ten						UMETA(DisplayName = "Fixed Integer: 10"),
//	// Variable Numbers
//	E_Rule_VariableInteger_Current_Power		UMETA(DisplayName = "Variable Integer: Current Power"),
//	E_Rule_VariableInteger_Random_Number		UMETA(DisplayName = "Variable Integer: Random Number (0 - 10)"),
//	E_Rule_VariableInteger_Card_Cost			UMETA(DisplayName = "Variable Integer: Casting Cost"),
//	// Choose-a-Card Functions
//	E_Rule_ChooseCards_Draw						UMETA(DisplayName = "Miscellaneous: Draw Chosen Card"),
//	E_Rule_ChooseCards_Discard					UMETA(DisplayName = "Miscellaneous: Discard Chosen Card"),
//	// Targets
//	E_Rule_Target_Self							UMETA(DisplayName = "Target: Self"),
//	E_Rule_Target_CastTarget					UMETA(DisplayName = "Target: Cast Target"),
//	E_Rule_Target_RandomEnemy					UMETA(DisplayName = "Target: Random Enemy"),
//	E_Rule_Target_AllEnemies					UMETA(DisplayName = "Target: All Enemies"),
//	// The Stack
//	E_Rule_Stack_InterruptTheStack				UMETA(DisplayName = "The Stack: Interrupt The Stack"),
//	//Overrides
//	E_Rule_Override_CastingCostX				UMETA(DisplayName = "Override - Casting Cost: X Cost")
////};
//
//UENUM(BlueprintType)
//enum class E_Card_SetFunctions : uint8
//{
//	E_GunDown,
//	E_Shockwave,
//	E_SuddenInspiration,
//	E_EssenceRecycling,
//	E_Recall,
//	E_RollingQuake
//};

UENUM(BlueprintType)
enum class E_Card_SetTargets : uint8
{
	E_None,
	E_Self,
	E_AllEnemies,
	E_AnyTarget,
	E_CastTarget
};

//UENUM(BlueprintType)
//enum class E_Card_UserSelectModes : uint8
//{
//	E_Cast				UMETA(DisplayName = "Cast From Hand"),
//	E_Select			UMETA(DisplayName = "Select From CardSelector Widget"),
//};
//
//UENUM(BlueprintType)
//enum class E_Card_UserSelectFunctions : uint8
//{
//	E_Draw_Card,
//	E_Discard_Card,
//};
//
// Modes for casting on a target, not specifically the spells' target
UENUM(BlueprintType)
enum class E_Card_TargetModes : uint8
{
	E_Self,
	E_SingleEntity,
	E_AllEntities,
	E_SingleEnemy,
	E_AllEnemies,
};

UENUM(BlueprintType)
enum class E_Card_Zones : uint8
{
	E_Hand,
	E_Deck,
	E_Graveyard
};

// Level Rooms
UENUM(BlueprintType)
enum class E_LevelRoom_EncounterTypes : uint8
{
	E_Enemy,
	E_Treasure,
	E_Conversation,
};

// Structs
//--------------------------------------------------

// ------------------------- Base
USTRUCT(BlueprintType)
struct LOSTWORLD_422_API FIntVector2D
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 X_Value;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 Y_Value;

	// Default Constructor
	FIntVector2D() {}

	FIntVector2D(int32 SetX, int32 SetY)
	{
		X_Value = SetX;
		Y_Value = SetY;
	}
};

// ------------------------- Cards and Card Functions
USTRUCT(BlueprintType)
struct LOSTWORLD_422_API FCardAbilitiesAndConditions
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<ACardAbilityActor_BaseClass> Ability;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TMap<E_Card_AbilityConditions, int> AbilityConditions;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString AbilityDescription;

	FCardAbilitiesAndConditions()
	{

	}
};

USTRUCT(BlueprintType)
struct LOSTWORLD_422_API FCardBase : public FTableRowBase
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

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Functions")
	TArray<FCardAbilitiesAndConditions> AbilitiesAndConditions;

	// Use this for spells that only have one target or set of targets.
	// For complicated spells, use a target variable for each ability.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Functions")
	E_Card_SetTargets SimpleTargetsOverride;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Technical")
	int32 UniqueID;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Technical")
	int32 ZoneIndex;

	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Technical")
	//E_Card_UserSelectModes CurrentSelectMode;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Technical")
	ABaseClass_EntityInBattle* Owner;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Technical")
	ABaseClass_EntityInBattle* Controller;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Technical")
	TArray<ABaseClass_EntityInBattle*> CurrentTargets;

	FCardBase()
	{
		DisplayName = "Default";
		ManaCost = 1;
		Type = E_Card_Types::E_Spell;
		Elements.Add(E_Card_Elements::E_Fire);
		Art = NULL;
		Description = "Blank.";
		UniqueID = -1;
		ZoneIndex = -1;
		//CurrentSelectMode = E_Card_UserSelectModes::E_Cast;
		Owner = NULL;
		Controller = NULL;
	}

	FORCEINLINE bool operator==(const FCardBase& OtherCard) const
	{
		if (DisplayName == OtherCard.DisplayName && 
			ManaCost == OtherCard.ManaCost &&
			Type == OtherCard.Type &&
			Elements == OtherCard.Elements) {
			return true;
			//&& Functions == OtherCard.Functions
		}
		else {
			return false;
		}
	}
};

// ------------------------- The Stack
USTRUCT(BlueprintType)
struct LOSTWORLD_422_API FStackEntry
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FCardBase Card;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Delay;

	FStackEntry(FCardBase NewCard, float SetDelay)
	{
		Card = NewCard;
		Delay = SetDelay;
	}

	FStackEntry()
	{

	}
};

// ------------------------- Entities
USTRUCT(BlueprintType)
struct LOSTWORLD_422_API FEntityBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Base")
	FString DisplayName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
	FIntVector2D HealthValues;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
	FIntVector2D ManaValues;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Technical")
	bool IsPlayerControllable;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cards")
	TArray<FCardBase> CurrentDeck;

	FEntityBase()
	{
		DisplayName = "Default";
		HealthValues = FIntVector2D(10, 10);
		ManaValues = FIntVector2D(5, 5);
		IsPlayerControllable = false;
	}
};

// Enemy Database
USTRUCT(BlueprintType)
struct LOSTWORLD_422_API F_NonPlayerEntity_DatabaseEntry : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Base")
	FString DisplayName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
	int32 MaximumHealthPoints;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
	int32 MaximumManaPoints;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cards")
	TArray<FDataTableRowHandle> Cards;

	F_NonPlayerEntity_DatabaseEntry()
	{
		DisplayName = "Default";
		MaximumHealthPoints = 10;
		MaximumManaPoints = 5;
	}
};

// Summon Database
//USTRUCT(BlueprintType)
//struct LOSTWORLD_422_API F_Summon_DatabaseEntry
//{
//	GENERATED_BODY()
//
//	F_Summon_DatabaseEntry()
//	{
//
//	}
//};

// ------------------------- Level

// Room Enemy Formations
USTRUCT(BlueprintType)
struct LOSTWORLD_422_API F_LevelRoom_EnemyFormation : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Display")
	FString FormationName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemies")
	TMap<FVector2D, FDataTableRowHandle> EnemiesMap;

	F_LevelRoom_EnemyFormation()
	{
		FormationName = "Default";
	}
};

// Treasure Boxes Combinations
USTRUCT(BlueprintType)
struct LOSTWORLD_422_API F_LevelRoom_TreasureBoxCombination : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Display")
	FString CombinationName;

	F_LevelRoom_TreasureBoxCombination()
	{
		CombinationName = "Default";
	}
};

// Level Room
USTRUCT(BlueprintType)
struct LOSTWORLD_422_API F_Level_Room : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Display")
	FString DisplayName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gameplay")
	bool CurrentlyActiveEncounter;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gameplay")
	FDataTableRowHandle EncounterListEntry;

	F_Level_Room()
	{
		DisplayName = "Default";
		CurrentlyActiveEncounter = false;
	}
};

// ------------------------- Default
USTRUCT()
struct LOSTWORLD_422_API FTestStruct
{
	GENERATED_BODY();

};


UCLASS()
class LOSTWORLD_422_API ALostWorld_422GameModeBase : public AGameModeBase
{
	GENERATED_BODY()
	
public:
// Base Variables
// --------------------------------------------------

// ------------------------- References
	// Card Data Table Reference
	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data - Technical")
	//FDataTableRowHandle CardDataTableRowRef;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "References")
	UDataTable* CardDataTableRef;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "References")
	ABaseClass_CardFunctionsLibrary* CardFunctionLibraryReference;

	// Player
	//UPROPERTY()
	//ABaseClass_EntityInBattle* Player;

// ------------------------- Classes
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "References")
	TSubclassOf<class UBaseClass_Widget_ZoneSearch> ZoneSearchWidget_Class;
};