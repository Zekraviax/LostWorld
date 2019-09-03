// Fill out your copyright notice in the Description page of Project Settings.


#include "LostWorld_422GameStateBase.h"

#include "EngineUtils.h"


void ALostWorld_422GameStateBase::DebugBattleStart()
{
	if (!PlayerControllerRef)
		PlayerControllerRef = Cast<ABaseClass_PlayerController>(GetWorld()->GetFirstPlayerController());

	if (PlayerControllerRef->CurrentEntityData.CurrentDeck.Num() < 10)
		GEngine->AddOnScreenDebugMessage(-1, 2.5f, FColor::Cyan, TEXT("Error: Not Enough Cards In Deck"));
	else
	{
		SortedTurnOrderList.Empty();

		// Spawn Player's EntityInBattle and add it to the turn order first
		PlayerControllerRef->EntityInBattleRef->CardsInDeck = PlayerControllerRef->CurrentEntityData.CurrentDeck;
		SortedTurnOrderList.Add(PlayerControllerRef->EntityInBattleRef);

		// Spawn every other entity's EntityInBattle and add them to the turn order last
		for (TActorIterator<ABaseClass_EntityInBattle> ActorItr(GetWorld()); ActorItr; ++ActorItr)
		{
			ABaseClass_EntityInBattle* FoundEntity = *ActorItr;

			if (FoundEntity != PlayerControllerRef->EntityInBattleRef) {
				// Give an entity a default deck if they have no cards
				if (FoundEntity->EntityBaseData.CurrentDeck.Num() <= 0) {
					FoundEntity->Debug_CreateDefaultDeck();
					FoundEntity->EntityBaseData.CurrentDeck = FoundEntity->CardsInDeck;
				}

				SortedTurnOrderList.Add(FoundEntity);
			}
		}

		for (TActorIterator<ABaseClass_EntityInBattle> EntityItr(GetWorld()); EntityItr; ++EntityItr)
		{
			ABaseClass_EntityInBattle* BattleEntity = *EntityItr;

			BattleEntity->ShuffleCardsInDeck_BP();
			BattleEntity->Begin_Battle();
		}

		SortedTurnOrderList[0]->Begin_Turn();
	}
}


void ALostWorld_422GameStateBase::EntityBeginTurn_Delay()
{
	SortedTurnOrderList[0]->Begin_Turn();
}


void ALostWorld_422GameStateBase::EntityEndOfTurn()
{
	SortedTurnOrderList.RemoveAt(0);

	if (SortedTurnOrderList.Num() <= 0)
		GetWorldTimerManager().SetTimer(BeginTurnTimerHandle, this, &ALostWorld_422GameStateBase::NewCombatRound, 0.5f, false);
	else
		GetWorldTimerManager().SetTimer(BeginTurnTimerHandle, this, &ALostWorld_422GameStateBase::EntityBeginTurn_Delay, 1.f, false);
}


void ALostWorld_422GameStateBase::NewCombatRound()
{
	// Player always goes first
	for (TActorIterator<ABaseClass_EntityInBattle> ActorItr(GetWorld()); ActorItr; ++ActorItr)
	{
		ABaseClass_EntityInBattle* FoundEntity = *ActorItr;
		if (FoundEntity->EntityBaseData.IsPlayerControllable) {
			SortedTurnOrderList.Add(FoundEntity);
		}
	}

	// Enemies move after the player
	for (TActorIterator<ABaseClass_EntityInBattle> ActorItr(GetWorld()); ActorItr; ++ActorItr)
	{
		ABaseClass_EntityInBattle* FoundEntity = *ActorItr;
		if (!FoundEntity->EntityBaseData.IsPlayerControllable) {
			SortedTurnOrderList.Add(FoundEntity);
		}
	}

	GetWorldTimerManager().SetTimer(BeginTurnTimerHandle, this, &ALostWorld_422GameStateBase::EntityBeginTurn_Delay, 0.5f, false);
}