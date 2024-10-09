#include "LostWorldPlayerControllerBattle.h"


#include "ActorEntityPlayer.h"
#include "ActorGridTile.h"


void ALostWorldPlayerControllerBattle::SetupInputComponent()
{
	Super::SetupInputComponent();

	// Setup proper mouse controls
	SetInputMode(FInputModeGameAndUI());
	bShowMouseCursor = true;
	ClickEventKeys.Add(EKeys::RightMouseButton);

	// Bind keys to functions
	InputComponent->BindAction("PlayerMoveNorth", IE_Pressed, this, &ALostWorldPlayerControllerBattle::PlayerMoveNorth);
	InputComponent->BindAction("PlayerMoveSouth", IE_Pressed, this, &ALostWorldPlayerControllerBattle::PlayerMoveSouth);
	InputComponent->BindAction("PlayerMoveEast", IE_Pressed, this, &ALostWorldPlayerControllerBattle::PlayerMoveEast);
	InputComponent->BindAction("PlayerMoveWest", IE_Pressed, this, &ALostWorldPlayerControllerBattle::PlayerMoveWest);
}


// ReSharper disable once CppMemberFunctionMayBeConst
void ALostWorldPlayerControllerBattle::PlayerMoveNorth()
{
	if (ControlledPlayerEntity) {
		int ExpectedXCoordinate = ControlledPlayerEntity->GetActorLocation().X + 200;
		int ExpectedYCoordinate = ControlledPlayerEntity->GetActorLocation().Y;
		
		for (TObjectIterator<AActorGridTile> Itr; Itr; ++Itr) {
			AActorGridTile* FoundTile = *Itr;

			if (FoundTile) {
				if (FoundTile->GetActorLocation().X == ExpectedXCoordinate && FoundTile->GetActorLocation().Y == ExpectedYCoordinate) {
					ControlledPlayerEntity->SetActorLocation(FVector(ExpectedXCoordinate, ExpectedYCoordinate, ControlledPlayerEntity->GetActorLocation().Z));
					break;
				}
			}
		}
	}
}


// ReSharper disable once CppMemberFunctionMayBeConst
void ALostWorldPlayerControllerBattle::PlayerMoveSouth()
{
	if (ControlledPlayerEntity) {
		int ExpectedXCoordinate = ControlledPlayerEntity->GetActorLocation().X - 200;
		int ExpectedYCoordinate = ControlledPlayerEntity->GetActorLocation().Y;
		
		for (TObjectIterator<AActorGridTile> Itr; Itr; ++Itr) {
			AActorGridTile* FoundTile = *Itr;

			if (FoundTile) {
				if (FoundTile->GetActorLocation().X == ExpectedXCoordinate && FoundTile->GetActorLocation().Y == ExpectedYCoordinate) {
					ControlledPlayerEntity->SetActorLocation(FVector(ExpectedXCoordinate, ExpectedYCoordinate, ControlledPlayerEntity->GetActorLocation().Z));
					break;
				}
			}
		}
	}
}


// ReSharper disable once CppMemberFunctionMayBeConst
void ALostWorldPlayerControllerBattle::PlayerMoveEast()
{
	if (ControlledPlayerEntity) {
		int ExpectedXCoordinate = ControlledPlayerEntity->GetActorLocation().X;
		int ExpectedYCoordinate = ControlledPlayerEntity->GetActorLocation().Y + 200;
		
		for (TObjectIterator<AActorGridTile> Itr; Itr; ++Itr) {
			AActorGridTile* FoundTile = *Itr;

			if (FoundTile) {
				if (FoundTile->GetActorLocation().X == ExpectedXCoordinate && FoundTile->GetActorLocation().Y == ExpectedYCoordinate) {
					ControlledPlayerEntity->SetActorLocation(FVector(ExpectedXCoordinate, ExpectedYCoordinate, ControlledPlayerEntity->GetActorLocation().Z));
					break;
				}
			}
		}
	}
}


// ReSharper disable once CppMemberFunctionMayBeConst
void ALostWorldPlayerControllerBattle::PlayerMoveWest()
{
	if (ControlledPlayerEntity) {
		int ExpectedXCoordinate = ControlledPlayerEntity->GetActorLocation().X;
		int ExpectedYCoordinate = ControlledPlayerEntity->GetActorLocation().Y - 200;
		
		for (TObjectIterator<AActorGridTile> Itr; Itr; ++Itr) {
			AActorGridTile* FoundTile = *Itr;

			if (FoundTile) {
				if (FoundTile->GetActorLocation().X == ExpectedXCoordinate && FoundTile->GetActorLocation().Y == ExpectedYCoordinate) {
					ControlledPlayerEntity->SetActorLocation(FVector(ExpectedXCoordinate, ExpectedYCoordinate, ControlledPlayerEntity->GetActorLocation().Z));
					break;
				}
			}
		}
	}
}
