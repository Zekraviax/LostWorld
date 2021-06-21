#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"

#include "Engine/UserDefinedStruct.h"
#include "Engine/DataTable.h"
#include "ItemFunctions_BaseClass.h"

#include "LostWorld_422GameModeBase.generated.h"

// Forward Declarations
class ABaseClass_EntityInBattle;
class ABaseClass_CardFunctionsLibrary;
class ABaseClass_LevelRoom;
class UBaseClass_Widget_ZoneSearch;
class ACardAbilityActor_BaseClass;
class AStatusFunctions_BaseClass;


// Enums
//--------------------------------------------------


// Card Base Variables
UENUM(BlueprintType)
enum class E_Card_Types : uint8
{
	E_Summon			UMETA(DisplayName = "Summon"),
	E_Spell				UMETA(DisplayName = "Spell"),
	E_Technique			UMETA(DisplayName = "Technique"),
	E_Command			UMETA(DisplayName = "Command"),
};


UENUM(BlueprintType)
enum class E_Card_Subypes : uint8
{
	E_Miracle			UMETA(DisplayName = "Miracle"),
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
enum class E_Card_Traits : uint8
{
	E_CastsWhenDrawn		UMETA(DisplayName = "Auto-Cast"),
	E_Lifesteal				UMETA(DisplayName = "Life Drain"),
};



UENUM(BlueprintType)
enum class E_Card_DamageTypes : uint8
{
	E_Physical,
	E_Magical,
	E_LifeLoss,
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


UENUM(BlueprintType)
enum class E_Card_Zones : uint8
{
	E_Hand,
	E_Deck,
	E_Graveyard,
	E_Void,
};


UENUM(BlueprintType)
enum class E_Entity_Traits : uint8
{
	E_CastsWhenDrawn		UMETA(DisplayName = "Auto-Cast")
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
	// Head									(Helmets, Hats)
	// 5 Left-ear Earrings/Piercings		(Earrings, Piercings, Industrial Bars)
	// 5 Right-ear Earrings/Piercings
	// Neck									(Capes, Amulets, Chokers, Cloaks)
	// Torso								(Shirts, Breastplates, Robes, Corsets)
	// Left Glove							(Gloves)
	// Right Glove
	// 5 Left Hand Rings					(Rings)
	// 5 Right Hand Rings
	// Belt									(Belts)
	// Legs (Pant)							(Pants, Greaves)
	// Left Shoe							(Shoes, Boots)
	// Right Shoe
	// Left-hand Weapon						(Swords, Axes, Staves, Bows, Maces, Rods, Wands, )
	// Right-hand Weapon
	E_NotEquippable			UMETA(DisplayName = "N/A"),
	E_Head					UMETA(DisplayName = "Head"),
	E_LeftEar				UMETA(DisplayName = "Left Ear"),
	E_RightEar				UMETA(DisplayName = "Right Ear"),
	E_Neck					UMETA(DisplayName = "Neck"),
	E_Torso					UMETA(DisplayName = "Torso"),
	E_LeftHand				UMETA(DisplayName = "Left Hand"),
	E_RightHand				UMETA(DisplayName = "Right Hand"),
	E_LeftFinger			UMETA(DisplayName = "Left Finger"),
	E_RightFinger			UMETA(DisplayName = "Right Finger"),
	E_Waist					UMETA(DisplayName = "Waist"),
	E_Legs					UMETA(DisplayName = "Legs"),
	E_LeftFoot				UMETA(DisplayName = "Left Foot"),
	E_RightFoot				UMETA(DisplayName = "Right Foot"),
	E_LeftHandWeapon		UMETA(DisplayName = "Left-Hand Weapon"),
	E_RightHandWeapon		UMETA(DisplayName = "Right-Hand Weapon"),
};


// Status Effects
UENUM(BlueprintType)
enum class E_StatusEffect_TickDownConditions : uint8
{
	E_None,
	E_BeginningOfAffectedEntityTurn,
	E_BeginningOfAnyEntityTurn,
	E_CastCard,
};


// A general categorization for how the game should treat a status effect
UENUM(BlueprintType)
enum class E_StatusEffect_Considerations : uint8
{
	E_Positive,
	E_Negative,
	E_Mixed,
	E_NotApplicable,
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

	//UPROPERTY(EditAnywhere, BlueprintReadWrite)
	//TMap<E_Card_AbilityConditions, int> AbilityConditions;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	E_Card_DamageTypes DamageType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString AbilityDescription;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 BaseDamage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 CalculatedDamage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 BaseHealing;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 CalculatedHealing;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 BaseDraw;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 CalculatedDraw;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 BaseBarrier;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 CalculatedBarrier;

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

	// Traits

	// Use this for spells that only have one target or set of targets.
	// For complicated spells, the target(s) must be found using code.
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
	TArray<AActor*> CurrentTargets;

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


	FORCEINLINE bool operator==(const F_Item_Base& OtherItem) const
	{
		if (DisplayName == OtherItem.DisplayName &&
			Description == OtherItem.Description &&
			EquipSlots == OtherItem.EquipSlots &&
			Functions == OtherItem.Functions) {
			return true;
		} else {
			return false;
		}
	}
};


USTRUCT(BlueprintType)
struct LOSTWORLD_422_API F_StatusEffect_Base : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString DisplayName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Description;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UTexture2D* Icon;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FIntVector2D CounterValues;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	E_StatusEffect_TickDownConditions TickDownCondition;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	E_StatusEffect_Considerations Consideration;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<AStatusFunctions_BaseClass> StatusFunctions;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Technical Variables")
	ABaseClass_EntityInBattle* Source;

	F_StatusEffect_Base()
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

	// Increases damage dealt by Fire attacks
	// Decreases damage taken by Fire attacks
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int Fervor;

	// Flexibility?

	// Increases damage dealt by Air attacks
	// Decreases damage taken by Air attacks
	int Exuberance;

	// Increases damage dealt by Earth attacks
	// Decreases damage taken by Earth attacks
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int Toughness;

	// Dynamism

	// Mysteriousness?

	// Increases damage dealt by Light attacks
	// Decreases damage taken by Light attacks
	int Radiance;

	// Increases damage dealt by Divine attacks
	// Decreases damage taken by Divine attacks
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int Loyalty;

	FEntity_ElementalStats()
	{
		Fervor = 0;
		Exuberance = 0;
		Toughness = 0;
		Radiance = 0;
		Loyalty = 0;
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
	int Barrier;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
	int HealthRegenPerTurn;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
	int ManaRegenPerTurn;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
	int HandSize;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
	FEntity_BaseStats CoreStats;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Technical")
	bool IsPlayer;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Technical")
	bool IsPlayerControllable;

	// Traits

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Technical")
	FEntity_GameOverOnDeath GameOverOnDeath;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cards")
	TArray<FCardBase> CurrentDeck;

	FEntityBase()
	{
		DisplayName = "Default";
		HealthRegenPerTurn = 0;
		ManaRegenPerTurn = 3;
		HandSize = 7;
		HealthValues = FIntVector2D(10, 10);
		ManaValues = FIntVector2D(10, 10);
		IsPlayerControllable = false;
		IsPlayer = false;
	}
};


// Enemy Database
USTRUCT(BlueprintType)
struct LOSTWORLD_422_API F_NonPlayerEntity_DatabaseEntry : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Base")
	FEntityBase EntityBaseData;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Base")
	FString Description;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Base")
	UTexture2D* Image;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cards")
	TArray<FDataTableRowHandle> Cards;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemy")
	FEntity_BaseStats MinimumBaseStats;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemy")
	FEntity_BaseStats MaximumBaseStats;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemy")
	float BaseExperiencePoints;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemy")
	float BaseMoney;

	F_NonPlayerEntity_DatabaseEntry()
	{
		Description = "Default";
		BaseExperiencePoints = 1;
		BaseMoney = 1;
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