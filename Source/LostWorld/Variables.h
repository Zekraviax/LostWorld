#pragma once


#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "Variables.generated.h"


// Forward declarations
class AActorEntityBase;
class AActorGridTile;


// ---------------------------------------- Constants ---------------------------------------- //
// The size of a GridTile in Unreal Engine units.
//int GlobalGridTileWidth = 100;
//int GlobalGridTileLength = 100;

// The maximum number of entities that can be added to the turn queue.
//int TurnQueueMaxSize = 15;


// ---------------------------------------- Enums ---------------------------------------- //

// -------------------------------- Levels
UENUM(BlueprintType)
enum class EFloorLayouts : uint8
{
	FourSquares
};


UENUM(BlueprintType)
enum class EEncounterTypes : uint8
{
	None,
	Enemy
};


// -------------------------------- Cards
UENUM(BlueprintType)
enum class ECardTypes : uint8
{
	Spell,
	Summon,
	Technique,
	Command,
	Shout
};


UENUM(BlueprintType)
enum class ECardElements : uint8
{
	Fire,
	Water,
	Air,
	Earth,
	Light,
	Cosmic,
	Arcane,
	Divine,
	NonElemental
};


UENUM(BlueprintType)
enum class ECardTargets : uint8
{
	None,
	Self,
	OneEnemy,
	OneRandomEnemy,
	AnyOneEntity,
	AllAllies,
	AllEnemies,
};


/**Modifiers can be positive (such as cost reductions); negative (such as blocking healing); or mixed.

Modifiers can also have different 'durations' (durations should be inherent to the modifier?)

List of 'durations':
-  Permanent.
- Until end of battle.
- Until end of turn.

Modifiers can be applied at different times:
- As soon as the modifier is applied to the card. (Should also be applied when the game is launched as well?)
- At the start of battles/when the cards are copied into the draw pile from the deck.
- Each time the card is drawn.
- After each time the card is played.
- When the player wins a battle.
- On damage dealt.
- After damage calculations but before damage is dealt.*/
UENUM(BlueprintType)
enum class ECardModifiers : uint8
{
	// Positive ----------------
	TotalCostMinusOne,
	TotalDamagePlusOne,
	// Negative ----------------
	// This one overrides any damage the card would deal to 1.
	DamageSetToOne				UMETA(DisplayName="Damage One"),
	// Mixed ----------------
	// Increases cost, damage, and healing.
	CostUpDamageUpHealingUp,
	Cantrip,	// Cost plus 1 and draws a card when played.
};


UENUM(BlueprintType)
enum class ECardModifierTimingTriggers : uint8
{
	OnModifierApplied,
	StartOfBattle,
	StartOfOwnersTurn,
	OnDrawn,
	OnDamageDealt,
	OnBattleVictory
};


/** Keywords are special behaviours.

Keywords can be inherent to a card, or applied to cards.

Keywords can be applied to any type of card; spells, equipment, etc,
and might behave differently depending on the card it's attached to.*/
UENUM(BlueprintType)
enum class ECardKeywords : uint8
{
	// This permanently removes a card from the players' collection/inventory.
	// Spells: Permanent removal when the player plays it.
	// Equipment: ?
	//Destroy,

	// Spells: The player can only have one copy in their deck.
	// Equipment: The player can only have one total in their inventory OR equipped.
	Unique,
	// Spells: Always draw this card at the start of battles.
	// Equipment: N/A
	Ace,
	// Spells: Cannot be played.
	// Equipment: Any benefits or downsides given by the equipment don't apply while disabled.
	Disabled,
	// Spells: Exiled to your void at the end of every turn, if it isn't already in the void.
	// Equipment: N/A
	Ephemeral,
	// Spells: If this card is in your opening hand at the start of battle, it is automagically played for free.
	// Equipment: if this item is equipped at the start of a battle and has an active or triggered effect, the effect
	// is automagically activated at no cost.
	Auto,
};


// To-Do: Write down how to differentiate between Functions and Modifiers.
UENUM(BlueprintType)
enum class ECardFunctions : uint8
{
	// -------- Placeholder -------- //
	None,
	// -------- Passively modified cards while they're in the hand -------- //
	CostsAllMana,
	CostsHp,
	// -------- Passively modified cards while they're in any zone except the hand -------- //
	CanCastFromGraveyard,
	CanCastFromDeck,
	CanCastFromExile,
	// -------- Deletes cards when certain conditions are met -------- //
	Temporary,	// At end of battle.
	Ephemeral,	// At the end of every turn and when played.
	SingleUse,	// When played.
	// -------- Specific to one card -------- //
	TestFunctionOne,
	TestFunctionTwo,
	TestFunctionThree,
	TestFunctionFour,
	PoisonDart,
	ArmourBreaker,
	HyperBeam,
	TestFunctionFive,
	TestFunctionSix,
	HowlOfCommand,
	EnergyAllAround,
	PinpointThrust,
	CallForFriends,
	Inflame,
	InfectedBite,
	Vomit,
	Demi,
	HammerBlow,
	CreateEphemeralTrainOfThought,
	// -------- Generic functions -------- //
	DealDamageToOneTargets,	// To-Do: Fix this typo.
	CasterDrawsOneCard,
	InflictToughnessDown,
	DrawOneCardThenBottomOneCard,
	// -------- Modifier functions -------- //
	// We can use modifier functions to store values,
	// so that we can create mods that stack or vary over time.
	CastCount, // How many times this card has been played in a single battle.
	// -------- Other -------- //
	AddTotalCostStackEntries, // Used for X cost cards. X is the amount of MP spent to cast the card.
	// When this comes -after- another function, wait for that function to finish executing
	// before executing the next function. Currently, this one ignores targeting because it's player-exclusive.
	WaitForPreviousFunctionPlayerInput,	
};


// -------------------------------- Player
UENUM(BlueprintType)
enum class EPlayerControlModes : uint8
{
	None,
	// Out-of-battle
	LevelExploration,
	DeckEditor,
	// In battle
	Battle,
	TargetSelectionSingleEntity,
	BottomOneCardInHand,
};


// -------------------------------- Miscellaneous
UENUM(BlueprintType)
enum class EStatusEffectFunctions : uint8
{
	Poison,
	IronShell,
	StrengthUp,
	Howl,
	Adrenaline,
	MutantAura,
	Sap, // Reduces all base stats by 1.
	Bleeding,
	ToughnessDown,
	Stun,
};


UENUM(BlueprintType)
enum class ETimingTriggers : uint8
{
	//
	None,
	StartOfBattle,
	// The 'StartOf' triggers are mutually exclusive (except for StartOfBattle).
	StartOfAffectedEntitiesTurn,
	StartOfEveryTurn,
	// The 'EndOf' triggers are mutually exclusive.
	EndOfAffectedEntitiesTurn,
	EndOfEveryTurn,
	OnStatusEffectApplied,
	WhenStatusEffectTriggers,
};


UENUM(BlueprintType)
enum class EDamageTypes : uint8
{
	Physical,
	Magical,
	Pure
};


UENUM(BlueprintType)
enum class ETeams : uint8
{
	PlayerTeam,
	EnemyTeam1,
	EnemyTeam2
};


UENUM(BlueprintType)
enum class EEquipSlots : uint8
{
	// Slots:
	// Head									(Helmets, Hats)
	// Five Left-ear Earrings/Piercings		(Earrings, Piercings, Industrial Bars)
	// Five Right-ear Earrings/Piercings
	// Neck									(Capes, Amulets, Chokers, Cloaks)
	// Torso								(Shirts, Breastplates, Robes, Corsets)
	// Left Hand							(Gloves)
	// Right Hand
	// Five Left Hand Fingers				(Rings)
	// Five Right Hand Fingers
	// Waist								(Belts)
	// Legs (Pant)							(Pants, Greaves)
	// Left Shoe							(Shoes, Boots)
	// Right Shoe
	// Left-hand Weapon						(Swords, Axes, Staves, Bows, Maces, Rods, Wands, etc.)
	// Right-hand Weapon
	None						UMETA(DisplayName = "N/A"),
	Head						UMETA(DisplayName = "Head"),
	LeftEar						UMETA(DisplayName = "Left Ear"),
	RightEar					UMETA(DisplayName = "Right Ear"),
	Neck						UMETA(DisplayName = "Neck"),
	Torso						UMETA(DisplayName = "Torso"),
	LeftHand					UMETA(DisplayName = "Left Hand"),
	RightHand					UMETA(DisplayName = "Right Hand"),
	LeftFinger					UMETA(DisplayName = "Left Finger"),
	RightFinger					UMETA(DisplayName = "Right Finger"),
	Waist						UMETA(DisplayName = "Waist"),
	Legs						UMETA(DisplayName = "Legs"),
	LeftFoot					UMETA(DisplayName = "Left Foot"),
	RightFoot					UMETA(DisplayName = "Right Foot"),
	LeftHandWeapon				UMETA(DisplayName = "Left-Hand Weapon"),
	RightHandWeapon				UMETA(DisplayName = "Right-Hand Weapon"),
};


UENUM(BlueprintType)
enum class EEntityTypes : uint8
{
	// Extensive list of entities.
	// Main types:
	Player,
	Enemy,
	SummonedEntity,
	Boss,
	// Enemy exclusive types
	TestEnemyOne,
	TestEnemyTwo,
	WolfPack,
	WolfPackAlpha,
	Hogbot,
	MegaHogbot,
	RabidRat,
	// Boss types
	IronShellAutomation,
};


/** Like keywords, but for entities.*/
UENUM(BlueprintType)
enum class EEntityTraits : uint8
{
	Passive, // Entity cannot play cards, and does not get to take turns.
	Sturdy, // Only takes 1 damage per stack entry.
};


// ---------------------------------------- Structs ---------------------------------------- //
USTRUCT(BlueprintType)
struct LOSTWORLD_API FIntVector2D
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int X;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int Y;

	// Default constructor
	FIntVector2D()
	{
		X = 0;
		Y = 0;
	}

	// Creates and initializes a new instance with the specified coordinates.
	FIntVector2D(int32 InX, int32 InY)
	{
		X = InX;
		Y = InY;
	}

	// Comparator
	FORCEINLINE bool operator==(const FIntVector2D& OtherStruct) const
	{
		return X == OtherStruct.X &&
			Y == OtherStruct.Y;
	}
};

/** To-Do: Create a terminology json that handles the following (amongst other things):
- Translates enums into proper english.
- Provides descriptions for terminology.
- Provides alternate words for terminology.
- Display icons for any terminology that has them (e.g. the Eight Elements.)*/
USTRUCT(BlueprintType)
struct LOSTWORLD_API FTerminology : public FTableRowBase
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString EnumAsString;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString DisplayName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString ShortDescription;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString LongDescription;
};


USTRUCT(BlueprintType)
struct LOSTWORLD_API FStatusEffect : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString DisplayName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Description;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EStatusEffectFunctions StatusEffect;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<ETimingTriggers> TimingTriggers;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<ETimingTriggers> DecrementStackTriggers;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int CurrentStackCount;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int MaximumStackCount;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool VisibleToPlayer;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool BlockedByBarrier;

	FStatusEffect()
	{
		DisplayName = "Test";
		Description = "This is a test description.";
		StatusEffect = EStatusEffectFunctions::Poison;
		TimingTriggers = { ETimingTriggers::StartOfBattle };
		CurrentStackCount = 1;
		MaximumStackCount = 9999999;
		VisibleToPlayer = true;
		BlockedByBarrier = true;
	}
};


// -------------------------------- Cards
USTRUCT(BlueprintType)
struct LOSTWORLD_API FCard : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Base)
	FString DisplayName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Base)
	int BaseCost; // Use a different variable for the total cost (the cost after any changes to the base cost.)

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Base)
	TArray<ECardTypes> CardTypes; // Card types should be added to the array in the order that they're written on the card.

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Base)
	TArray<ECardElements> CardElements; // Elements should be added to the array in the order that they're written on the card.

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Base)
	int BaseDamage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Base)
	int BaseHealing;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Text)
	FString Description; // To-Do: Create a Style Guide for writing card description.

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Text)
	FString FlavourText;

	// For each function that requires different targets, the game will add an entry to the stack.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Functions)
	TMap<ECardFunctions, ECardTargets> FunctionsAndTargets;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Functions)
	TMap<ECardModifiers, ECardModifierTimingTriggers> ModifiersWithTriggers;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Functions)
	TArray<ECardKeywords> Keywords;

	/** Action Speed modifies the user's Readiness. The higher the card's Action Speed, the higher the users' Readiness.
	 
	 If a character plays multiple cards with different Action Speeds, the cards' Action Speeds will all be added together,
	 and the sum total will be applied to the character when they end their turn.
	 
	 An Action Speed of 0 is the default, and the neutral value. 0 means that the user's Readiness will not be impacted at all.
	 
	 For every integer value, the characters' Readiness is multiplied by 0.1.
	 E.g:
	 A total Action Value of 3 equals a Readiness multiplier of 1.3x.
	 A total Action Value of -4 equals a Readiness multiplier of 0.6x.
	 This means a characters' Action Value cannot go below 0.1x, or -9.*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Functions)
	int ActionSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = CalculatedVariables)
	int TotalCost;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = CalculatedVariables)
	int TotalDamage;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = CalculatedVariables)
	int TotalHealing;

	// Default constructor
	FCard()
	{
		DisplayName = "Default Card";
		BaseCost = 1;
		CardTypes.Add(ECardTypes::Spell);
		BaseDamage = 0;
		BaseHealing = 0;
		Description = "This is a default description.";
		FlavourText = "This is a default flavour text.";
		FunctionsAndTargets.Add(ECardFunctions::TestFunctionOne, ECardTargets::OneEnemy);
		ActionSpeed = 0;
		TotalCost = 1;
		TotalDamage = 0;
		TotalHealing = 0;
	}

	FORCEINLINE bool operator==(const FCard& OtherCard) const
	{
		TArray<ECardFunctions> ThisFunctions, OtherFunctions;
		this->FunctionsAndTargets.GetKeys(ThisFunctions);
		OtherCard.FunctionsAndTargets.GetKeys(OtherFunctions);

		TArray<ECardModifiers> ThisModifiers, OtherModifiers;
		this->ModifiersWithTriggers.GetKeys(ThisModifiers);
		OtherCard.ModifiersWithTriggers.GetKeys(OtherModifiers);
		
		return this->DisplayName == OtherCard.DisplayName &&
			this->BaseCost == OtherCard.BaseCost &&
			this->CardTypes == OtherCard.CardTypes &&
			this->CardElements == OtherCard.CardElements &&
			this->BaseDamage == OtherCard.BaseDamage &&
			this->BaseHealing == OtherCard.BaseHealing &&
			this->Description == OtherCard.Description &&
			ThisFunctions == OtherFunctions &&
			ThisModifiers == OtherModifiers;
	}
};


USTRUCT(BlueprintType)
struct LOSTWORLD_API FStackEntry
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	ECardFunctions Function;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	ECardTargets TargetingMode;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	AActorEntityBase* Controller;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<AActorEntityBase*> SelectedTargets;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int IndexInHandArray;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	FCard Card;
};


// -------------------------------- Entities
USTRUCT(BlueprintType)
struct LOSTWORLD_API FEntityBaseStats
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int CurrentHealthPoints;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int MaximumHealthPoints;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int CurrentManaPoints;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int MaximumManaPoints;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int CurrentBarrierPoints;

	// Increases damage dealt by physical attacks.
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int Strength;

	// Reduces damage taken from physical attacks.
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int Toughness;

	// Increases damage dealt by magical attacks.
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int Intelligence;
	
	// Reduces damage taken from magical attacks.
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int Willpower;

	// Determines the rate at which their Readiness increases.
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int Agility;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int HealthRegeneration;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int ManaRegeneration;

	// If a character has an EntityBaseStat ActionSpeed that is not zero, then that value will always be applied
	// to their TotalActionSpeed at the start of their turns.
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int TotalActionSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Readiness;
	
	// Default constructor
	FEntityBaseStats()
	{
		CurrentHealthPoints = 10;
		MaximumHealthPoints = 10;
		CurrentManaPoints = 10;
		MaximumManaPoints = 10;
		CurrentBarrierPoints = 0;
		Strength = 1;
		Toughness = 1;
		Intelligence = 1;
		Willpower = 1;
		Agility = 1;
		HealthRegeneration = 1;
		ManaRegeneration = 1;
		TotalActionSpeed = 0;
		Readiness = 0;
	}
};


// Offensive affinities: Multiply the calculated damage by the given number (converted to a percentage).
// Defensive affinities: "Invert" the percentage, then multiply the damage by the given number (e.g. 175 becomes 25%.)
// A high enough defensive affinity will cause the entity to absorb the damage as healing.
// A low enough defensive affinity will cause the entity to take more damage.
USTRUCT(BlueprintType)
struct LOSTWORLD_API FElementalAffinities
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int FireAffinity = 100;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int WaterAffinity = 100;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int AirAffinity = 100;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int EarthAffinity = 100;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int LightAffinity = 100;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int CosmicAffinity = 100;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int ArcaneAffinity = 100;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int DivineAffinity = 100;
};


USTRUCT(BlueprintType)
struct LOSTWORLD_API FEquipment : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString DisplayName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Description;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EEquipSlots EquipSlot;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FEntityBaseStats StatModifiers;

	FEquipment()
	{
		DisplayName = "Test Equipment";
		Description = "This is a test equipment.";
		EquipSlot = EEquipSlots::Head;
	}

	FORCEINLINE bool operator==(const FEquipment& OtherEquipment) const
	{
		return this->DisplayName == OtherEquipment.DisplayName &&
				this->Description == OtherEquipment.Description &&
				this->EquipSlot == OtherEquipment.EquipSlot;
				//&& this->StatModifiers == OtherEquipment.StatModifiers;
	}
};


// This struct should only contain variables that are relevant to all types of entities:
// Players, normal enemies, boss enemies, summons, and NPCs(?)
USTRUCT(BlueprintType)
struct LOSTWORLD_API FEntity : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString DisplayName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<EEntityTypes> EntityTypes;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FEntityBaseStats BaseStats;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FEntityBaseStats TotalStats;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FElementalAffinities OffensiveAffinities;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FElementalAffinities DefensiveAffinities;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FStatusEffect> CurrentStatusEffects;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<EStatusEffectFunctions> StartBattleWithStatusEffectFunctions;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FCard> Collection;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FCard> Deck;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FCard> Hand;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FCard> DrawPile;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FCard> DiscardPile;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FCard> Exile;

	// To-Do: Consider creating a new card zone to put summon cards when they're played.

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TArray<FStatusEffect> StatusEffects;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int MinimumDeckSize = -1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int MaximumDeckSize = -1;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FEquipment> EquippedItems;

	// This variable exists for all entities because all entities can have unequipped and equipped items.
	// Future: Give enemies the ability to equip and unequip items.
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FEquipment> EquipmentInventory;

	// How many cards should this entity draw at the start of a battle?
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int StartOfBattleHandSize;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	ETeams Team;

	// Shout cards can only be played once per turn, but don't cost anything to play.
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool HasUsedShoutThisTurn;

	FEntity()
	{
		DisplayName = "Default Jim";
		EntityTypes = { EEntityTypes::Enemy };
		StartOfBattleHandSize = 5;
		Team = ETeams::PlayerTeam;
		HasUsedShoutThisTurn = false;
	}
};


USTRUCT(BlueprintType)
struct LOSTWORLD_API FEnemyEntity : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EEntityTypes EnemyType;

	// Experience points given to the player when defeated.
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int ExperiencePoints;

	FEnemyEntity()
	{
		EnemyType = EEntityTypes::TestEnemyOne;
		ExperiencePoints = 1;
	}
};


USTRUCT(BlueprintType)
struct LOSTWORLD_API FSummonEntity : public FTableRowBase
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FEntity EntityData;
};


// -------------------------------- Player
USTRUCT(BlueprintType)
struct LOSTWORLD_API FPlayerSave : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FEntity EntityData;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString CurrentLevel;

	// To-Do: Learn more about signed vs unsigned integers, and use smaller ints when bigger ones aren't necessary.
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	uint8 CurrentFloor;
	
	FPlayerSave()
	{
		CurrentLevel = "TestLevel";
		CurrentFloor = 1;
	}
};


// -------------------------------- Level
USTRUCT(BlueprintType)
struct LOSTWORLD_API FEncounter : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EEncounterTypes EncounterType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<EEntityTypes> EntityTypes;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int MinimumFloor;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int MaximumFloor;

	FEncounter()
	{
		EncounterType = EEncounterTypes::None;
		MinimumFloor = 1;
		MaximumFloor = 1;
	}

	FORCEINLINE bool operator==(const FEncounter& OtherStruct) const
	{
		return this->EncounterType == OtherStruct.EncounterType &&
				this->EntityTypes == OtherStruct.EntityTypes &&
				this->MinimumFloor == OtherStruct.MinimumFloor &&
				this->MaximumFloor == OtherStruct.MaximumFloor;
	}
};


USTRUCT(BlueprintType)
struct LOSTWORLD_API FCorridorDataAsStruct
{
	GENERATED_BODY()

	// Each corridor grid tile coordinate.
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FIntVector2D> GridTileCoordinates;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<AActorGridTile*> GridTilesInCorridor;

	FORCEINLINE bool operator==(const FCorridorDataAsStruct& OtherStruct) const
	{
		return this->GridTileCoordinates == OtherStruct.GridTileCoordinates &&
				this->GridTilesInCorridor == OtherStruct.GridTilesInCorridor;
	}
};


USTRUCT(BlueprintType)
struct LOSTWORLD_API FRoomDataAsStruct
{
	GENERATED_BODY()

	// The lengths and widths should not exceed the dimensions of the floor.
	// These values are the minimum and maximum possible sizes of a room (not the coordinates.)
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int MinimumLength;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int MinimumWidth;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int MaximumLength;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int MaximumWidth;

	// These Boundary variables are generated by the level generator functions
	// and shouldn't be assigned in any JSON files.
	// Except for the bottom left Boundary, which will always be 1,1.
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FIntVector2D BottomLeftBoundary;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FIntVector2D BottomRightBoundary;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FIntVector2D TopLeftBoundary;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FIntVector2D TopRightBoundary;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<AActorGridTile*> GridTilesInRoom;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector BottomLeftCoordinate;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector BottomRightCoordinate;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector TopLeftCoordinate;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector TopRightCoordinate;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector RoomMidpoint;

	FRoomDataAsStruct()
	{
		MinimumLength = 3;
		MinimumWidth = 3;
		MaximumLength = 4;
		MaximumWidth = 4;
		BottomLeftBoundary = FIntVector2D(1, 1);
		BottomRightBoundary = FIntVector2D(1, 1);
		TopLeftBoundary = FIntVector2D(1, 1);
		TopRightBoundary = FIntVector2D(1, 1);
	}

	FORCEINLINE bool operator==(const FRoomDataAsStruct& OtherStruct) const
	{
		return this->MinimumLength == OtherStruct.MinimumLength &&
			this->MinimumWidth == OtherStruct.MinimumWidth &&
			this->MaximumLength == OtherStruct.MaximumLength &&
			this->MaximumWidth == OtherStruct.MaximumWidth &&
			this->BottomLeftBoundary == OtherStruct.BottomLeftBoundary &&
			this->BottomRightBoundary == OtherStruct.BottomRightBoundary &&
			this->TopLeftBoundary == OtherStruct.TopLeftBoundary &&
			this->TopRightBoundary == OtherStruct.TopRightBoundary &&
			this->GridTilesInRoom == OtherStruct.GridTilesInRoom;
	}
};


USTRUCT(BlueprintType)
struct LOSTWORLD_API FFloorDataAsStruct
{
	GENERATED_BODY()

	// The north-south dimension will be called 'Length' and 'X'.
	// This is the minimum size of the map in tiles.
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int MinimumLength;

	// The east-west dimension will be called 'Width' and 'Y'.
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int MinimumWidth;

	// This is the maximum size of the map in tiles.
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int MaximumLength;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int MaximumWidth;

	// These Boundary variables are generated by the level generator functions
	// and shouldn't be assigned in any JSON files.
	// Except for the bottom left Boundary, which will be the zero point of the level.
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FIntVector2D BottomLeftBoundary;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FIntVector2D BottomRightBoundary;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FIntVector2D TopLeftBoundary;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FIntVector2D TopRightBoundary;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EFloorLayouts Layout;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FRoomDataAsStruct> RoomDataAsStructsArray;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FCorridorDataAsStruct> CorridorDataAsStructsArray;

	FFloorDataAsStruct()
	{
		MinimumLength = 18;
		MinimumWidth = 18;
		MaximumLength = 28;
		MaximumWidth = 28;
		BottomLeftBoundary = FIntVector2D(1, 1);
		BottomRightBoundary = FIntVector2D(1, 1);
		TopLeftBoundary = FIntVector2D(1, 1);
		TopRightBoundary = FIntVector2D(1, 1);
		Layout = EFloorLayouts::FourSquares;
		RoomDataAsStructsArray = { FRoomDataAsStruct(),
									FRoomDataAsStruct(),
									FRoomDataAsStruct(),
									FRoomDataAsStruct() };
		CorridorDataAsStructsArray = { FCorridorDataAsStruct(),
									FCorridorDataAsStruct(),
									FCorridorDataAsStruct(),
									FCorridorDataAsStruct(), };
	}

	FORCEINLINE bool operator==(const FFloorDataAsStruct& OtherStruct) const
	{
		return this->MinimumLength == OtherStruct.MinimumLength &&
			this->MinimumWidth == OtherStruct.MinimumWidth &&
			this->MaximumLength == OtherStruct.MaximumLength &&
			this->MaximumWidth == OtherStruct.MaximumWidth &&
			this->BottomLeftBoundary == OtherStruct.BottomLeftBoundary &&
			this->BottomRightBoundary == OtherStruct.BottomRightBoundary &&
			this->TopLeftBoundary == OtherStruct.TopLeftBoundary &&
			this->TopRightBoundary == OtherStruct.TopRightBoundary &&
			this->Layout == OtherStruct.Layout &&
			this->RoomDataAsStructsArray == OtherStruct.RoomDataAsStructsArray &&
			this->CorridorDataAsStructsArray == OtherStruct.CorridorDataAsStructsArray;
	}
};


USTRUCT(BlueprintType)
struct LOSTWORLD_API FLevelDataAsStruct : public FTableRowBase
{
	GENERATED_BODY()

	// If true, the floor count will increment by +1 and
	// the stairs will appear to climb upward.
	// If false, then the opposite will be the case.
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool StairsGoUp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FEncounter> Encounters;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FFloorDataAsStruct FloorDataAsStruct;

	FLevelDataAsStruct()
	{
		StairsGoUp = true;
		Encounters.Add(FEncounter());
		Encounters[0].EncounterType = EEncounterTypes::Enemy;
	}

	FORCEINLINE bool operator==(const FLevelDataAsStruct& OtherStruct) const
	{
		return this->StairsGoUp == OtherStruct.StairsGoUp &&
			this->FloorDataAsStruct == OtherStruct.FloorDataAsStruct &&
			this->Encounters == OtherStruct.Encounters;
	}
};


// -------------------------------- Boiler-plate code
class LOSTWORLD_API Variables
{
public:
	Variables();
	~Variables();
};
