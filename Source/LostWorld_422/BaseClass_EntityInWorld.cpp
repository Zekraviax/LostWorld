// Fill out your copyright notice in the Description page of Project Settings.

#include "BaseClass_EntityInWorld.h"

#include "EngineUtils.h"
#include "BaseClass_PlayerController.h"
#include "Runtime/Engine/Classes/Kismet/KismetMathLibrary.h"

// Sets default values
ABaseClass_EntityInWorld::ABaseClass_EntityInWorld()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Initialize Components
	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>("StaticMesh");
	SpringArm = CreateDefaultSubobject<USpringArmComponent>("SpringArm");
	Camera = CreateDefaultSubobject<UCameraComponent>("Camera");

	FAttachmentTransformRules AttachRules(EAttachmentRule::KeepWorld, EAttachmentRule::KeepWorld, EAttachmentRule::KeepWorld, true);
	AttachRules.bWeldSimulatedBodies = false;

	StaticMesh->SetupAttachment(RootComponent);
	SpringArm->SetupAttachment(RootComponent);
	Camera->SetupAttachment(SpringArm);

	// Create EntityInBattle Ref
	static ConstructorHelpers::FObjectFinder<UBlueprint>EntityInBattleBlueprintConstruct(TEXT("Blueprint'/Game/Blueprint_EntityInBattle.Blueprint_EntityInBattle'"));

	if (EntityInBattleBlueprintConstruct.Object) {
		EntityInBattle_Class = (UClass*)EntityInBattleBlueprintConstruct.Object->GeneratedClass;
	}
}

// Called when the game starts or when spawned
void ABaseClass_EntityInWorld::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void ABaseClass_EntityInWorld::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABaseClass_EntityInWorld::CustomOnBeginMouseOverEvent(UPrimitiveComponent* TouchedComponent)
{
	//if(GEngine)
}

void ABaseClass_EntityInWorld::CreateEntityInBattle()
{
	// Create the player EntityInBattle
	if (!EntityInBattleRef && EntityInBattle_Class)
	{
		UWorld* const World = GetWorld(); // get a reference to the world
		FActorSpawnParameters SpawnParameters;
		EntityInBattleRef = World->SpawnActor<ABaseClass_EntityInBattle>(EntityInBattle_Class, SpawnParameters);

		if(EntityBaseData.IsPlayerControllable || !PlayerControllerRef)
			PlayerControllerRef = PlayerControllerRef = Cast<ABaseClass_PlayerController>(GetWorld()->GetFirstPlayerController());
	}
}