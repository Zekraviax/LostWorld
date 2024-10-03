#include "LostWorldGameModeBattle.h"


#include "ActorGridTile.h"
#include "Kismet/GameplayStatics.h"
#include "SaveGameLevelData.h"


// -------------------------------- Battle 
void ALostWorldGameModeBattle::PreBattleShuffleDecks()
{
	
}


// -------------------------------- Level Generation
void ALostWorldGameModeBattle::LoadLevelData()
{
	if (!LevelDataSaveGameReference) {
		LevelDataSaveGameReference = Cast<USaveGameLevelData>(UGameplayStatics::CreateSaveGameObject(USaveGameLevelData::StaticClass()));
	}

	// If the LevelData var is equal to the default, that means it hasn't been loaded.
	if (LevelDataSaveGameReference->LevelData == FLevelDataAsStruct()) {
		LevelDataSaveGameReference->LoadLevelDataFromJson();
	}

	// Create a copy of the LevelData variable for editing and assigning variables.
	LevelDataCopy = LevelDataSaveGameReference->LevelData;

	// Randomly generate the boundaries of the level.
	LevelDataCopy.FloorDataAsStruct.BottomLeftBoundary = FIntVector2D(1, 1);
	LevelDataCopy.FloorDataAsStruct.BottomRightBoundary = FIntVector2D(1,
		FMath::RandRange(LevelDataCopy.FloorDataAsStruct.MinimumWidth, LevelDataCopy.FloorDataAsStruct.MaximumWidth));
	LevelDataCopy.FloorDataAsStruct.TopLeftBoundary = FIntVector2D(
		FMath::RandRange(LevelDataCopy.FloorDataAsStruct.MinimumLength, LevelDataCopy.FloorDataAsStruct.MaximumLength), 1);
	LevelDataCopy.FloorDataAsStruct.TopRightBoundary = FIntVector2D(
		LevelDataCopy.FloorDataAsStruct.TopLeftBoundary.X, LevelDataCopy.FloorDataAsStruct.BottomRightBoundary.Y);

	DualLog("Level bottom left boundary: " + FString::FromInt(LevelDataCopy.FloorDataAsStruct.BottomLeftBoundary.X) +
		", " + FString::FromInt(LevelDataCopy.FloorDataAsStruct.BottomLeftBoundary.Y));
	DualLog("Level top right boundary: " + FString::FromInt(LevelDataCopy.FloorDataAsStruct.TopRightBoundary.X) +
		", " + FString::FromInt(LevelDataCopy.FloorDataAsStruct.TopRightBoundary.Y));

	// The rest of the level generation depends on the layout.
	switch (LevelDataCopy.FloorDataAsStruct.Layout)
	{
		case EFloorLayouts::FourSquares:
			GenerateLevelLayoutFourSquares();
			break;
		default:
			// The FourSquares layout will be used as the default.
			GenerateLevelLayoutFourSquares();
			break;
	}
}


void ALostWorldGameModeBattle::GenerateLevelLayoutFourSquares()
{
	// Four Squares level layout:
	// Divide the level up into four roughly equal quadrants.
	// Generate one room for each quadrant.
	// Use the boundaries of the rooms to generate hallways that connect them.

	// ReSharper disable once CppTooWideScope
	const FActorSpawnParameters SpawnParameters;
	
	// Step One:
	for (int RoomCount = 0; RoomCount < LevelDataCopy.FloorDataAsStruct.RoomDataAsStructsArray.Num(); RoomCount++) {
		// In the level data copy, the minimum and maximum lengths and widths will become the boundaries of the rooms.
		int CalculatedLengthAndWidth = FMath::RandRange(
			LevelDataCopy.FloorDataAsStruct.RoomDataAsStructsArray[RoomCount].MinimumLength,
			LevelDataCopy.FloorDataAsStruct.RoomDataAsStructsArray[RoomCount].MaximumLength);

		// Since this Layout is 'Four Squares', each room will have one variable that determines the dimensions of the room.
		LevelDataCopy.FloorDataAsStruct.RoomDataAsStructsArray[RoomCount].MaximumLength = CalculatedLengthAndWidth;
		LevelDataCopy.FloorDataAsStruct.RoomDataAsStructsArray[RoomCount].MaximumWidth =
			LevelDataCopy.FloorDataAsStruct.RoomDataAsStructsArray[RoomCount].MaximumLength;
		LevelDataCopy.FloorDataAsStruct.RoomDataAsStructsArray[RoomCount].MinimumLength =
			LevelDataCopy.FloorDataAsStruct.RoomDataAsStructsArray[RoomCount].MaximumLength;
		LevelDataCopy.FloorDataAsStruct.RoomDataAsStructsArray[RoomCount].MinimumWidth =
			LevelDataCopy.FloorDataAsStruct.RoomDataAsStructsArray[RoomCount].MaximumLength;
		
		DualLog("Room " + FString::FromInt(RoomCount) + " calculated width and length: " + FString::FromInt(CalculatedLengthAndWidth));

		// Calculate the boundaries of the room, then calculate their positions in the level.
		// When the boundaries of the level are odd numbers, we round up for quadrant 4 and round down for all other quadrants
		// Quadrant 1 is the bottom-left corner. The bottom-left corner of the bottom-left quadrant always equals 1,1.
		// Quadrant 4 is the top-right corner. The top-right corner of the top-right quadrant always equals the maximum length and width.
		// Quadrant 2 is the bottom-right corner. It runs along the Width / Y axis, and shares the same X value as quadrant 1.
		// Quadrant 3 is in the top-left corner. It runs along the Length / X axis, and shares the same Y value as quadrant 1.

		// 2024/09/28 Addendum: Calculating the boundaries of the rooms also needs to account for the boundaries of the quadrants.
		// Currently, there aren't any checks that the rooms are generated outside of the level boundaries.
		// We can 'assign' rooms to quadrants by putting the top-right corner into a quadrant
		// and calculating the other boundaries using the top-right corner.

		// Room 3 is the room in the top-right quadrant.
		// Room 2 is the room in the top-left quadrant.
		// Room 1 is the room in the bottom-right quadrant.
		// Room 0 is the room in the bottom-left quadrant.
		if (RoomCount == 3) {
			LevelDataCopy.FloorDataAsStruct.RoomDataAsStructsArray[RoomCount].TopRightBoundary.X =
				FMath::RandRange(FMath::CeilToInt(LevelDataCopy.FloorDataAsStruct.TopRightBoundary.X / 2) + 2 + CalculatedLengthAndWidth, LevelDataCopy.FloorDataAsStruct.TopRightBoundary.X);
			LevelDataCopy.FloorDataAsStruct.RoomDataAsStructsArray[RoomCount].TopRightBoundary.Y =
				FMath::RandRange(FMath::CeilToInt(LevelDataCopy.FloorDataAsStruct.TopRightBoundary.Y / 2) + 2 + CalculatedLengthAndWidth, LevelDataCopy.FloorDataAsStruct.TopRightBoundary.Y);
		} else if (RoomCount == 2) {
			LevelDataCopy.FloorDataAsStruct.RoomDataAsStructsArray[RoomCount].TopRightBoundary.X =
				FMath::RandRange(FMath::CeilToInt(LevelDataCopy.FloorDataAsStruct.TopRightBoundary.X / 2) + CalculatedLengthAndWidth, LevelDataCopy.FloorDataAsStruct.TopRightBoundary.X);
			LevelDataCopy.FloorDataAsStruct.RoomDataAsStructsArray[RoomCount].TopRightBoundary.Y =
				FMath::RandRange(CalculatedLengthAndWidth, FMath::FloorToInt(LevelDataCopy.FloorDataAsStruct.TopRightBoundary.Y / 2));
		} else if (RoomCount == 1) {
			LevelDataCopy.FloorDataAsStruct.RoomDataAsStructsArray[RoomCount].TopRightBoundary.X =
				FMath::RandRange(CalculatedLengthAndWidth, FMath::FloorToInt(LevelDataCopy.FloorDataAsStruct.TopRightBoundary.X / 2));
			LevelDataCopy.FloorDataAsStruct.RoomDataAsStructsArray[RoomCount].TopRightBoundary.Y =
				FMath::RandRange(FMath::CeilToInt(LevelDataCopy.FloorDataAsStruct.TopRightBoundary.Y / 2) + CalculatedLengthAndWidth, LevelDataCopy.FloorDataAsStruct.TopRightBoundary.Y);
		} else if (RoomCount == 0) {
			LevelDataCopy.FloorDataAsStruct.RoomDataAsStructsArray[RoomCount].TopRightBoundary.X =
				FMath::RandRange(CalculatedLengthAndWidth, FMath::FloorToInt(LevelDataCopy.FloorDataAsStruct.TopRightBoundary.X / 2) - 1);
			LevelDataCopy.FloorDataAsStruct.RoomDataAsStructsArray[RoomCount].TopRightBoundary.Y =
				FMath::RandRange(CalculatedLengthAndWidth, FMath::FloorToInt(LevelDataCopy.FloorDataAsStruct.TopRightBoundary.Y / 2) - 1);
		}

		// Use the top-right boundary coordinates to calculate the rest of the boundary coordinates.
		LevelDataCopy.FloorDataAsStruct.RoomDataAsStructsArray[RoomCount].TopLeftBoundary.X =
			LevelDataCopy.FloorDataAsStruct.RoomDataAsStructsArray[RoomCount].TopRightBoundary.X - CalculatedLengthAndWidth;
		LevelDataCopy.FloorDataAsStruct.RoomDataAsStructsArray[RoomCount].TopLeftBoundary.Y =
			LevelDataCopy.FloorDataAsStruct.RoomDataAsStructsArray[RoomCount].TopRightBoundary.Y;

		LevelDataCopy.FloorDataAsStruct.RoomDataAsStructsArray[RoomCount].BottomRightBoundary.X =
			LevelDataCopy.FloorDataAsStruct.RoomDataAsStructsArray[RoomCount].TopRightBoundary.X;
		LevelDataCopy.FloorDataAsStruct.RoomDataAsStructsArray[RoomCount].BottomRightBoundary.Y =
			LevelDataCopy.FloorDataAsStruct.RoomDataAsStructsArray[RoomCount].TopRightBoundary.Y - CalculatedLengthAndWidth;
		
		LevelDataCopy.FloorDataAsStruct.RoomDataAsStructsArray[RoomCount].BottomLeftBoundary.X =
			LevelDataCopy.FloorDataAsStruct.RoomDataAsStructsArray[RoomCount].TopRightBoundary.X - CalculatedLengthAndWidth;
		LevelDataCopy.FloorDataAsStruct.RoomDataAsStructsArray[RoomCount].BottomLeftBoundary.Y =
			LevelDataCopy.FloorDataAsStruct.RoomDataAsStructsArray[RoomCount].TopRightBoundary.Y - CalculatedLengthAndWidth;

		DualLog("Room " + FString::FromInt(RoomCount) + " bottom left boundary: " +
			FString::FromInt(LevelDataCopy.FloorDataAsStruct.RoomDataAsStructsArray[RoomCount].BottomLeftBoundary.X) + ", " +
			FString::FromInt(LevelDataCopy.FloorDataAsStruct.RoomDataAsStructsArray[RoomCount].BottomLeftBoundary.Y));
		DualLog("Room " + FString::FromInt(RoomCount) + " bottom right boundary: " +
			FString::FromInt(LevelDataCopy.FloorDataAsStruct.RoomDataAsStructsArray[RoomCount].BottomRightBoundary.X) + ", " +
			FString::FromInt(LevelDataCopy.FloorDataAsStruct.RoomDataAsStructsArray[RoomCount].BottomRightBoundary.Y));
		DualLog("Room " + FString::FromInt(RoomCount) + " top left boundary: " +
			FString::FromInt(LevelDataCopy.FloorDataAsStruct.RoomDataAsStructsArray[RoomCount].TopLeftBoundary.X) + ", " +
			FString::FromInt(LevelDataCopy.FloorDataAsStruct.RoomDataAsStructsArray[RoomCount].TopLeftBoundary.Y));
		DualLog("Room " + FString::FromInt(RoomCount) + " top right boundary: " +
			FString::FromInt(LevelDataCopy.FloorDataAsStruct.RoomDataAsStructsArray[RoomCount].TopRightBoundary.X) + ", " +
			FString::FromInt(LevelDataCopy.FloorDataAsStruct.RoomDataAsStructsArray[RoomCount].TopRightBoundary.Y));

		// For each valid coordinate in each room, spawn a GridTile actor at those coordinates.
		for (int LengthCount = LevelDataCopy.FloorDataAsStruct.RoomDataAsStructsArray[RoomCount].BottomLeftBoundary.X;
			LengthCount <= LevelDataCopy.FloorDataAsStruct.RoomDataAsStructsArray[RoomCount].TopRightBoundary.X;
			LengthCount++) {
			for (int WidthCount = LevelDataCopy.FloorDataAsStruct.RoomDataAsStructsArray[RoomCount].BottomLeftBoundary.Y;
				WidthCount <= LevelDataCopy.FloorDataAsStruct.RoomDataAsStructsArray[RoomCount].TopRightBoundary.Y;
				WidthCount++) {
				GetWorld()->SpawnActor<AActorGridTile>(ActorGridTileBlueprintClass,
					FVector(LengthCount * 200, WidthCount * 200, 0),
					FRotator::ZeroRotator,
					SpawnParameters);
				}
			}
	}

	// Generate four corridors that connect the four rooms.
	for (int CorridorCount = 0; CorridorCount < LevelDataCopy.FloorDataAsStruct.CorridorDataAsStructsArray.Num(); CorridorCount++) {
		// Corridors will be listed and generated in clockwise order.
		// Corridor 0 = Bridge between the top two rooms.
		// Corridor 1 = Bridge between the right two rooms.
		// Corridor 2 = Bridge between the bottom two rooms.
		// Corridor 3 = Bridge between the left two rooms.

		// Corridors will be divided up in to two halves.
		// The first half will start in one room, and the second half will start in the opposite room.
		FIntVector2D CorridorFirstHalfStartingPoint;
		FIntVector2D CorridorSecondHalfStartingPoint;

		// The distance between rooms should not include room tiles.
		int YAxisDistanceBetweenRooms = 0;
		int XAxisDistanceBetweenRooms = 0;
		
		if (CorridorCount == 0) {
			// Get the boundaries of the two rooms that the corridor should be spawned between in order to get the corridor starting points.
			// RoomDataAsStructsArray[2] = Top-left Quadrant Room
			// Get a random integer for the Right.X coordinate from between the Top-Right.X and Top-Right.X coordinates.
			// The Top-Right.Y and Bottom-Right.Y coordinates are the same.
			CorridorFirstHalfStartingPoint.X = FMath::RandRange(LevelDataCopy.FloorDataAsStruct.RoomDataAsStructsArray[2].TopLeftBoundary.X,
			LevelDataCopy.FloorDataAsStruct.RoomDataAsStructsArray[2].TopRightBoundary.X);
			CorridorFirstHalfStartingPoint.Y = FMath::RandRange(LevelDataCopy.FloorDataAsStruct.RoomDataAsStructsArray[2].TopLeftBoundary.Y,
			LevelDataCopy.FloorDataAsStruct.RoomDataAsStructsArray[2].TopRightBoundary.Y);

			// RoomDataAsStructsArray[3] = Top-right Quadrant Room
			// Get a random integer for the Left.X coordinate from between the Bottom-Left.X and Bottom-Right.X coordinates.
			// The Bottom-Left.Y and Bottom-Right.X coordinates are the same.
			CorridorSecondHalfStartingPoint.X = FMath::RandRange(LevelDataCopy.FloorDataAsStruct.RoomDataAsStructsArray[3].BottomLeftBoundary.X,
			LevelDataCopy.FloorDataAsStruct.RoomDataAsStructsArray[3].BottomRightBoundary.X);
			CorridorSecondHalfStartingPoint.Y = FMath::RandRange(LevelDataCopy.FloorDataAsStruct.RoomDataAsStructsArray[3].BottomLeftBoundary.Y,
			LevelDataCopy.FloorDataAsStruct.RoomDataAsStructsArray[3].BottomRightBoundary.Y);
		} else if (CorridorCount == 1) {
			// RoomDataAsStructsArray[1] = Bottom-right Quadrant Room
			CorridorFirstHalfStartingPoint.X = FMath::RandRange(LevelDataCopy.FloorDataAsStruct.RoomDataAsStructsArray[1].BottomRightBoundary.X,
			LevelDataCopy.FloorDataAsStruct.RoomDataAsStructsArray[1].TopRightBoundary.X);
			CorridorFirstHalfStartingPoint.Y = FMath::RandRange(LevelDataCopy.FloorDataAsStruct.RoomDataAsStructsArray[1].BottomRightBoundary.Y,
			LevelDataCopy.FloorDataAsStruct.RoomDataAsStructsArray[1].TopRightBoundary.Y);
			
			// RoomDataAsStructsArray[3] = Top-right Quadrant Room
			CorridorSecondHalfStartingPoint.X = FMath::RandRange(LevelDataCopy.FloorDataAsStruct.RoomDataAsStructsArray[3].BottomLeftBoundary.X,
			LevelDataCopy.FloorDataAsStruct.RoomDataAsStructsArray[3].TopLeftBoundary.X);
			CorridorSecondHalfStartingPoint.Y = FMath::RandRange(LevelDataCopy.FloorDataAsStruct.RoomDataAsStructsArray[3].BottomLeftBoundary.Y,
			LevelDataCopy.FloorDataAsStruct.RoomDataAsStructsArray[3].TopLeftBoundary.Y);
		} else if (CorridorCount == 2) {
			// RoomDataAsStructsArray[0] = Bottom-left Quadrant Room
			// Get a random integer for the Right.X coordinate from between the Top-Right.X and Top-Right.X coordinates.
			// The Top-Right.Y and Bottom-Right.Y coordinates are the same.
			CorridorFirstHalfStartingPoint.X = FMath::RandRange(LevelDataCopy.FloorDataAsStruct.RoomDataAsStructsArray[0].TopLeftBoundary.X,
			LevelDataCopy.FloorDataAsStruct.RoomDataAsStructsArray[0].TopRightBoundary.X);
			CorridorFirstHalfStartingPoint.Y = FMath::RandRange(LevelDataCopy.FloorDataAsStruct.RoomDataAsStructsArray[0].TopLeftBoundary.Y,
			LevelDataCopy.FloorDataAsStruct.RoomDataAsStructsArray[0].TopRightBoundary.Y);

			// RoomDataAsStructsArray[1] = Bottom-right Quadrant Room
			// Get a random integer for the Left.X coordinate from between the Bottom-Left.X and Bottom-Right.X coordinates.
			// The Bottom-Left.Y and Bottom-Right.X coordinates are the same.
			CorridorSecondHalfStartingPoint.X = FMath::RandRange(LevelDataCopy.FloorDataAsStruct.RoomDataAsStructsArray[1].BottomLeftBoundary.X,
			LevelDataCopy.FloorDataAsStruct.RoomDataAsStructsArray[1].BottomRightBoundary.X);
			CorridorSecondHalfStartingPoint.Y = FMath::RandRange(LevelDataCopy.FloorDataAsStruct.RoomDataAsStructsArray[1].BottomLeftBoundary.Y,
			LevelDataCopy.FloorDataAsStruct.RoomDataAsStructsArray[1].BottomRightBoundary.Y);
		} else if (CorridorCount == 3) {
			// RoomDataAsStructsArray[0] = Bottom-left Quadrant Room
			CorridorFirstHalfStartingPoint.X = FMath::RandRange(LevelDataCopy.FloorDataAsStruct.RoomDataAsStructsArray[0].BottomRightBoundary.X,
			LevelDataCopy.FloorDataAsStruct.RoomDataAsStructsArray[0].TopRightBoundary.X);
			CorridorFirstHalfStartingPoint.Y = FMath::RandRange(LevelDataCopy.FloorDataAsStruct.RoomDataAsStructsArray[0].BottomRightBoundary.Y,
			LevelDataCopy.FloorDataAsStruct.RoomDataAsStructsArray[0].TopRightBoundary.Y);
			
			// RoomDataAsStructsArray[2] = Top-left Quadrant Room
			CorridorSecondHalfStartingPoint.X = FMath::RandRange(LevelDataCopy.FloorDataAsStruct.RoomDataAsStructsArray[2].BottomLeftBoundary.X,
			LevelDataCopy.FloorDataAsStruct.RoomDataAsStructsArray[2].TopLeftBoundary.X);
			CorridorSecondHalfStartingPoint.Y = FMath::RandRange(LevelDataCopy.FloorDataAsStruct.RoomDataAsStructsArray[2].BottomLeftBoundary.Y,
			LevelDataCopy.FloorDataAsStruct.RoomDataAsStructsArray[2].TopLeftBoundary.Y);
		}

		/*DualLog("Corridor " + FString::FromInt(CorridorCount) + " first half starting point " +
			FString::FromInt(CorridorFirstHalfStartingPoint.X) + ", " +
			FString::FromInt(CorridorFirstHalfStartingPoint.Y));

		DualLog("Corridor " + FString::FromInt(CorridorCount) + " second half starting point " +
			FString::FromInt(CorridorSecondHalfStartingPoint.X) + ", " +
			FString::FromInt(CorridorSecondHalfStartingPoint.Y));*/

		// Calculate the distance between rooms.
		if (CorridorCount == 0 || CorridorCount == 2) {
			// Calculate the distance between rooms.
			// For the top and bottom corridors, use the Y axis first.
			
			// If the distance between rooms is zero, do nothing.
			// If the distance between rooms is one, just spawn a single tile in the corridor.
			// If the distance between rooms is two or more, spawn tiles alternatively between either side of the corridor
			// until they meet on one axis, then spawn tiles on the other axis until they meet properly and can be traversed.
			
			// Use absolute values when calculating distances to avoid adding complexity.
			YAxisDistanceBetweenRooms = abs(CorridorFirstHalfStartingPoint.Y - CorridorSecondHalfStartingPoint.Y) - 1;
			
			// DualLog("Y-Axis distance between rooms: " + FString::FromInt(YAxisDistanceBetweenRooms));

			// First half of the corridor generation:
			// Spawn two separate halves of the corridor that meet on one axis, but not both axes.
			if (YAxisDistanceBetweenRooms == 1) {
				// If the axis distance is 1, just add 1 set of coordinates to the corridor 
				// in order to spawn a single tile into the corridor.
				CorridorFirstHalfStartingPoint.Y++;
				LevelDataCopy.FloorDataAsStruct.CorridorDataAsStructsArray[CorridorCount].GridTileCoordinates.AddUnique(
					FIntVector2D(CorridorFirstHalfStartingPoint.X, CorridorFirstHalfStartingPoint.Y));
			} else if (YAxisDistanceBetweenRooms > 1) {
				// If the distance is greater than one, alternate between calculating the next set of coordinates starting
				// from the first half starting point and the second half starting point.
				while (YAxisDistanceBetweenRooms >= 0) {
					if (YAxisDistanceBetweenRooms % 2 == 0) {
						CorridorFirstHalfStartingPoint.Y++;
						LevelDataCopy.FloorDataAsStruct.CorridorDataAsStructsArray[CorridorCount].GridTileCoordinates.AddUnique(
							FIntVector2D(CorridorFirstHalfStartingPoint.X, CorridorFirstHalfStartingPoint.Y));
					} else {
						CorridorSecondHalfStartingPoint.Y--;
						LevelDataCopy.FloorDataAsStruct.CorridorDataAsStructsArray[CorridorCount].GridTileCoordinates.AddUnique(
							FIntVector2D(CorridorSecondHalfStartingPoint.X, CorridorSecondHalfStartingPoint.Y));
					}
					
					YAxisDistanceBetweenRooms--;
				}
			}

			// Second half of the corridor generation:
			// Spawn tiles along the other axis until the halves of the corridor fully meet.
			// Can't use the absolute value here because we need to know in which direction to spawn the tiles
			XAxisDistanceBetweenRooms = (CorridorFirstHalfStartingPoint.X - CorridorSecondHalfStartingPoint.X);

			// In order to get the true distance between corridors, we need to add 1 to the XAxisDistanceBetweenRooms
			// if the distance is a negative number. If its positive and non-zero, subtract 1.
			if (XAxisDistanceBetweenRooms < 0) {
				XAxisDistanceBetweenRooms++;
			} else if (XAxisDistanceBetweenRooms > 0) {
				XAxisDistanceBetweenRooms--;
			}

			// If the distance between rooms is 1 or -1, that means only one tile needs to spawned in the corridor.
			if (XAxisDistanceBetweenRooms == 1 || XAxisDistanceBetweenRooms == -1) {
				if (XAxisDistanceBetweenRooms == 1) {
					CorridorFirstHalfStartingPoint.X--;
				} else {
					CorridorFirstHalfStartingPoint.X++;
				}
				
				LevelDataCopy.FloorDataAsStruct.CorridorDataAsStructsArray[CorridorCount].GridTileCoordinates.AddUnique(
				FIntVector2D(CorridorFirstHalfStartingPoint.X, CorridorFirstHalfStartingPoint.Y));
			} else if (XAxisDistanceBetweenRooms > 1 || XAxisDistanceBetweenRooms < -1) {
				while (XAxisDistanceBetweenRooms != 0) {
					if (XAxisDistanceBetweenRooms > 1) {
						XAxisDistanceBetweenRooms--;
						CorridorFirstHalfStartingPoint.X--;
					} else {
						XAxisDistanceBetweenRooms++;
						CorridorFirstHalfStartingPoint.X++;
					}

					LevelDataCopy.FloorDataAsStruct.CorridorDataAsStructsArray[CorridorCount].GridTileCoordinates.AddUnique(
					FIntVector2D(CorridorFirstHalfStartingPoint.X, CorridorFirstHalfStartingPoint.Y));
				}
			}
		} else if (CorridorCount == 1 || CorridorCount == 3) {
			// Calculate the distance between rooms.
			// For the left and right corridors, use the X axis first.
			
			// If the distance between rooms is zero, do nothing.
			// If the distance between rooms is one, just spawn a single tile in the corridor.
			// If the distance between rooms is two or more, spawn tiles alternatively between either side of the corridor
			// until they meet on one axis, then spawn tiles on the other axis until they meet properly and can be traversed.
			
			// Use absolute values when calculating distances to avoid adding complexity.
			XAxisDistanceBetweenRooms = abs(CorridorFirstHalfStartingPoint.X - CorridorSecondHalfStartingPoint.X) - 1;
			
			// DualLog("X-Axis distance between rooms: " + FString::FromInt(XAxisDistanceBetweenRooms));

			// First half of the corridor generation:
			// Spawn two separate halves of the corridor that meet on one axis, but not both axes.
			if (XAxisDistanceBetweenRooms == 1) {
				// If the axis distance is 1, just add 1 set of coordinates to the corridor 
				// in order to spawn a single tile into the corridor.
				CorridorFirstHalfStartingPoint.X++;
				LevelDataCopy.FloorDataAsStruct.CorridorDataAsStructsArray[CorridorCount].GridTileCoordinates.AddUnique(
					FIntVector2D(CorridorFirstHalfStartingPoint.X, CorridorFirstHalfStartingPoint.Y));
			} else if (XAxisDistanceBetweenRooms > 1)
			{
				// If the distance is greater than one, alternate between calculating the next set of coordinates starting
				// from the first half starting point and the second half starting point.
				while (XAxisDistanceBetweenRooms >= 0) {
					if (XAxisDistanceBetweenRooms % 2 == 0) {
						CorridorFirstHalfStartingPoint.X++;
						LevelDataCopy.FloorDataAsStruct.CorridorDataAsStructsArray[CorridorCount].GridTileCoordinates.AddUnique(
							FIntVector2D(CorridorFirstHalfStartingPoint.X, CorridorFirstHalfStartingPoint.Y));
					} else {
						CorridorSecondHalfStartingPoint.X--;
						LevelDataCopy.FloorDataAsStruct.CorridorDataAsStructsArray[CorridorCount].GridTileCoordinates.AddUnique(
							FIntVector2D(CorridorSecondHalfStartingPoint.X, CorridorSecondHalfStartingPoint.Y));
					}
					
					XAxisDistanceBetweenRooms--;
				}
			}

			// Second half of the corridor generation:
			// Spawn tiles along the other axis until the halves of the corridor fully meet.
			// Can't use the absolute value here because we need to know in which direction to spawn the tiles
			YAxisDistanceBetweenRooms = (CorridorFirstHalfStartingPoint.Y - CorridorSecondHalfStartingPoint.Y);

			// In order to get the true distance between corridors, we need to add 1 to the XAxisDistanceBetweenRooms
			// if the distance is a negative number. If its positive and non-zero, subtract 1.
			if (YAxisDistanceBetweenRooms < 0) {
				YAxisDistanceBetweenRooms++;
			} else if (YAxisDistanceBetweenRooms > 0) {
				YAxisDistanceBetweenRooms--;
			}

			// If the distance between rooms is 1 or -1, that means only one tile needs to spawned in the corridor.
			if (YAxisDistanceBetweenRooms == 1 || YAxisDistanceBetweenRooms == -1) {
				if (YAxisDistanceBetweenRooms == 1) {
					CorridorFirstHalfStartingPoint.Y--;
				} else {
					CorridorFirstHalfStartingPoint.Y++;
				}
				
				LevelDataCopy.FloorDataAsStruct.CorridorDataAsStructsArray[CorridorCount].GridTileCoordinates.AddUnique(
				FIntVector2D(CorridorFirstHalfStartingPoint.X, CorridorFirstHalfStartingPoint.Y));
			} else if (YAxisDistanceBetweenRooms > 1 || YAxisDistanceBetweenRooms < -1) {
				while (YAxisDistanceBetweenRooms != 0) {
					if (YAxisDistanceBetweenRooms > 1) {
						YAxisDistanceBetweenRooms--;
						CorridorFirstHalfStartingPoint.Y--;
					} else {
						YAxisDistanceBetweenRooms++;
						CorridorFirstHalfStartingPoint.Y++;
					}

					LevelDataCopy.FloorDataAsStruct.CorridorDataAsStructsArray[CorridorCount].GridTileCoordinates.AddUnique(
					FIntVector2D(CorridorFirstHalfStartingPoint.X, CorridorFirstHalfStartingPoint.Y));
				}
			}
		}
			
		// For each set of coordinates in the corridor, spawn a GridTile actor there.
		for (FIntVector2D Coordinate : LevelDataCopy.FloorDataAsStruct.CorridorDataAsStructsArray[CorridorCount].GridTileCoordinates) {
			GetWorld()->SpawnActor<AActorGridTile>(ActorGridTileBlueprintClass,
				FVector(Coordinate.X * 200, Coordinate.Y * 200, 0),
				FRotator::ZeroRotator,
				SpawnParameters);
		}
	}
}