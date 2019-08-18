// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseClass_GridTile.h"

// Sets default values
ABaseClass_GridTile::ABaseClass_GridTile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Initialize Components
	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>("StaticMesh");
	RootComponent = StaticMesh;
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

