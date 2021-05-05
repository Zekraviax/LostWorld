#include "Level_SpawnTypeBase.h"

#include "BaseClass_LevelRoom.h"


// Sets default values
ALevel_SpawnTypeBase::ALevel_SpawnTypeBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	// Constructors
	//static ConstructorHelpers::FObjectFinder<ABaseClass_LevelRoom> LevelRoom_BlueprintConstruct(TEXT("Blueprint'/Game/Level_Room_Blueprint.Level_Room_Blueprint'"));
	//if (LevelRoom_BlueprintConstruct.Object) {
	//	LevelRoom_Class = (UClass*)LevelRoom_BlueprintConstruct.Object->StaticClass;
	//}
}

// Called when the game starts or when spawned
void ALevel_SpawnTypeBase::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ALevel_SpawnTypeBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


// ------------------------- Base Class Functions
void ALevel_SpawnTypeBase::RunLevelGeneratorFunction()
{

}