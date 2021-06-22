#include "BaseClass_GridTile.h"

#include "LostWorld_422GameStateBase.h"
#include "BaseClass_PlayerController.h"


// Sets default values
ABaseClass_GridTile::ABaseClass_GridTile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	OnPlayerEnterTileFunction = E_GridTile_OnPlayerEnterTileFunctions_Enum::E_None;

	Tile = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Tile"));
	//Tile->SetupAttachment(RootComponent);
	Tile->SetRelativeTransform(FTransform(FRotator::ZeroRotator, FVector::ZeroVector, FVector(2.f, 2.f, 1.f)));

	RootComponent = Tile;
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
void ABaseClass_GridTile::OnPlayerEnterTile(ABaseClass_PlayerController* PlayerControllerReference)
{
	if (OnPlayerEnterTileFunction == E_GridTile_OnPlayerEnterTileFunctions_Enum::E_TriggerBattle) {
		// Stop the player from moving normally
		PlayerControllerReference->ControlMode = E_Player_ControlMode::E_Battle;
	}

	GetWorldTimerManager().SetTimer(TileFunctionsTimerHandle, this, &ABaseClass_GridTile::RunTileFunctions, 0.2f, false);
}


void ABaseClass_GridTile::RunTileFunctions()
{
	switch (OnPlayerEnterTileFunction)
	{
	case(E_GridTile_OnPlayerEnterTileFunctions_Enum::E_TriggerBattle):
		GetWorld()->GetGameState<ALostWorld_422GameStateBase>()->DebugBattleStart(EncountersList[0]);
		break;
	case(E_GridTile_OnPlayerEnterTileFunctions_Enum::E_Stairs):
		GetWorld()->GetGameState<ALostWorld_422GameStateBase>()->RegenerateLevel();
		break;
	default:
		break;
	}
}