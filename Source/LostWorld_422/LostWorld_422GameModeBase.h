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

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Technical")
		FEntity_GameOverOnDeath GameOverOnDeath;

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

// Room encounter
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
};

// Room exit
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

// ------------------------- Classes
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "References")
	TSubclassOf<class UBaseClass_Widget_ZoneSearch> ZoneSearchWidget_Class;
};