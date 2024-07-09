#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"

#include "BaseClass_CardFunctionsLibrary.h"

#include "BaseClass_DefaultPawn.generated.h"


UCLASS()
class LOSTWORLD_422_API ABaseClass_DefaultPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ABaseClass_DefaultPawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

// Base Variables
// --------------------------------------------------

// ------------------------- Reference
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<class ALibrary_CardFunctions> CardFunctionsLibraryClass;

	UPROPERTY()
	ALibrary_CardFunctions* CardFunctionsLibraryActorRef;
};
