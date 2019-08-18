// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseClass_EntityInBattle.h"

#include "BaseClass_EntityInWorld.h"
#include "BaseClass_PlayerController.h"

// Sets default values
ABaseClass_EntityInBattle::ABaseClass_EntityInBattle()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ABaseClass_EntityInBattle::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABaseClass_EntityInBattle::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABaseClass_EntityInBattle::Debug_CreateDefaultDeck()
{
	for (int i = 0; i < 11; i++)
	{
		ALostWorld_422GameModeBase* LocalGameModeRef = (ALostWorld_422GameModeBase*)GetWorld()->GetAuthGameMode();
		FString ContextString;
		TArray<FName> RowNames = LocalGameModeRef->CardDataTableRef->GetRowNames();
		EntityBaseData.CurrentDeck.Add(*LocalGameModeRef->CardDataTableRef->FindRow<FCardBase>(RowNames[0], ContextString));

		EntityBaseData.CurrentDeck[i].Controller = this;
		EntityBaseData.CurrentDeck[i].Owner = this;
		EntityBaseData.CurrentDeck[i].ZoneIndex = i;
	}
}

void ABaseClass_EntityInBattle::Begin_Battle()
{
	int32 RandIndex;

	// Draw seven cards at random
	for (int i = 0; i < 7; i++)
	{
		RandIndex = FMath::RandRange(0, EntityBaseData.CurrentDeck.Num() - 1);
		CardsInHand.Add(EntityBaseData.CurrentDeck[RandIndex]);
		EntityBaseData.CurrentDeck.RemoveAt(RandIndex);

		// Set Indices
		CardsInHand[i].ZoneIndex = i;

		if (!CardsInHand[i].Controller)
			CardsInHand[i].Controller = this;
		if (!CardsInHand[i].Owner)
			CardsInHand[i].Owner = this;
	}

	UpdateCardIndicesInAllZones();
}

void ABaseClass_EntityInBattle::Begin_Turn()
{
	UpdateCardIndicesInAllZones();

	if (EntityBaseData.IsPlayerControllable && EntityInWorldRef->PlayerControllerRef)
	{
		for (int i = 0; i < 7; i++)
		{
			if(i == 0)
				EntityInWorldRef->PlayerControllerRef->Battle_HUD_Widget->CreatePlayerCardsInHandWidgets(true, CardsInHand[i]);
			else
				EntityInWorldRef->PlayerControllerRef->Battle_HUD_Widget->CreatePlayerCardsInHandWidgets(false, CardsInHand[i]);
		}
	}
}

void ABaseClass_EntityInBattle::UpdateCardIndicesInAllZones()
{
	for (int i = 0; i < CardsInHand.Num(); i++)
		CardsInHand[i].ZoneIndex = i;
	
	for (int j = 0; j < CardsInGraveyard.Num(); j++)
		CardsInGraveyard[j].ZoneIndex = j;

	for (int k = 0; k < CardsInDeck.Num(); k++)
		CardsInDeck[k].ZoneIndex = k;
}