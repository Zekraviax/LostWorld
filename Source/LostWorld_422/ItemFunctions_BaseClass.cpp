// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemFunctions_BaseClass.h"

// Sets default values
AItemFunctions_BaseClass::AItemFunctions_BaseClass()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AItemFunctions_BaseClass::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AItemFunctions_BaseClass::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

