#include "ActorGridTile.h"

#include <solver/PxSolverDefs.h>


#include "ActorEntityBase.h"
#include "LostWorldGameModeBase.h"
#include "LostWorldGameModeBattle.h"


// Sets default values
AActorGridTile::AActorGridTile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	// Create the actors' components
	TileStaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Tile"));
	TileStaticMesh->SetRelativeTransform(FTransform(FRotator::ZeroRotator, FVector::ZeroVector, FVector(2.f, 2.f, 1.f)));
	RootComponent = TileStaticMesh;
}

// Called when the game starts or when spawned
void AActorGridTile::BeginPlay()
{
	Super::BeginPlay();

	// Create a dynamic material instance and set the tile material
	DynamicMaterial = UMaterialInstanceDynamic::Create(TileStaticMesh->GetMaterial(0), this);
	TileStaticMesh->SetMaterial(0, DynamicMaterial);
	SetTileColour(FLinearColor(0.15f, 0.15f, 0.15f));
}

// Called every frame
void AActorGridTile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


void AActorGridTile::SetTileColour(FLinearColor NewColour)
{
	TileColour = NewColour;
	DynamicMaterial->SetVectorParameterValue("Color", TileColour);
}


void AActorGridTile::MoveEntityToTile(AActorEntityBase* MovingEntity)
{
	MovingEntity->SetActorLocation(FVector(GetActorLocation().X, GetActorLocation().Y, MovingEntity->GetActorLocation().Z));

	// Once the entity has officially moved to the tile, we can trigger events that happen on movement,
	// like battles starting or collecting items from treasure chests
	switch (Encounter.EncounterType)
	{
		case EEncounterTypes::Enemy:
			// Battle begin!
			Cast<ALostWorldGameModeBattle>(GetWorld()->GetAuthGameMode())->TransitionToBattle(Encounter);
			break;
		default:
			// Do nothing
			break;
	}
}
