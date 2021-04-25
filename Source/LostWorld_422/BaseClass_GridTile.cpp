#include "BaseClass_GridTile.h"

#include "LostWorld_422GameStateBase.h"


// Sets default values
ABaseClass_GridTile::ABaseClass_GridTile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	OnPlayerEnterTileFunction = E_GridTile_OnPlayerEnterFunctions::E_None;
}


// Called when the game starts or when spawned
void ABaseClass_GridTile::BeginPlay()
{
	Super::BeginPlay();
}


// Called every frame
void ABaseClass_GridTile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}


// ------------------------- Mouse
void ABaseClass_GridTile::OnMouseBeginHover()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("Mouse Hover Over Begin"));
}


void ABaseClass_GridTile::OnPlayerEnterTile()
{
	switch (OnPlayerEnterTileFunction) 
	{
		case(E_GridTile_OnPlayerEnterFunctions::E_TriggerBattle):
			// Get GameState Ref
			GetWorld()->GetGameState<ALostWorld_422GameStateBase>()->DebugBattleStart();
			break;
		default:
			break;
	}
}