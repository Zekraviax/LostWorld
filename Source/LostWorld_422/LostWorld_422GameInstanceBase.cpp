#include "LostWorld_422GameInstanceBase.h"

#include "BaseClass_LevelRoom.h"
#include "GameFramework/Actor.h"


// ------------------------- Initializer
//ULostWorld_422GameInstanceBase::ULostWorld_422GameInstanceBase(const FObjectInitializer& ObjectInitializer)
//{
//	// Construct all Room Blueprints
//	static ConstructorHelpers::FObjectFinder<UBlueprint> TestOne_Room_BlueprintConstruct(TEXT("Blueprint'/Game/RoomLayouts/BlueprintChild_Room_TestOne.BlueprintChild_Room_TestOne'"));
//
//	if (TestOne_Room_BlueprintConstruct.Object) {
//		TestOne_Room_Class = (UClass*)TestOne_Room_BlueprintConstruct.Object->GeneratedClass;
//	}
//
//	UE_LOG(LogTemp, Warning, TEXT("GameInstance Constructed"));
//}


void ULostWorld_422GameInstanceBase::SpawnNewRoom(TSubclassOf<ABaseClass_LevelRoom> RoomToSpawnClass, FVector WorldLocation, FRotator WorldRotation)
{
	FActorSpawnParameters SpawnParameters;
	SpawnParameters.bNoFail = true;
	SpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	
	if (GetWorld() && TestOne_Room_Class) {
		Room_Reference = GetWorld()->SpawnActor<ABaseClass_LevelRoom>(TestOne_Room_Class, WorldLocation, WorldRotation, SpawnParameters);
	}
}