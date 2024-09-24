#pragma once


#include "CoreMinimal.h"
#include "Variables.generated.h"


// ---------------------------------------- Enums ---------------------------------------- //

// -------------------------------- Levels
UENUM(BlueprintType)
enum class EFloorLayouts : uint8
{
	FourSquares
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


// ---------------------------------------- Structs ---------------------------------------- //

// -------------------------------- Levels
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

	FRoomDataAsStruct()
	{
		MinimumLength = 2;
		MinimumWidth = 2;
		MaximumLength = 4;
		MaximumWidth = 4;
	}

	FORCEINLINE bool operator==(const FRoomDataAsStruct& OtherStruct) const
	{
		return this->MinimumLength == OtherStruct.MinimumLength &&
			this->MinimumWidth == OtherStruct.MinimumWidth &&
			this->MaximumLength == OtherStruct.MaximumLength &&
			this->MaximumWidth == OtherStruct.MaximumWidth;
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

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EFloorLayouts Layout;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FRoomDataAsStruct> RoomDataAsStructsArray;

	FFloorDataAsStruct()
	{
		MinimumLength = 20;
		MinimumWidth = 20;
		MaximumLength = 40;
		MaximumWidth = 40;
		Layout = EFloorLayouts::FourSquares;
	}

	FORCEINLINE bool operator==(const FFloorDataAsStruct& OtherStruct) const
	{
		return this->MinimumLength == OtherStruct.MinimumLength &&
			this->MinimumWidth == OtherStruct.MinimumWidth &&
			this->MaximumLength == OtherStruct.MaximumLength &&
			this->MaximumWidth == OtherStruct.MaximumWidth &&
			this->Layout == OtherStruct.Layout &&
			this->RoomDataAsStructsArray == OtherStruct.RoomDataAsStructsArray;
	}
};


USTRUCT(BlueprintType)
struct LOSTWORLD_API FLevelDataAsStruct
{
	GENERATED_BODY()

	// If true, the floor count will increment by +1 and
	// the stairs will appear to climb upward.
	// If false, then the reverse will be the case.
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool StairsGoUp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FFloorDataAsStruct FloorDataAsStruct;

	FLevelDataAsStruct()
	{
		StairsGoUp = true;
	}

	FORCEINLINE bool operator==(const FLevelDataAsStruct& OtherStruct) const
	{
		return this->StairsGoUp == OtherStruct.StairsGoUp &&
			this->FloorDataAsStruct == OtherStruct.FloorDataAsStruct;
	}
};


// -------------------------------- Entities
USTRUCT(BlueprintType)
struct LOSTWORLD_API FEntityBaseStats
{
	GENERATED_BODY()

	// Increases damage dealt by physical attacks.
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int Strength;

	// Default constructor
	FEntityBaseStats()
	{
		Strength = 1;
	}
};


// -------------------------------- Cards
USTRUCT(BlueprintType)
struct LOSTWORLD_API FCard
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Base)
	FString DisplayName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Base)
	int BaseCost; // Use a different variable for the total cost (after any changes to the base cost)

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Base)
	TArray<ECardTypes> CardTypes; // Should be added to the array in the order that they're written on the card.

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Calculated)
	int CalculatedCost;

	// Default constructor
	FCard()
	{
		DisplayName = "Default Name";
		BaseCost = 1;
		CalculatedCost = 1;
	}
};


// -------------------------------- Boiler-plate code
class LOSTWORLD_API Variables
{
public:
	Variables();
	~Variables();
};
