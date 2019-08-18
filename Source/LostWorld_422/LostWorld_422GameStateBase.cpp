// Fill out your copyright notice in the Description page of Project Settings.


#include "LostWorld_422GameStateBase.h"

#include "EngineUtils.h"


void ALostWorld_422GameStateBase::DebugBattleStart()
{
	if (!PlayerControllerRef)
		PlayerControllerRef = Cast<ABaseClass_PlayerController>(GetWorld()->GetFirstPlayerController());

	if (PlayerControllerRef->CurrentEntityData.CurrentDeck.Num() < 10)
	{
		GEngine->AddOnScreenDebugMessage(-1, 2.5f, FColor::Cyan, TEXT("Error: Not Enough Cards In Deck"));
	}
	else
	{
		SortedTurnOrderList.Empty();

		// Spawn Player's EntityInBattle and add it to the turn order first
		PlayerControllerRef->EntityInWorldRef->CreateEntityInBattle();
		SortedTurnOrderList.Add(PlayerControllerRef->EntityInWorldRef->EntityInBattleRef);

		// Spawn every other entity's EntityInBattle and add them to the turn order last
		for (TActorIterator<ABaseClass_EntityInWorld> ActorItr(GetWorld()); ActorItr; ++ActorItr)
		{
			ABaseClass_EntityInWorld* FoundEntity = *ActorItr;
			FoundEntity->CreateEntityInBattle();

			// Set EntityInBattle data
			FoundEntity->EntityInBattleRef->EntityBaseData = FoundEntity->EntityBaseData;

			if (FoundEntity->EntityInBattleRef != PlayerControllerRef->EntityInWorldRef->EntityInBattleRef)
				SortedTurnOrderList.Add(FoundEntity->EntityInBattleRef);
		}

		for (TActorIterator<ABaseClass_EntityInBattle> EntityItr(GetWorld()); EntityItr; ++EntityItr)
		{
			ABaseClass_EntityInBattle* BattleEntity = *EntityItr;

			// Give an entity a default deck if they have no cards
			if (BattleEntity->EntityBaseData.CurrentDeck.Num() <= 0)
				BattleEntity->Debug_CreateDefaultDeck();
			

			BattleEntity->CardsInDeck = BattleEntity->EntityBaseData.CurrentDeck;
			BattleEntity->ShuffleCardsInDeck_BP();
			BattleEntity->Begin_Battle();
		}

		SortedTurnOrderList[0]->Begin_Turn();
	}
}

void ALostWorld_422GameStateBase::EntityEndOfTurn()
{
	SortedTurnOrderList.RemoveAt(0);

	if (SortedTurnOrderList.Num() <= 0)
		NewCombatRound();
	else
		SortedTurnOrderList[0]->Begin_Turn();
}

void ALostWorld_422GameStateBase::NewCombatRound()
{
	TArray<ABaseClass_EntityInBattle> PlayerEntities;
	TArray<ABaseClass_EntityInBattle> EnemyEntities;

	for (TActorIterator<ABaseClass_EntityInWorld> ActorItr(GetWorld()); ActorItr; ++ActorItr)
	{
		ABaseClass_EntityInWorld* FoundEntity = *ActorItr;

		if (FoundEntity->PlayerControllerRef)
			PlayerEntities.Add(FoundEntity->EntityInBattleRef);
		else
			EnemyEntities.Add(FoundEntity->EntityInBattleRef);
	}

	for (int i = 0; i < PlayerEntities.Num(); i++)
		//SortedTurnOrderList.Add(PlayerEntities[i]);

	for (int j = 0; j < EnemyEntities.Num(); j++)
		//SortedTurnOrderList.Add(EnemyEntities[j]);

	SortedTurnOrderList[0]->Begin_Turn();
}