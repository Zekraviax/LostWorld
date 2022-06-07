#include "LostWorld_422GameInstanceBase.h"

#include "BaseClass_LevelRoom.h"
#include "GameFramework/Actor.h"


void ULostWorld_422GameInstanceBase::SpawnNewRoom(TSubclassOf<ABaseClass_LevelRoom> RoomToSpawnClass, FVector WorldLocation, FRotator WorldRotation)
{
	FActorSpawnParameters SpawnParameters;
	SpawnParameters.bNoFail = true;
	SpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	
	if (GetWorld() && TestOne_Room_Class) {
		Room_Reference = GetWorld()->SpawnActor<ABaseClass_LevelRoom>(TestOne_Room_Class, WorldLocation, WorldRotation, SpawnParameters);
	}
}


// ------------------------- Inventory
UWidget_Inventory_Base* ULostWorld_422GameInstanceBase::GetInventory()
{
	UWorld* World = GEngine->GameViewport->GetWorld();

	if (!IsValid(Inventory_Reference)) {
		Inventory_Reference = CreateWidget<UWidget_Inventory_Base>(World, Inventory_Class);
	}

	return Inventory_Reference;
}