#include "BaseClass_GridTile.h"

#include "LostWorld_422GameStateBase.h"


// Sets default values
ABaseClass_GridTile::ABaseClass_GridTile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	OnPlayerEnterTileFunction = E_GridTile_OnPlayerEnterFunctions::E_None;

	Tile = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Tile"));
	Tile->SetupAttachment(RootComponent);
	Tile->SetRelativeTransform(FTransform(FRotator::ZeroRotator, FVector::ZeroVector, FVector(2.f, 2.f, 1.f)));
}


// Called when the game starts or when spawned
void ABaseClass_GridTile::BeginPlay()
{
	Super::BeginPlay();

	// Dynamic Material Instance
	DynamicMaterial = UMaterialInstanceDynamic::Create(Tile->GetMaterial(0), this);
	Tile->SetMaterial(0, DynamicMaterial);
}


// Called every frame
void ABaseClass_GridTile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}


// ------------------------- Grid Tile
void ABaseClass_GridTile::OnPlayerEnterTile()
{
	switch (OnPlayerEnterTileFunction) 
	{
		case(E_GridTile_OnPlayerEnterFunctions::E_TriggerBattle):
			GetWorld()->GetGameState<ALostWorld_422GameStateBase>()->DebugBattleStart(EncountersList[0]);
			break;
		case(E_GridTile_OnPlayerEnterFunctions::E_Stairs):
			break;
		default:
			break;
	}
}