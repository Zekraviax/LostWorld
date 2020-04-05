#include "BaseClass_DefaultPawn.h"


// Sets default values
ABaseClass_DefaultPawn::ABaseClass_DefaultPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ABaseClass_DefaultPawn::BeginPlay()
{
	Super::BeginPlay();

	if (CardFunctionsLibraryClass && !CardFunctionsLibraryActorRef)
	{
		UWorld* const World = GetWorld(); // get a reference to the world
		FActorSpawnParameters SpawnParameters;
		CardFunctionsLibraryActorRef= World->SpawnActor<ABaseClass_CardFunctionsLibrary>(CardFunctionsLibraryClass, SpawnParameters);

		if (CardFunctionsLibraryActorRef)
			Cast<ALostWorld_422GameModeBase>(GetWorld()->GetAuthGameMode())->CardFunctionLibraryReference = CardFunctionsLibraryActorRef;
	}
}

// Called every frame
void ABaseClass_DefaultPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ABaseClass_DefaultPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}