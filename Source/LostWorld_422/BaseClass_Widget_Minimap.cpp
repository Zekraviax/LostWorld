#include "BaseClass_Widget_Minimap.h"

#include "WidgetComponent_MinimapRoom.h"
#include "Components/SceneComponent.h"
#include "Components/UniformGridSlot.h"
#include "Components/GridSlot.h"
#include "BaseClass_GridTile.h"
#include "BaseClass_PlayerController.h"


void UBaseClass_Widget_Minimap::GenerateLevel()
{
	FActorSpawnParameters SpawnParameters;
	TArray<USceneComponent*> GridTileSceneComponents;

	// Test Room Formation: Four Square
	// Divide the map into four equal quadrants,
	// Then randomly pick a tile near the centre of each quadrant.
	// Create a room of variable size around the chosen tiles.

	// Randomly generate half-width values for the sizes of the room.
	// Then pick a random tile to be the center of the room.
	// Strip away all tiles that are further away than the half-values.
	// We use half-values instead of full values in order to make it easier to generate rooms.
	// And maybe we can have special things or events take place in room centers.

	TArray<FVector2D> MinimapArrayRoomOneCoordinates, MinimapArrayRoomTwoCoordinates, MinimapArrayRoomThreeCoordinates, MinimapArrayRoomFourCoordinates, MinimapArrayRoomFiveCoordinates, MinimapArrayRoomSixCoordinates, MinimapArrayRoomSevenCoordinates, MinimapArrayRoomEightCoordinates;
	TArray<FVector2D> MinimapArrayCorridorOneCoordinates, MinimapArrayCorridorTwoCoordinates, MinimapArrayCorridorThreeCoordinates, MinimapArrayCorridorFourCoordinates, MinimapArrayCorridorFiveCoordinates, MinimapArrayCorridorSixCoordinates, MinimapArrayCorridorSevenCoordinates, MinimapArrayCorridorEightCoordinates;

	FVector2D RoomOneCenter = FVector2D(FMath::RandRange(3, 6), FMath::RandRange(3, 6));
	//int RoomOneHalfWidth = FMath::RandRange(1, 3);
	int RoomOneHalfWidth = 2;
	int RoomOneHalfHeight = 2;

	FVector2D RoomTwoCenter = FVector2D(FMath::RandRange(3, 6), FMath::RandRange(13, 16));
	int RoomTwoHalfWidth = 2;
	int RoomTwoHalfHeight = 2;

	FVector2D RoomThreeCenter = FVector2D(FMath::RandRange(13, 16), FMath::RandRange(3, 6));
	int RoomThreeHalfWidth = 2;
	int RoomThreeHalfHeight = 2;

	FVector2D RoomFourCenter = FVector2D(FMath::RandRange(13, 16), FMath::RandRange(13, 16));
	int RoomFourHalfWidth = 2;
	int RoomFourHalfHeight = 2;

	//MinimapTileOne = MinimapRoomArrayOne[FMath::RandRange(3, MinimapRoomArrayOne.Num() - 4)];

	//int LeftRoomBound = MinimapTileOne->X_Coordinate - RoomOneHalfWidth;
	//int RightRoomBound = MinimapTileOne->X_Coordinate + RoomOneHalfHeight;

	// Generate Base Level
	// Hard-Coded to be no bigger than 20x20
	// (Need to experiment with a reasonable size limit)
	for (int x = 0; x <= 20; x++) {
		for (int y = 0; y <= 20; y++) {
			if (x <= (RoomOneCenter.X + RoomOneHalfWidth) && x >= (RoomOneCenter.X - RoomOneHalfWidth) &&
				y <= (RoomOneCenter.Y + RoomOneHalfHeight) && y >= (RoomOneCenter.Y - RoomOneHalfHeight)) {
				MinimapArrayRoomOneCoordinates.Add(FVector2D(x, y));
			} else if (x <= (RoomTwoCenter.X + RoomTwoHalfWidth) && x >= (RoomTwoCenter.X - RoomTwoHalfWidth) &&
				y <= (RoomTwoCenter.Y + RoomTwoHalfHeight) && y >= (RoomTwoCenter.Y - RoomTwoHalfHeight)) {
				MinimapArrayRoomTwoCoordinates.Add(FVector2D(x, y));
			} else if (x <= (RoomThreeCenter.X + RoomThreeHalfWidth) && x >= (RoomThreeCenter.X - RoomThreeHalfWidth) &&
				y <= (RoomThreeCenter.Y + RoomThreeHalfHeight) && y >= (RoomThreeCenter.Y - RoomThreeHalfHeight)) {
				MinimapArrayRoomThreeCoordinates.Add(FVector2D(x, y));
			} else if (x <= (RoomFourCenter.X + RoomFourHalfWidth) && x >= (RoomFourCenter.X - RoomFourHalfWidth) &&
				y <= (RoomFourCenter.Y + RoomFourHalfHeight) && y >= (RoomFourCenter.Y - RoomFourHalfHeight)) {
				MinimapArrayRoomFourCoordinates.Add(FVector2D(x, y));
			}

			//if (x <= (RoomOneCenter.X + RoomOneHalfWidth) && x >= (RoomOneCenter.X - RoomOneHalfWidth)) {
			//	MinimapArrayRoomOneCoordinates.Add(FVector2D(x, y));
			//}
			//else if (y <= (RoomOneCenter.Y + RoomOneHalfHeight) && y >= (RoomOneCenter.Y - RoomOneHalfHeight)) {
			//	MinimapArrayRoomFiveCoordinates.Add(FVector2D(x, y));
			//}
			//else if (x <= (RoomTwoCenter.X + RoomTwoHalfWidth) && x >= (RoomTwoCenter.X - RoomTwoHalfWidth)) {
			//	MinimapArrayRoomTwoCoordinates.Add(FVector2D(x, y));
			//}
			//else if (y <= (RoomTwoCenter.Y + RoomTwoHalfHeight) && y >= (RoomTwoCenter.Y - RoomTwoHalfHeight)) {
			//	MinimapArrayRoomSixCoordinates.Add(FVector2D(x, y));
			//}
			//else if (x <= (RoomThreeCenter.X + RoomThreeHalfWidth) && x >= (RoomThreeCenter.X - RoomThreeHalfWidth)) {
			//	MinimapArrayRoomThreeCoordinates.Add(FVector2D(x, y));
			//}
			//else if (y <= (RoomThreeCenter.Y + RoomThreeHalfHeight) && y >= (RoomThreeCenter.Y - RoomThreeHalfHeight)) {
			//	MinimapArrayRoomSevenCoordinates.Add(FVector2D(x, y));
			//}
			//else if (x <= (RoomFourCenter.X + RoomFourHalfWidth) && x >= (RoomFourCenter.X - RoomFourHalfWidth)) {
			//	MinimapArrayRoomFourCoordinates.Add(FVector2D(x, y));
			//}
			//else if (y <= (RoomFourCenter.Y + RoomFourHalfHeight) && y >= (RoomFourCenter.Y - RoomFourHalfHeight)) {
			//	MinimapArrayRoomEightCoordinates.Add(FVector2D(x, y));
			//}

			//if (x <= (RoomOneCenter.X + RoomOneHalfWidth) && y <= (RoomOneCenter.Y + RoomOneHalfHeight) ||
			//	x >= (RoomOneCenter.X - RoomOneHalfWidth) && y >= (RoomOneCenter.Y - RoomOneHalfHeight) ||
			//	x <= (RoomOneCenter.X + RoomOneHalfWidth) && y >= (RoomOneCenter.Y - RoomOneHalfHeight) || 
			//	x >= (RoomOneCenter.X - RoomOneHalfWidth) && y <= (RoomOneCenter.Y + RoomOneHalfHeight)) {
			//	MinimapArrayRoomOneCoordinates.Add(FVector2D(x, y));
			//} 
			//else if (x <= (RoomTwoCenter.X + RoomTwoHalfWidth) && y <= (RoomTwoCenter.Y + RoomTwoHalfHeight) ||
			//	x >= (RoomTwoCenter.X - RoomTwoHalfWidth) && y >= (RoomTwoCenter.Y - RoomTwoHalfHeight) ||
			//	x <= (RoomTwoCenter.X + RoomTwoHalfWidth) && y >= (RoomTwoCenter.Y - RoomTwoHalfHeight) ||
			//	x >= (RoomTwoCenter.X - RoomTwoHalfWidth) && y <= (RoomTwoCenter.Y + RoomTwoHalfHeight)) {
			//	MinimapArrayRoomTwoCoordinates.Add(FVector2D(x, y));
			//} else if (x <= (RoomThreeCenter.X + RoomThreeHalfWidth) && y <= (RoomThreeCenter.Y + RoomThreeHalfHeight) ||
			//	x >= (RoomThreeCenter.X - RoomThreeHalfWidth) && y >= (RoomThreeCenter.Y - RoomThreeHalfHeight) ||
			//	x <= (RoomThreeCenter.X + RoomThreeHalfWidth) && y >= (RoomThreeCenter.Y - RoomThreeHalfHeight) ||
			//	x >= (RoomThreeCenter.X - RoomThreeHalfWidth) && y <= (RoomThreeCenter.Y + RoomThreeHalfHeight)) {
			//	MinimapArrayRoomThreeCoordinates.Add(FVector2D(x, y));
			//} else if (x <= (RoomFourCenter.X + RoomFourHalfWidth) && y <= (RoomFourCenter.Y + RoomFourHalfHeight) ||
			//	x >= (RoomFourCenter.X - RoomFourHalfWidth) && y >= (RoomFourCenter.Y - RoomFourHalfHeight) ||
			//	x <= (RoomFourCenter.X + RoomFourHalfWidth) && y >= (RoomFourCenter.Y - RoomFourHalfHeight) ||
			//	x >= (RoomFourCenter.X - RoomFourHalfWidth) && y <= (RoomFourCenter.Y + RoomFourHalfHeight)) {
			//	MinimapArrayRoomFourCoordinates.Add(FVector2D(x, y));
			//}
		}
	}

	// Find the edges of the four rooms and select one tile to start making corridors
	// Bottom Row and Right Column for Room One
	for (int i = 0; i < MinimapArrayRoomOneCoordinates.Num(); i++) {
		if (MinimapArrayRoomOneCoordinates[i].X == (RoomOneCenter.X + RoomOneHalfWidth)) {
			MinimapArrayCorridorFiveCoordinates.Add(MinimapArrayRoomOneCoordinates[i]);
		}
		else if (MinimapArrayRoomOneCoordinates[i].Y == (RoomOneCenter.Y + RoomOneHalfHeight)) {
			MinimapArrayCorridorOneCoordinates.Add(MinimapArrayRoomOneCoordinates[i]);
		}
	}
	// Bottom Row and Left Column for Room Two
	for (int i = 0; i < MinimapArrayRoomTwoCoordinates.Num(); i++) {
		if (MinimapArrayRoomTwoCoordinates[i].X == (RoomTwoCenter.X + RoomTwoHalfWidth)) {
			MinimapArrayCorridorSixCoordinates.Add(MinimapArrayRoomTwoCoordinates[i]);
		}
		else if (MinimapArrayRoomTwoCoordinates[i].Y == (RoomTwoCenter.Y - RoomTwoHalfWidth)) {
			MinimapArrayCorridorTwoCoordinates.Add(MinimapArrayRoomTwoCoordinates[i]);
		}
	}
	// Top Row and Right Colomn for Room Three
	for (int i = 0; i < MinimapArrayRoomThreeCoordinates.Num(); i++) {
		if (MinimapArrayRoomThreeCoordinates[i].X == (RoomThreeCenter.X - RoomTwoHalfWidth)) {
			MinimapArrayCorridorSevenCoordinates.Add(MinimapArrayRoomThreeCoordinates[i]);
		}
		else if (MinimapArrayRoomThreeCoordinates[i].Y == (RoomThreeCenter.Y + RoomTwoHalfWidth)) {
			MinimapArrayCorridorThreeCoordinates.Add(MinimapArrayRoomThreeCoordinates[i]);
		}
	}
	// Top Row and Left Column for Room Four
	for (int i = 0; i < MinimapArrayRoomFourCoordinates.Num(); i++) {
		if (MinimapArrayRoomFourCoordinates[i].X == (RoomFourCenter.X - RoomTwoHalfWidth)) {
			MinimapArrayCorridorEightCoordinates.Add(MinimapArrayRoomFourCoordinates[i]);
		}
		else if (MinimapArrayRoomFourCoordinates[i].Y == (RoomFourCenter.Y - RoomTwoHalfWidth)) {
			MinimapArrayCorridorFourCoordinates.Add(MinimapArrayRoomFourCoordinates[i]);
		}
	}

	// Pick eight random tiles along the edges of the rooms to be the start of the corridors that join the rooms
	int MinimapArrayCorridorOneChosenIndex = FMath::RandRange(0, MinimapArrayCorridorOneCoordinates.Num() - 1);
	int MinimapArrayCorridorTwoChosenIndex = FMath::RandRange(0, MinimapArrayCorridorTwoCoordinates.Num() - 1);
	int MinimapArrayCorridorThreeChosenIndex = FMath::RandRange(0, MinimapArrayCorridorThreeCoordinates.Num() - 1);
	int MinimapArrayCorridorFourChosenIndex = FMath::RandRange(0, MinimapArrayCorridorFourCoordinates.Num() - 1);
	int MinimapArrayCorridorFiveChosenIndex = FMath::RandRange(0, MinimapArrayCorridorFiveCoordinates.Num() - 1);
	int MinimapArrayCorridorSixChosenIndex = FMath::RandRange(0, MinimapArrayCorridorSixCoordinates.Num() - 1);
	int MinimapArrayCorridorSevenChosenIndex = FMath::RandRange(0, MinimapArrayCorridorSevenCoordinates.Num() - 1);
	int MinimapArrayCorridorEightChosenIndex = FMath::RandRange(0, MinimapArrayCorridorEightCoordinates.Num() - 1);

	for (int i = MinimapArrayCorridorOneCoordinates.Num() - 1; i >= 0 ; i--) {
		if (i != MinimapArrayCorridorOneChosenIndex) {
			MinimapArrayCorridorOneCoordinates.RemoveAt(i);
		}
	}
	for (int i = MinimapArrayCorridorTwoCoordinates.Num() - 1; i >= 0; i--) {
		if (i != MinimapArrayCorridorTwoChosenIndex) {
			MinimapArrayCorridorTwoCoordinates.RemoveAt(i);
		}
	}
	for (int i = MinimapArrayCorridorThreeCoordinates.Num() - 1; i >= 0; i--) {
		if (i != MinimapArrayCorridorThreeChosenIndex) {
			MinimapArrayCorridorThreeCoordinates.RemoveAt(i);
		}
	}
	for (int i = MinimapArrayCorridorFourCoordinates.Num() - 1; i >= 0; i--) {
		if (i != MinimapArrayCorridorFourChosenIndex) {
			MinimapArrayCorridorFourCoordinates.RemoveAt(i);
		}
	}
	for (int i = MinimapArrayCorridorFiveCoordinates.Num() - 1; i >= 0; i--) {
		if (i != MinimapArrayCorridorFiveChosenIndex) {
			MinimapArrayCorridorFiveCoordinates.RemoveAt(i);
		}
	}
	for (int i = MinimapArrayCorridorSixCoordinates.Num() - 1; i >= 0; i--) {
		if (i != MinimapArrayCorridorSixChosenIndex) {
			MinimapArrayCorridorSixCoordinates.RemoveAt(i);
		}
	}
	for (int i = MinimapArrayCorridorSevenCoordinates.Num() - 1; i >= 0; i--) {
		if (i != MinimapArrayCorridorSevenChosenIndex) {
			MinimapArrayCorridorSevenCoordinates.RemoveAt(i);
		}
	}
	for (int i = MinimapArrayCorridorEightCoordinates.Num() - 1; i >= 0; i--) {
		if (i != MinimapArrayCorridorEightChosenIndex) {
			MinimapArrayCorridorEightCoordinates.RemoveAt(i);
		}
	}

	// Starting with the Bottom Row columns, place one tile in the corridor, then check if the corridor on the opposite side is at the same coordinate.
	// If False, then swap to the Top Row columns and repeat the process.
	// If True, start placing tiles perpendicular to the columns so that the two corridors meet and create one whole corridor that joins two rooms.
	// Then swap to Left Rows and repeat the process for Rows.

	// Generate Corridor coordinates until the two corridor segments are parallel
	int MaxLoopCount = 0;
	while (MinimapArrayCorridorOneCoordinates[MinimapArrayCorridorOneCoordinates.Num() - 1].Y != MinimapArrayCorridorTwoCoordinates[MinimapArrayCorridorTwoCoordinates.Num() - 1].Y && MaxLoopCount < 10) {
		MinimapArrayCorridorOneCoordinates.Add(FVector2D(MinimapArrayCorridorOneCoordinates.Last().X, MinimapArrayCorridorOneCoordinates.Last().Y + 1));

		if (MinimapArrayCorridorOneCoordinates[MinimapArrayCorridorOneCoordinates.Num() - 1].Y != MinimapArrayCorridorTwoCoordinates[MinimapArrayCorridorTwoCoordinates.Num() - 1].Y) {
			MinimapArrayCorridorTwoCoordinates.Add(FVector2D(MinimapArrayCorridorTwoCoordinates.Last().X, MinimapArrayCorridorTwoCoordinates.Last().Y - 1));
		}

		MaxLoopCount++;
	}

	// If the corridors aren't already joined, figure out which direction to keep placing corridor tiles.
	// Then place tiles until the first corridor has reached the second corridor.
	while (!MinimapArrayCorridorTwoCoordinates.Contains(FVector2D(MinimapArrayCorridorOneCoordinates[MinimapArrayCorridorOneCoordinates.Num() - 1].X, MinimapArrayCorridorOneCoordinates[MinimapArrayCorridorOneCoordinates.Num() - 1].Y + 1)) &&
		!MinimapArrayCorridorTwoCoordinates.Contains(FVector2D(MinimapArrayCorridorOneCoordinates[MinimapArrayCorridorOneCoordinates.Num() - 1].X - 1, MinimapArrayCorridorOneCoordinates[MinimapArrayCorridorOneCoordinates.Num() - 1].Y)) &&
		!MinimapArrayCorridorTwoCoordinates.Contains(FVector2D(MinimapArrayCorridorOneCoordinates[MinimapArrayCorridorOneCoordinates.Num() - 1].X + 1, MinimapArrayCorridorOneCoordinates[MinimapArrayCorridorOneCoordinates.Num() - 1].Y))) {

		if (MinimapArrayCorridorTwoCoordinates.Last().X > MinimapArrayCorridorOneCoordinates.Last().X) {
			MinimapArrayCorridorOneCoordinates.Add(FVector2D(MinimapArrayCorridorOneCoordinates.Last().X + 1, MinimapArrayCorridorOneCoordinates.Last().Y));
		}
		else if (MinimapArrayCorridorTwoCoordinates.Last().X < MinimapArrayCorridorOneCoordinates.Last().X) {
			MinimapArrayCorridorOneCoordinates.Add(FVector2D(MinimapArrayCorridorOneCoordinates.Last().X - 1, MinimapArrayCorridorOneCoordinates.Last().Y));
		}
	}

	// Corridor Segments Three and Four
	MaxLoopCount = 0;
	while (MinimapArrayCorridorThreeCoordinates[MinimapArrayCorridorThreeCoordinates.Num() - 1].Y != MinimapArrayCorridorFourCoordinates[MinimapArrayCorridorFourCoordinates.Num() - 1].Y && MaxLoopCount < 10) {
		MinimapArrayCorridorThreeCoordinates.Add(FVector2D(MinimapArrayCorridorThreeCoordinates.Last().X, MinimapArrayCorridorThreeCoordinates.Last().Y + 1));

		if (MinimapArrayCorridorThreeCoordinates[MinimapArrayCorridorThreeCoordinates.Num() - 1].Y != MinimapArrayCorridorFourCoordinates[MinimapArrayCorridorFourCoordinates.Num() - 1].Y) {
			MinimapArrayCorridorFourCoordinates.Add(FVector2D(MinimapArrayCorridorFourCoordinates.Last().X, MinimapArrayCorridorFourCoordinates.Last().Y - 1));
		}

		MaxLoopCount++;
	}

	while (!MinimapArrayCorridorFourCoordinates.Contains(FVector2D(MinimapArrayCorridorThreeCoordinates[MinimapArrayCorridorThreeCoordinates.Num() - 1].X, MinimapArrayCorridorThreeCoordinates[MinimapArrayCorridorThreeCoordinates.Num() - 1].Y + 1)) &&
		!MinimapArrayCorridorFourCoordinates.Contains(FVector2D(MinimapArrayCorridorThreeCoordinates[MinimapArrayCorridorThreeCoordinates.Num() - 1].X - 1, MinimapArrayCorridorThreeCoordinates[MinimapArrayCorridorThreeCoordinates.Num() - 1].Y)) &&
		!MinimapArrayCorridorFourCoordinates.Contains(FVector2D(MinimapArrayCorridorThreeCoordinates[MinimapArrayCorridorThreeCoordinates.Num() - 1].X + 1, MinimapArrayCorridorThreeCoordinates[MinimapArrayCorridorThreeCoordinates.Num() - 1].Y))) {

		if (MinimapArrayCorridorFourCoordinates.Last().X > MinimapArrayCorridorThreeCoordinates.Last().X) {
			MinimapArrayCorridorThreeCoordinates.Add(FVector2D(MinimapArrayCorridorThreeCoordinates.Last().X + 1, MinimapArrayCorridorThreeCoordinates.Last().Y));
		}
		else if (MinimapArrayCorridorFourCoordinates.Last().X < MinimapArrayCorridorThreeCoordinates.Last().X) {
			MinimapArrayCorridorThreeCoordinates.Add(FVector2D(MinimapArrayCorridorThreeCoordinates.Last().X - 1, MinimapArrayCorridorThreeCoordinates.Last().Y));
		}
	}

	// Corridor Segments Five and Seven
	MaxLoopCount = 0;
	while (MinimapArrayCorridorFiveCoordinates[MinimapArrayCorridorFiveCoordinates.Num() - 1].X != MinimapArrayCorridorSevenCoordinates[MinimapArrayCorridorSevenCoordinates.Num() - 1].X && MaxLoopCount < 10) {
		MinimapArrayCorridorFiveCoordinates.Add(FVector2D(MinimapArrayCorridorFiveCoordinates.Last().X + 1, MinimapArrayCorridorFiveCoordinates.Last().Y));

		if (MinimapArrayCorridorFiveCoordinates[MinimapArrayCorridorFiveCoordinates.Num() - 1].X != MinimapArrayCorridorSevenCoordinates[MinimapArrayCorridorSevenCoordinates.Num() - 1].X) {
			MinimapArrayCorridorSevenCoordinates.Add(FVector2D(MinimapArrayCorridorSevenCoordinates.Last().X - 1, MinimapArrayCorridorSevenCoordinates.Last().Y));
		}

		MaxLoopCount++;
	}

	while (!MinimapArrayCorridorSevenCoordinates.Contains(FVector2D(MinimapArrayCorridorFiveCoordinates[MinimapArrayCorridorFiveCoordinates.Num() - 1].X + 1, MinimapArrayCorridorFiveCoordinates[MinimapArrayCorridorFiveCoordinates.Num() - 1].Y)) &&
		!MinimapArrayCorridorSevenCoordinates.Contains(FVector2D(MinimapArrayCorridorFiveCoordinates[MinimapArrayCorridorFiveCoordinates.Num() - 1].X, MinimapArrayCorridorFiveCoordinates[MinimapArrayCorridorFiveCoordinates.Num() - 1].Y - 1)) &&
		!MinimapArrayCorridorSevenCoordinates.Contains(FVector2D(MinimapArrayCorridorFiveCoordinates[MinimapArrayCorridorFiveCoordinates.Num() - 1].X, MinimapArrayCorridorFiveCoordinates[MinimapArrayCorridorFiveCoordinates.Num() - 1].Y + 1))) {

		if (MinimapArrayCorridorSevenCoordinates.Last().Y > MinimapArrayCorridorFiveCoordinates.Last().Y) {
			MinimapArrayCorridorFiveCoordinates.Add(FVector2D(MinimapArrayCorridorFiveCoordinates.Last().X, MinimapArrayCorridorFiveCoordinates.Last().Y + 1));
		}
		else if (MinimapArrayCorridorSevenCoordinates.Last().Y < MinimapArrayCorridorFiveCoordinates.Last().Y) {
			MinimapArrayCorridorFiveCoordinates.Add(FVector2D(MinimapArrayCorridorFiveCoordinates.Last().X, MinimapArrayCorridorFiveCoordinates.Last().Y - 1));
		}
	}

	// Corridor Segments Six and Eight
	MaxLoopCount = 0;
	while (MinimapArrayCorridorSixCoordinates[MinimapArrayCorridorSixCoordinates.Num() - 1].X != MinimapArrayCorridorEightCoordinates[MinimapArrayCorridorEightCoordinates.Num() - 1].X && MaxLoopCount < 10) {
		MinimapArrayCorridorSixCoordinates.Add(FVector2D(MinimapArrayCorridorSixCoordinates.Last().X + 1, MinimapArrayCorridorSixCoordinates.Last().Y));

		if (MinimapArrayCorridorSixCoordinates[MinimapArrayCorridorSixCoordinates.Num() - 1].X != MinimapArrayCorridorEightCoordinates[MinimapArrayCorridorEightCoordinates.Num() - 1].X) {
			MinimapArrayCorridorEightCoordinates.Add(FVector2D(MinimapArrayCorridorEightCoordinates.Last().X - 1, MinimapArrayCorridorEightCoordinates.Last().Y));
		}

		MaxLoopCount++;
	}

	while (!MinimapArrayCorridorEightCoordinates.Contains(FVector2D(MinimapArrayCorridorSixCoordinates[MinimapArrayCorridorSixCoordinates.Num() - 1].X + 1, MinimapArrayCorridorSixCoordinates[MinimapArrayCorridorSixCoordinates.Num() - 1].Y)) &&
		!MinimapArrayCorridorEightCoordinates.Contains(FVector2D(MinimapArrayCorridorSixCoordinates[MinimapArrayCorridorSixCoordinates.Num() - 1].X, MinimapArrayCorridorSixCoordinates[MinimapArrayCorridorSixCoordinates.Num() - 1].Y - 1)) &&
		!MinimapArrayCorridorEightCoordinates.Contains(FVector2D(MinimapArrayCorridorSixCoordinates[MinimapArrayCorridorSixCoordinates.Num() - 1].X, MinimapArrayCorridorSixCoordinates[MinimapArrayCorridorSixCoordinates.Num() - 1].Y + 1))) {

		if (MinimapArrayCorridorEightCoordinates.Last().Y > MinimapArrayCorridorSixCoordinates.Last().Y) {
			MinimapArrayCorridorSixCoordinates.Add(FVector2D(MinimapArrayCorridorSixCoordinates.Last().X, MinimapArrayCorridorSixCoordinates.Last().Y + 1));
		}
		else if (MinimapArrayCorridorEightCoordinates.Last().Y < MinimapArrayCorridorSixCoordinates.Last().Y) {
			MinimapArrayCorridorSixCoordinates.Add(FVector2D(MinimapArrayCorridorSixCoordinates.Last().X, MinimapArrayCorridorSixCoordinates.Last().Y - 1));
		}
	}



	// Test Level Generation Progress
	TArray<FVector2D> FullLevelArrayCoordinates, RoomSetCoordinates, CorridorSetOneCoordinates, CorridorSetTwoCoordinates;

	FullLevelArrayCoordinates.Append(MinimapArrayRoomOneCoordinates);
	FullLevelArrayCoordinates.Append(MinimapArrayRoomTwoCoordinates);
	FullLevelArrayCoordinates.Append(MinimapArrayRoomThreeCoordinates);
	FullLevelArrayCoordinates.Append(MinimapArrayRoomFourCoordinates);
	FullLevelArrayCoordinates.Append(MinimapArrayCorridorOneCoordinates);
	FullLevelArrayCoordinates.Append(MinimapArrayCorridorTwoCoordinates);
	FullLevelArrayCoordinates.Append(MinimapArrayCorridorThreeCoordinates);
	FullLevelArrayCoordinates.Append(MinimapArrayCorridorFourCoordinates);
	FullLevelArrayCoordinates.Append(MinimapArrayCorridorFiveCoordinates);
	FullLevelArrayCoordinates.Append(MinimapArrayCorridorSixCoordinates);
	FullLevelArrayCoordinates.Append(MinimapArrayCorridorSevenCoordinates);
	FullLevelArrayCoordinates.Append(MinimapArrayCorridorEightCoordinates);

	RoomSetCoordinates.Append(MinimapArrayRoomOneCoordinates);
	RoomSetCoordinates.Append(MinimapArrayRoomTwoCoordinates);
	RoomSetCoordinates.Append(MinimapArrayRoomThreeCoordinates);
	RoomSetCoordinates.Append(MinimapArrayRoomFourCoordinates);

	CorridorSetOneCoordinates.Append(MinimapArrayCorridorOneCoordinates);
	CorridorSetOneCoordinates.Append(MinimapArrayCorridorTwoCoordinates);
	CorridorSetOneCoordinates.Append(MinimapArrayCorridorThreeCoordinates);
	CorridorSetOneCoordinates.Append(MinimapArrayCorridorFourCoordinates);

	CorridorSetTwoCoordinates.Append(MinimapArrayCorridorFiveCoordinates);
	CorridorSetTwoCoordinates.Append(MinimapArrayCorridorSixCoordinates);
	CorridorSetTwoCoordinates.Append(MinimapArrayCorridorSevenCoordinates);
	CorridorSetTwoCoordinates.Append(MinimapArrayCorridorEightCoordinates);

	//if (MinimapRoom_Class) {
	//	for (int i = 0; i < FullLevelArrayCoordinates.Num(); i++) {
	//		MinimapRoom_Widget = CreateWidget<UWidgetComponent_MinimapRoom>(GetWorld(), MinimapRoom_Class);
	//		MinimapRoom_Widget->MinimapReference = this;

	//		UUniformGridSlot* MinimapRoom_Slot = LevelGrid->AddChildToUniformGrid(Cast<UWidget>(MinimapRoom_Widget));

	//		MinimapRoom_Slot->SetRow(FullLevelArrayCoordinates[i].Y);
	//		MinimapRoom_Slot->SetColumn(FullLevelArrayCoordinates[i].X);

	//		MinimapRoom_Widget->X_Coordinate = FullLevelArrayCoordinates[i].Y;
	//		MinimapRoom_Widget->Y_Coordinate = FullLevelArrayCoordinates[i].X;

	//		MinimapRoom_Slot->SetHorizontalAlignment(EHorizontalAlignment::HAlign_Fill);
	//		MinimapRoom_Slot->SetVerticalAlignment(EVerticalAlignment::VAlign_Fill);

	//		FullMinimapRoomArray.Add(MinimapRoom_Widget);
	//	}
	//}

	if (MinimapRoom_Class) {
		for (int x = 0; x <= 20; x++) {
			for (int y = 0; y <= 20; y++) {
				MinimapRoom_Widget = CreateWidget<UWidgetComponent_MinimapRoom>(GetWorld(), MinimapRoom_Class);
				MinimapRoom_Widget->MinimapReference = this;

				UUniformGridSlot* MinimapRoom_Slot = LevelGrid->AddChildToUniformGrid(Cast<UWidget>(MinimapRoom_Widget));

				MinimapRoom_Slot->SetRow(y);
				MinimapRoom_Slot->SetColumn(x);

				MinimapRoom_Widget->X_Coordinate = x;
				MinimapRoom_Widget->Y_Coordinate = y;

				MinimapRoom_Slot->SetHorizontalAlignment(EHorizontalAlignment::HAlign_Fill);
				MinimapRoom_Slot->SetVerticalAlignment(EVerticalAlignment::VAlign_Fill);

				//if (CorridorSetOneCoordinates.Contains(FVector2D(x, y))) {
				//	MinimapRoom_Widget->BackgroundImage->SetColorAndOpacity(FLinearColor(1.f, 0.f, 0.f, 1.f));
				//}

				//if (CorridorSetTwoCoordinates.Contains(FVector2D(x, y))) {
				//	MinimapRoom_Widget->BackgroundImage->SetColorAndOpacity(FLinearColor(0.f, 0.f, 1.f, 1.f));
				//}

				if (!FullLevelArrayCoordinates.Contains(FVector2D(x, y))) {
					MinimapRoom_Widget->BackgroundImage->SetVisibility(ESlateVisibility::Hidden);
					MinimapRoom_Widget->InteractButton->SetVisibility(ESlateVisibility::Collapsed);
				} else {
					FullMinimapRoomArray.Add(MinimapRoom_Widget);
				}
			}
		}
	}

	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::White, FString::Printf(TEXT("FullMinimapRoomArray Length: %s"), *FString::FromInt(FullMinimapRoomArray.Num())));

	// Separate the Minimap Tiles into Rooms and Corridors so we can spawn enemies and events.
	TArray<ABaseClass_GridTile*> PlayerSpawnTiles, RoomOneGridTiles, RoomTwoGridTiles, RoomThreeGridTiles, RoomFourGridTiles, CorridorOneGridTiles, CorridorTwoGridTiles, CorridorThreeGridTiles, CorridorFourGridTiles;

	// Spawn Minimap tiles into World
	if (GridTile_Class) {
		for (int i = 0; i < FullMinimapRoomArray.Num(); i++) {
			FVector SpawnLocation = FVector((200 * FullMinimapRoomArray[i]->X_Coordinate) - 200, (200 * FullMinimapRoomArray[i]->Y_Coordinate) - 200, 0);

			GridTile_Actor = GetWorld()->SpawnActor<ABaseClass_GridTile>(GridTile_Class, SpawnLocation, FRotator::ZeroRotator, SpawnParameters);
			GridTile_Actor->X_Coordinate = FullMinimapRoomArray[i]->X_Coordinate;
			GridTile_Actor->Y_Coordinate = FullMinimapRoomArray[i]->Y_Coordinate;

			FullMinimapRoomArray[i]->GridTileReference = GridTile_Actor;
			GridTile_Actor->MinimapRoomReference = FullMinimapRoomArray[i];

			GridTilesArray.Add(GridTile_Actor);

			//if (RoomSetCoordinates.Contains(FVector2D(FullMinimapRoomArray[i]->X_Coordinate, FullMinimapRoomArray[i]->Y_Coordinate))) {
			//	PlayerSpawnTiles.Add(GridTile_Actor);
			//}
			
			if (MinimapArrayRoomOneCoordinates.Contains(FVector2D(GridTile_Actor->X_Coordinate, GridTile_Actor->Y_Coordinate))) {
				RoomOneGridTiles.Add(GridTile_Actor);
				PlayerSpawnTiles.Add(GridTile_Actor);
			} else if (MinimapArrayRoomTwoCoordinates.Contains(FVector2D(GridTile_Actor->X_Coordinate, GridTile_Actor->Y_Coordinate))) {
				RoomTwoGridTiles.Add(GridTile_Actor);
				PlayerSpawnTiles.Add(GridTile_Actor);
			} else if (MinimapArrayRoomThreeCoordinates.Contains(FVector2D(GridTile_Actor->X_Coordinate, GridTile_Actor->Y_Coordinate))) {
				RoomThreeGridTiles.Add(GridTile_Actor);
				PlayerSpawnTiles.Add(GridTile_Actor);
			} else if (MinimapArrayRoomFourCoordinates.Contains(FVector2D(GridTile_Actor->X_Coordinate, GridTile_Actor->Y_Coordinate))) {
				RoomFourGridTiles.Add(GridTile_Actor);
				PlayerSpawnTiles.Add(GridTile_Actor);
			} else if (MinimapArrayCorridorOneCoordinates.Contains(FVector2D(GridTile_Actor->X_Coordinate, GridTile_Actor->Y_Coordinate)) ||
				MinimapArrayCorridorTwoCoordinates.Contains(FVector2D(GridTile_Actor->X_Coordinate, GridTile_Actor->Y_Coordinate))) {
				CorridorOneGridTiles.Add(GridTile_Actor);
			} else if (MinimapArrayCorridorThreeCoordinates.Contains(FVector2D(GridTile_Actor->X_Coordinate, GridTile_Actor->Y_Coordinate)) ||
				MinimapArrayCorridorFourCoordinates.Contains(FVector2D(GridTile_Actor->X_Coordinate, GridTile_Actor->Y_Coordinate))) {
				CorridorTwoGridTiles.Add(GridTile_Actor);
			} else if (MinimapArrayCorridorFiveCoordinates.Contains(FVector2D(GridTile_Actor->X_Coordinate, GridTile_Actor->Y_Coordinate)) ||
				MinimapArrayCorridorSevenCoordinates.Contains(FVector2D(GridTile_Actor->X_Coordinate, GridTile_Actor->Y_Coordinate))) {
				CorridorThreeGridTiles.Add(GridTile_Actor);
			} else if (MinimapArrayCorridorSixCoordinates.Contains(FVector2D(GridTile_Actor->X_Coordinate, GridTile_Actor->Y_Coordinate)) ||
				MinimapArrayCorridorEightCoordinates.Contains(FVector2D(GridTile_Actor->X_Coordinate, GridTile_Actor->Y_Coordinate))) {
				CorridorFourGridTiles.Add(GridTile_Actor);
			}
		}
	}

	// Add an enemy encounter or two to each room
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::White, FString::Printf(TEXT("Generate Encounters")));
	FDataTableRowHandle EnemyFormationsTableRow;

	//for (int i = 0; i < 10; i++) {
	//EnemyFormationsTable->Table = EnemyFormationsTable;
	EnemyFormationsTableRow.DataTable = EnemyFormationsTable;
	EnemyFormationsTableRow.RowName = "Test";

	F_LevelRoom_Encounter NewEncounter("Test", false, EnemyFormationsTableRow);

	//GridTilesArray[FMath::RandRange(0, GridTilesArray.Num() - 1)]->EncountersList.Add(NewEncounter);
	//}

	// Room One
	ABaseClass_GridTile* RoomOneSpawnTile = RoomOneGridTiles[FMath::RandRange(0, RoomOneGridTiles.Num() - 1)];
	RoomOneSpawnTile->EncountersList.Add(NewEncounter);
	for (int i = 0; i < RoomOneGridTiles.Num(); i++) {
		RoomOneGridTiles[i]->OnPlayerEnterTileFunction = E_GridTile_OnPlayerEnterFunctions::E_TriggerBattle;
	}

	// Spawn Player Into a Room at a random tile
	ABaseClass_PlayerController* LocalPlayerControllerRef = Cast<ABaseClass_PlayerController>(GetWorld()->GetFirstPlayerController());
	LocalPlayerControllerRef->ManualBeginPlay();
	LocalPlayerControllerRef->MoveToTile(PlayerSpawnTiles[FMath::RandRange(0, PlayerSpawnTiles.Num() - 1)]);
}


void UBaseClass_Widget_Minimap::GetPlayerNeighbouringTiles(UWidgetComponent_MinimapRoom* CurrentRoomWidget)
{
	PlayerNeighbouringRoomWidgets.Empty();

	for (TObjectIterator<UWidgetComponent_MinimapRoom> Itr; Itr; ++Itr) {
		UWidgetComponent_MinimapRoom* FoundWidget = *Itr;

		// Get immediate neighbours, not including diagonals
		if (FoundWidget->X_Coordinate == CurrentRoomWidget->X_Coordinate + 1 && FoundWidget->Y_Coordinate == CurrentRoomWidget->Y_Coordinate ||
			FoundWidget->X_Coordinate == CurrentRoomWidget->X_Coordinate - 1 && FoundWidget->Y_Coordinate == CurrentRoomWidget->Y_Coordinate ||
			FoundWidget->X_Coordinate == CurrentRoomWidget->X_Coordinate && FoundWidget->Y_Coordinate == CurrentRoomWidget->Y_Coordinate + 1 ||
			FoundWidget->X_Coordinate == CurrentRoomWidget->X_Coordinate && FoundWidget->Y_Coordinate == CurrentRoomWidget->Y_Coordinate - 1) {
			PlayerNeighbouringRoomWidgets.Add(FoundWidget);
			FoundWidget->BackgroundImage->SetColorAndOpacity(FLinearColor(0.f, 1.f, 0.f, 1.f));
		} else if (FoundWidget->X_Coordinate == CurrentRoomWidget->X_Coordinate && FoundWidget->Y_Coordinate == CurrentRoomWidget->Y_Coordinate) {
			FoundWidget->BackgroundImage->SetColorAndOpacity(FLinearColor(0.67f, 0.67f, 0.67f, 0.67f));
		} else {
			FoundWidget->BackgroundImage->SetColorAndOpacity(FLinearColor(1.f, 1.f, 1.f, 1.f));
		}
	}
}