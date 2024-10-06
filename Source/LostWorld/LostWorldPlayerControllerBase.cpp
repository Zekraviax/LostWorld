#include "LostWorldPlayerControllerBase.h"


#include "ActorEntityPlayer.h"
#include "ActorGridTile.h"


void ALostWorldPlayerControllerBase::SetupInputComponent()
{
	Super::SetupInputComponent();

	// Setup proper mouse controls
	SetInputMode(FInputModeGameAndUI());
	bShowMouseCursor = true;
	ClickEventKeys.Add(EKeys::RightMouseButton);

	// Bind keys to functions
	InputComponent->BindAction("PlayerMoveNorth", IE_Pressed, this, &ALostWorldPlayerControllerBase::PlayerMoveNorth);
}


void ALostWorldPlayerControllerBase::PlayerMoveNorth()
{
	if (ControlledPlayerEntity) {
		int ExpectedXCoordinate = ControlledPlayerEntity->GetActorLocation().X + 200;
		int ExpectedYCoordinate = ControlledPlayerEntity->GetActorLocation().Y;
		
		for (TObjectIterator<AActorGridTile> Itr; Itr; ++Itr) {
			AActorGridTile* FoundTile = *Itr;

			if (FoundTile) {
				if (FoundTile->GetActorLocation().X + 200 == ExpectedXCoordinate && FoundTile->GetActorLocation().Y == ExpectedYCoordinate) {
					ControlledPlayerEntity->SetActorLocation(FVector(ExpectedXCoordinate, ExpectedYCoordinate, ControlledPlayerEntity->GetActorLocation().Z));
					break;
				}
			}
		}
	}
}
