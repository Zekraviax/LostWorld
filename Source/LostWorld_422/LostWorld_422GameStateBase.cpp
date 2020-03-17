#include "LostWorld_422GameStateBase.h"

#include "EngineUtils.h"
#include "BaseClass_EntityInBattle.h"
#include "BaseClass_PlayerController.h"


//-------------------- Base --------------------//
//ALostWorld_422GameStateBase::ALostWorld_422GameStateBase()
//{
//
//}


//-------------------- Battle --------------------//
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

		// Spawn every other entity's decks
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


void ALostWorld_422GameStateBase::AddCardFunctionsToTheStack(FCardBase Card)
{
	FCardBase NewStackEntry;
	NewStackEntry.Art = Card.Art;
	NewStackEntry.Controller = Card.Controller;
	//NewStackEntry.CurrentTargets = Card.CurrentTargets;
	NewStackEntry.DisplayName = Card.DisplayName;
	NewStackEntry.Elements = Card.Elements;
	NewStackEntry.ManaCost = Card.ManaCost;
	NewStackEntry.Owner = Card.Owner;
	NewStackEntry.Type = Card.Type;

	for (int i = 0; i < Card.AbilitiesAndConditions.Num(); i++) {
		NewStackEntry.Description = Card.Description;
		NewStackEntry.CurrentTargets = Card.CurrentTargets;
		NewStackEntry.AbilitiesAndConditions.Add(Card.AbilitiesAndConditions[i]);
		TheStack.Add(NewStackEntry);
	}

	// Start timer for the stack
	ExecuteCardFunctions();
	//GetWorldTimerManager().SetTimer(StackTimerHandle, this, &ALostWorld_422GameStateBase::ExecuteCardFunctions, 2.f);
}


void ALostWorld_422GameStateBase::ExecuteCardFunctions()
{
	// Spawn ability actor
	FActorSpawnParameters SpawnParameters;
	SpawnParameters.bNoFail = true;
	SpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	if (GetWorld()) {
		CardAbilityActor_Reference = GetWorld()->SpawnActor<ACardAbilityActor_BaseClass>(TheStack[TheStack.Num() - 1].AbilitiesAndConditions[0].Ability, FVector::ZeroVector, FRotator::ZeroRotator, SpawnParameters);
		CardAbilityActor_Reference->RunCardAbilityFunction(TheStack[TheStack.Num() - 1]);
		//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("Cast card: " + TheStack[TheStack.Num() - 1].AbilitiesAndConditions[0].Ability.Get()->GetName()));
	}
}


void ALostWorld_422GameStateBase::Event_EntityDied(ABaseClass_EntityInBattle* DeadEntity)
{
	TArray<ABaseClass_EntityInBattle*> CurrentAliveEnemyEntities;
	ABaseClass_PlayerController* LocalPlayerControllerRef = Cast<ABaseClass_PlayerController>(GetWorld()->GetFirstPlayerController());

	// Check if entity that died is the player
	// If it isn't the player, check if all enemies are dead instead
	if (DeadEntity->PlayerControllerRef) {
		GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Red, TEXT("Game Over."));
	}
	else {
		for (TActorIterator<ABaseClass_EntityInBattle> ActorItr(GetWorld()); ActorItr; ++ActorItr) {
			ABaseClass_EntityInBattle* FoundEntity = *ActorItr;

			if (!FoundEntity->EntityBaseData.IsPlayerControllable) {
				CurrentAliveEnemyEntities.Add(FoundEntity);
			}
		}

		// If all enemies are dead, end the battle
		if (CurrentAliveEnemyEntities.Num() <= 0) {
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Cyan, TEXT("All Enemies Defeated."));

			// Remove the Encounter from the list
			for (int i = 0; i < LocalPlayerControllerRef->CurrentRoom->EncountersList.Num(); i++) {
				if (LocalPlayerControllerRef->CurrentRoom->EncountersList[i].CurrentlyActiveEncounter) {
					LocalPlayerControllerRef->CurrentRoom->EncountersList.RemoveAt(i);
				}
			}

			// Return the player to the Room
			LocalPlayerControllerRef->ExitBattle();
		}
	}
}