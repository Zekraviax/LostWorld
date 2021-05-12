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
class AItemFunctions_BaseClass;


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
	E_NonElemental		UMETA(DisplayName = "Non-Elemental"),
	E_Fire				UMETA(DisplayName = "Fire"),
	E_Water				UMETA(DisplayName = "Water"),
	E_Air				UMETA(DisplayName = "Air"),
	E_Earth				UMETA(DisplayName = "Earth"),
	E_Light				UMETA(DisplayName = "Light"),
	E_Arcane			UMETA(DisplayName = "Arcane"),
	E_Cosmic			UMETA(DisplayName = "Cosmic"),
	E_Divine			UMETA(DisplayName = "Divine")
};

UENUM(BlueprintType)
enum class E_Card_DamageTypes : uint8
{
	E_Physical,
	E_Magical,
	E_Other
};

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


UENUM(BlueprintType)
enum class E_Card_SetTargets : uint8
{
	E_None,
	E_Self,
	E_AllEnemies,
	E_AnyTarget,
	E_CastTarget
};

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


// Items
UENUM(BlueprintType)
enum class E_Item_Types : uint8
{
	E_Equipment,
	E_Inventory,
};

UENUM(BlueprintType)
enum class E_Item_EquipSlots : uint8
{
	// Slots:
	// Head
	// 5 Left-ear Earrings/Piercings
	// 5 Right-ear Earrings/Piercings
	// Neck
	// Torso
	// Left Glove
	// Right Glove
	// 5 Left Hand Rings
	// 5 Right Hand Rings
	// Belt
	// Legs (Pant)
	// Left Shoe
	// Right Shoe
	// Left-hand Weapon
	// Right-hand Weapon
	E_NotEquippable,
	E_Head,
	E_LeftEar,
	E_RightEar,
	E_Neck,
	E_Torso,
	E_LeftHand,
	E_RightHand,
	E_LeftFinger,
	E_RightFinger,
	E_Waist,
	E_Legs,
	E_LeftFoot,
	E_RightFoot
};


// Level Rooms
UENUM(BlueprintType)
enum class E_Room_ExitDirections : uint8
{
	E_None,
	E_North,
	E_South,
	E_East,
	E_West
};

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

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Functions")
	float Delay;

	// Use this for spells that only have one target or set of targets.
	// For complicated spells, use a target variable for each ability.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Functions")
	E_Card_SetTargets SimpleTargetsOverride;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Technical")
	int32 UniqueID;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Technical")
	int32 ZoneIndex;

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


// ------------------------- Items and Item Functions
USTRUCT(BlueprintType)
struct LOSTWORLD_422_API F_Item_Base : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString DisplayName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Description;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<E_Item_EquipSlots> EquipSlots;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<AItemFunctions_BaseClass> Functions;

	F_Item_Base()
	{
		DisplayName = "Default";
		Description = "Default";
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

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool RunWidgetFunction;

	FStackEntry(FCardBase NewCard, float SetDelay, bool SetRunWidgetFunction)
	{
		Card = NewCard;
		Delay = SetDelay;
		RunWidgetFunction = SetRunWidgetFunction;
	}

	FStackEntry()
	{
		Delay = 1.5f;
		RunWidgetFunction = true;
	}
};


// ------------------------- Entities
USTRUCT(BlueprintType)
struct LOSTWORLD_422_API FEntity_GameOverOnDeath
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool GameOverOnDeath;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString GameOverMessage;

	FEntity_GameOverOnDeath()
	{
		GameOverOnDeath = false;
		GameOverMessage = "You died.";
	}
};


USTRUCT(BlueprintType)
struct LOSTWORLD_422_API FEntity_BaseStats
{
	GENERATED_BODY()

	// Increases damage dealt by physical attacks
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int Strength;

	// Increases maximum health
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int Constitution;

	// Increases damage dealt by magical attacks
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int Intelligence;

	// Increases healing dealt
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int Wisdom;

	// Increases position in the turn order
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int Dexterity;

	FEntity_BaseStats(int SetStrength, int SetConstitution, int SetIntelligence, int SetWisdom, int SetDexterity)
	{
		Strength = SetStrength;
		Constitution = SetConstitution;
		Intelligence = SetIntelligence;
		Wisdom = SetWisdom;
		Dexterity = SetDexterity;
	}

	// Default Constructor
	FEntity_BaseStats()
	{
		Strength = 1;
		Constitution = 1;
		Intelligence = 1;
		Wisdom = 1;
		Dexterity = 1;
	}
};


USTRUCT(BlueprintType)
struct LOSTWORLD_422_API FEntity_ElementalStats
{
	GENERATED_BODY()

	// Increases damage dealt by Earth attacks
	// Decreases damage taken by Earth attacks
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int Toughness;

	// Increases damage dealt by Divine attacks
	// Decreases damage taken by Divine attacks
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int Faith;

	FEntity_ElementalStats()
	{
		Toughness = 0;
		Faith = 0;
	}
};


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

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
	FEntity_BaseStats CoreStats;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Technical")
	bool IsPlayerControllable;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Technical")
	FEntity_GameOverOnDeath GameOverOnDeath;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cards")
	TArray<FCardBase> CurrentDeck;

	FEntityBase()
	{
		DisplayName = "Default";
		HealthValues = FIntVector2D(10, 10);
		ManaValues = FIntVector2D(10, 10);
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

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemy")
	float BaseExperiencePointsRate;

	F_NonPlayerEntity_DatabaseEntry()
	{
		DisplayName = "Default";
		MaximumHealthPoints = 10;
		MaximumManaPoints = 10;
		BaseExperiencePointsRate = 1;
	}
};


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

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemies")
	TArray<FVector2D> PossibleSpawnLocationsRelativeToPlayer;

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


// Exits
USTRUCT(BlueprintType)
struct LOSTWORLD_422_API F_LevelRoom_Exits : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Display")
	FString ExitName;

	F_LevelRoom_Exits()
	{
		ExitName = "Default";
	}
};


// Miscellaneous Encounters
USTRUCT(BlueprintType)
struct LOSTWORLD_422_API F_LevelRoom_MiscellaneousEncounters : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Display")
	FString EncounterName;

	F_LevelRoom_MiscellaneousEncounters()
	{
		EncounterName = "Default";
	}
};


// Room Encounter
USTRUCT(BlueprintType)
struct LOSTWORLD_422_API F_LevelRoom_Encounter : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Display")
	FString DisplayName;

	// Used to remove encounters from the list when the player defeats them
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gameplay")
	bool CurrentlyActiveEncounter;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gameplay")
	FDataTableRowHandle EncounterListEntry;

	F_LevelRoom_Encounter()
	{
		DisplayName = "Default";
		CurrentlyActiveEncounter = false;
	}

	F_LevelRoom_Encounter(FString NewName, bool IsActiveEncounter, FDataTableRowHandle EnemyEncounterDataTableRow)
	{
		DisplayName = NewName;
		CurrentlyActiveEncounter = IsActiveEncounter;
		EncounterListEntry = EnemyEncounterDataTableRow;
	}
};


// Room Exit
USTRUCT(BlueprintType)
struct LOSTWORLD_422_API F_LevelRoom_Exit
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Display")
	FString DisplayName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Display")
	E_Room_ExitDirections ExitDirection;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gameplay")
	ABaseClass_LevelRoom* RoomReference;

	F_LevelRoom_Exit()
	{
		DisplayName = "Default";
		ExitDirection = E_Room_ExitDirections::E_None;
	}
};


// Level Data
USTRUCT(BlueprintType)
struct LOSTWORLD_422_API F_Level_Data
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Display")
	FString DisplayName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Rooms")
	int MinimumRoomCount;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Rooms")
	int MaximumRoomCount;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Rooms")
	int CurrentRoomCount;

	F_Level_Data()
	{
		DisplayName = "Level";
		MinimumRoomCount = 6;
		MaximumRoomCount = 10;
		CurrentRoomCount = 0;
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
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "References")
	UDataTable* CardDataTableRef;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "References")
	ABaseClass_CardFunctionsLibrary* CardFunctionLibraryReference;

//// ------------------------- Classes
//	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "References")
//	TSubclassOf<class UBaseClass_Widget_ZoneSearch> ZoneSearchWidget_Class;
};