#include "Level_SpawnTypeBase.h"

#include "BaseClass_GridTile.h"


// Sets default values
ALevel_SpawnTypeBase::ALevel_SpawnTypeBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	// Constructors
	//static ConstructorHelpers::FObjectFinder<ABaseClass_GridTile> GridTile_BlueprintConstruct(TEXT("Blueprint'/Game/Level_GridTile_Blueprint.Level_GridTile_Blueprint'"));
	//if (GridTile_BlueprintConstruct.Object) {
	//	GridTile_Class = (UClass*)GridTile_BlueprintConstruct.Object->StaticClass;
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