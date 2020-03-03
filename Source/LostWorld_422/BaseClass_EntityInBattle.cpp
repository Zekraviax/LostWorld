// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseClass_EntityInBattle.h"

#include "BaseClass_PlayerController.h"
#include "LostWorld_422GameStateBase.h"


// Sets default values
ABaseClass_EntityInBattle::ABaseClass_EntityInBattle()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Initialize Components
	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>("StaticMesh");
	SpringArm = CreateDefaultSubobject<USpringArmComponent>("SpringArm");
	Camera = CreateDefaultSubobject<UCameraComponent>("Camera");
	EntityStats_WidgetComponent = CreateDefaultSubobject<UWidgetComponent>("EntityStats_WidgetComponent");

	StaticMesh->SetupAttachment(RootComponent);
	SpringArm->SetupAttachment(RootComponent);
	Camera->SetupAttachment(SpringArm);
	EntityStats_WidgetComponent->SetupAttachment(RootComponent);
}


// Called when the game starts or when spawned
void ABaseClass_EntityInBattle::BeginPlay()
{
	Super::BeginPlay();

	// Get a reference to the EntityStats proper widget and set the variables
	if (EntityStats_WidgetComponent && EntityStats_WidgetComponent_Class) {
		EntityStats_WidgetComponent_Reference = Cast<UBaseClass_WidgetComponent_Stats>(EntityStats_WidgetComponent->GetUserWidgetObject());

		if (EntityStats_WidgetComponent_Reference)
			EntityStats_WidgetComponent_Reference->LinkedEntity = this;
	}
}


// Called every frame
void ABaseClass_EntityInBattle::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ABaseClass_EntityInBattle::CustomOnBeginMouseOverEvent(UPrimitiveComponent * TouchedComponent)
{

}


void ABaseClass_EntityInBattle::Debug_CreateDefaultDeck()
{
	for (int i = 0; i < 10; i++)
	{
		ALostWorld_422GameModeBase* LocalGameModeRef = (ALostWorld_422GameModeBase*)GetWorld()->GetAuthGameMode();
		FString ContextString;
		TArray<FName> RowNames = LocalGameModeRef->CardDataTableRef->GetRowNames();
		CardsInDeck.Add(*LocalGameModeRef->CardDataTableRef->FindRow<FCardBase>(RowNames[0], ContextString));

		CardsInDeck[i].Controller = this;
		CardsInDeck[i].Owner = this;
		CardsInDeck[i].ZoneIndex = i;
	}
}


void ABaseClass_EntityInBattle::ResetStatsWidget()
{
	EntityStats_WidgetComponent->SetWorldLocation(FVector(this->GetActorLocation().X, this->GetActorLocation().Y, this->GetActorLocation().Z + 150));
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Cyan, TEXT("Reset entity stats widget location."));
}


void ABaseClass_EntityInBattle::Begin_Battle()
{
	int32 RandIndex;

	// Set ownership of all cards
	for (int i = 0; i < CardsInDeck.Num(); i++) {
		CardsInDeck[i].Owner = this;
		CardsInDeck[i].Controller = this;
	}

	// Draw seven cards at random
	for (int i = 0; i < 7; i++)
	{
		RandIndex = FMath::RandRange(0, CardsInDeck.Num() - 1);
		CardsInHand.Add(CardsInDeck[RandIndex]);

		// Set Indices
		CardsInHand[i].ZoneIndex = i;

		// Set Ownership
		if (!CardsInHand[i].Controller) {
			CardsInHand[i].Controller = this;
		}
		if (!CardsInHand[i].Owner == NULL) {
			CardsInHand[i].Owner = this;
		}

		CardsInDeck.RemoveAt(RandIndex);
	}

	UpdateCardIndicesInAllZones();
}


void ABaseClass_EntityInBattle::UpdateCardWidgets()
{
	if (!GameStateRef)
		GameStateRef = GetWorld()->GetGameState<ALostWorld_422GameStateBase>();

	if (EntityBaseData.IsPlayerControllable && GameStateRef->SortedTurnOrderList[0] == this)
	{
		for (int i = 0; i < CardsInHand.Num(); i++)
		{
			if (i == 0)
				PlayerControllerRef->Battle_HUD_Widget->CreatePlayerCardsInHandWidgets(true, CardsInHand[i]);
			else
				PlayerControllerRef->Battle_HUD_Widget->CreatePlayerCardsInHandWidgets(false, CardsInHand[i]);
		}
	}
}


void ABaseClass_EntityInBattle::Begin_Turn()
{
	UpdateCardIndicesInAllZones();
	UpdateCardWidgets();

	EntityBaseData.ManaValues.X_Value = EntityBaseData.ManaValues.Y_Value;

	if (!EntityBaseData.IsPlayerControllable) {
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::White, TEXT("IsPlayerControllable: False"));
		AI_CastRandomCard();
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


void ABaseClass_EntityInBattle::Event_CardCastOnThis()
{
	// Check if entity is dead
	if (EntityBaseData.HealthValues.X_Value <= 0) {
		Destroy();

		// Get GameState
		if (!GameStateRef)
			GameStateRef = GetWorld()->GetGameState<ALostWorld_422GameStateBase>();

		// BattleEvent_EntityDied();
		GameStateRef->Event_EntityDied(this);
	}

	// Check if all entities are/the player is dead
	// In the GameState class
}


void ABaseClass_EntityInBattle::AI_CastRandomCard()
{
	// Get random card in hand
	int32 RandCardIndex = FMath::RandRange(0, CardsInHand.Num() - 1);
	FCardBase RandCard = CardsInHand[RandCardIndex];
	TArray<ABaseClass_EntityInBattle*> RandTargetsArray;

	if (RandCard.Targets.Contains(E_Card_SetTargets::E_CastTarget)) {
		TArray<ABaseClass_EntityInBattle*> TargetsArray;

		for (TActorIterator<ABaseClass_EntityInBattle> ActorItr(GetWorld()); ActorItr; ++ActorItr) {
			ABaseClass_EntityInBattle* FoundEntity = *ActorItr;

			if (FoundEntity->EntityBaseData.IsPlayerControllable != this->EntityBaseData.IsPlayerControllable) {
				TargetsArray.Add(FoundEntity);
			}
		}

		RandCard.CurrentTargets.Add(TargetsArray[FMath::RandRange(0, TargetsArray.Num() - 1)]);
	}

	// Cast card
	if (!GameModeRef)
		GameModeRef = Cast<ALostWorld_422GameModeBase>(GetWorld()->GetAuthGameMode());

	if (!GameStateRef)
		GameStateRef = GetWorld()->GetGameState<ALostWorld_422GameStateBase>();

	// Mana Check
	if (EntityBaseData.ManaValues.X_Value >= RandCard.ManaCost) {
		EntityBaseData.ManaValues.X_Value -= RandCard.ManaCost;
	}
	else {
		GameStateRef->EntityEndOfTurn();
	}

	GameModeRef->CardFunctionLibraryReference->AddCardFunctionsToTheStack(RandCard);
	GetWorldTimerManager().SetTimer(EndTurn_TimerHandle, this, &ABaseClass_EntityInBattle::AI_EndTurnDelay, (RandCard.FunctionsWithRules.Num() + 1), false);
}


void ABaseClass_EntityInBattle::AI_EndTurnDelay()
{
	GameStateRef->EntityEndOfTurn();
}