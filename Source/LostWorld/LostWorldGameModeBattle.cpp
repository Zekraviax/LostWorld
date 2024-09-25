#include "LostWorldGameModeBattle.h"


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
	
	LevelDataCopy = LevelDataSaveGameReference->LevelData;

	// Randomly generate the boundaries of the level.
	LevelDataCopy.FloorDataAsStruct.BottomLeftBoundary = FIntVector2D(1, 1);
	LevelDataCopy.FloorDataAsStruct.BottomRightBoundary = FIntVector2D(1,
		FMath::RandRange(LevelDataCopy.FloorDataAsStruct.MinimumWidth, LevelDataCopy.FloorDataAsStruct.MaximumWidth));
	LevelDataCopy.FloorDataAsStruct.TopLeftBoundary = FIntVector2D(
		FMath::RandRange(LevelDataCopy.FloorDataAsStruct.MinimumLength, LevelDataCopy.FloorDataAsStruct.MaximumLength), 1);
	LevelDataCopy.FloorDataAsStruct.TopRightBoundary = FIntVector2D(LevelDataCopy.FloorDataAsStruct.TopLeftBoundary.X, LevelDataCopy.FloorDataAsStruct.BottomRightBoundary.Y);

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
	
	// Step One:
	for (int RoomCount = 0; RoomCount < LevelDataCopy.FloorDataAsStruct.RoomDataAsStructsArray.Num(); RoomCount++) {
		// In the level data copy, the minimum and maximum lengths and widths will become the boundaries of the rooms.
		// Since the Layout is called 'Four Squares', each room will have one variable that determines the lengths and widths.
		if (RoomCount == 0) {
			int CalculatedMaximumLength = FMath::RandRange(
				LevelDataCopy.FloorDataAsStruct.RoomDataAsStructsArray[RoomCount].MinimumLength,
				LevelDataCopy.FloorDataAsStruct.RoomDataAsStructsArray[RoomCount].MaximumLength);
			
			LevelDataCopy.FloorDataAsStruct.RoomDataAsStructsArray[RoomCount].MaximumLength = CalculatedMaximumLength;
			LevelDataCopy.FloorDataAsStruct.RoomDataAsStructsArray[RoomCount].MaximumWidth = LevelDataCopy.FloorDataAsStruct.RoomDataAsStructsArray[RoomCount].MaximumLength;
			LevelDataCopy.FloorDataAsStruct.RoomDataAsStructsArray[RoomCount].MinimumLength = LevelDataCopy.FloorDataAsStruct.RoomDataAsStructsArray[RoomCount].MaximumLength;
			LevelDataCopy.FloorDataAsStruct.RoomDataAsStructsArray[RoomCount].MinimumWidth = LevelDataCopy.FloorDataAsStruct.RoomDataAsStructsArray[RoomCount].MaximumLength;

			// Calculate the corners of the room.
		}
	}
}
