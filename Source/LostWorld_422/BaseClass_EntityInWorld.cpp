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
	StaticMesh->AttachToComponent(RootComponent, AttachRules);
	SpringArm->AttachToComponent(StaticMesh, AttachRules);
	Camera->AttachToComponent(SpringArm, AttachRules);

	//HealthText_WorldRender = CreateDefaultSubobject<UTextRenderComponent>("HealthText_WorldRender");
	//HealthText_WorldRender->AttachToComponent(RootComponent, AttachRules);

	// Initialize Mouse Events
	//StaticMesh->OnBeginCursorOver.AddDynamic(this, &ABaseClass_EntityInWorld::CustomOnBeginMouseOverEvent);

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

	// Rotate TextRenders towards player camera
	//if (!PlayerControllerRef)
	//	PlayerControllerRef = Cast<ABaseClass_PlayerController>(GetWorld()->GetFirstPlayerController());

	//FVector CameraLocation = PlayerControllerRef->PlayerCameraManager->GetCameraLocation();
	//FVector RenderLocation = HealthText_WorldRender->GetComponentLocation();
	//FRotator LookAtRotation = UKismetMathLibrary::FindLookAtRotation(RenderLocation, CameraLocation);
	//// Pitch, Yaw, Roll
	//FRotator CalculatedRotation = FRotator(0, (LookAtRotation.Yaw - 90), ((LookAtRotation.Pitch * -1) + 90));

	//if (HealthText_WorldRender)
	//{
	//	//HealthText_WorldRender->SetWorldRotation(CalculatedRotation);
	//}
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
		EntityInBattleRef->EntityInWorldRef = this;

		if(EntityBaseData.IsPlayerControllable || !PlayerControllerRef)
			PlayerControllerRef = PlayerControllerRef = Cast<ABaseClass_PlayerController>(GetWorld()->GetFirstPlayerController());
	}
}