#include "BaseClass_EntityInBattle.h"

#include "BaseClass_PlayerController.h"
#include "BaseClass_GridTile.h"
#include "Widget_CustomConsole_Base.h"
#include "ItemFunctions_BaseClass.h"
#include "StatusFunctions_BaseClass.h"
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

	FAttachmentTransformRules AttachRules = FAttachmentTransformRules(EAttachmentRule::KeepWorld, EAttachmentRule::KeepWorld, EAttachmentRule::KeepWorld, true);
	// Attach components to entity
	EntityStats_WidgetComponent->AttachToComponent(RootComponent, AttachRules);
	SpringArm->AttachToComponent(RootComponent, AttachRules);

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


void ABaseClass_EntityInBattle::Debug_CreateDefaultDeck()
{
	ALostWorld_422GameModeBase* LocalGameModeRef = (ALostWorld_422GameModeBase*)GetWorld()->GetAuthGameMode();
	FString ContextString;
	TArray<FName> RowNames = LocalGameModeRef->CardDataTableRef->GetRowNames();

	for (int i = 0; i < 10; i++) {
		CardsInDeck.Add(*LocalGameModeRef->CardDataTableRef->FindRow<FCardBase>(RowNames[1], ContextString));

		CardsInDeck[i].Controller = this;
		CardsInDeck[i].Owner = this;
		CardsInDeck[i].ZoneIndex = i;
	}
}


void ABaseClass_EntityInBattle::ResetComponentsLocations()
{
	SpringArm->SetWorldLocation(FVector(this->GetActorLocation().X, this->GetActorLocation().Y, this->GetActorLocation().Z));
	EntityStats_WidgetComponent->SetWorldLocation(FVector(this->GetActorLocation().X, this->GetActorLocation().Y, this->GetActorLocation().Z + 150));
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
		if (CardsInHand[i].Controller != this) {
			CardsInHand[i].Controller = this;
		}
		if (CardsInHand[i].Owner != this) {
			CardsInHand[i].Owner = this;
		}

		CardsInDeck.RemoveAt(RandIndex);
	}

	UpdateCardIndicesInAllZones();
	UpdateCardVariables();
}


void ABaseClass_EntityInBattle::UpdateCardVariables()
{
	TArray<FCardBase> AllCards;
	AllCards.Append(CardsInGraveyard);
	AllCards.Append(CardsInHand);

	for (int d = 0; d < CardsInDeck.Num(); d++) {
		AllCards.Add_GetRef(CardsInDeck[d]);
	}

	for (int i = 0; i < CardsInHand.Num(); i++) {
		CardsInHand[i].AbilitiesAndConditions[0].CalculatedBarrier = CardsInHand[i].AbilitiesAndConditions[0].BaseBarrier;
		CardsInHand[i].AbilitiesAndConditions[0].CalculatedDraw = CardsInHand[i].AbilitiesAndConditions[0].BaseDraw;
		CardsInHand[i].AbilitiesAndConditions[0].CalculatedHealing = CardsInHand[i].AbilitiesAndConditions[0].BaseHealing + EntityBaseData.CoreStats.Wisdom;

		if (CardsInHand[i].AbilitiesAndConditions[0].DamageType == E_Card_DamageTypes::E_Physical) {
			CardsInHand[i].AbilitiesAndConditions[0].CalculatedDamage = (EntityBaseData.CoreStats.Strength + CardsInHand[i].AbilitiesAndConditions[0].BaseDamage);
		} else if (CardsInHand[i].AbilitiesAndConditions[0].DamageType == E_Card_DamageTypes::E_Magical) {
			CardsInHand[i].AbilitiesAndConditions[0].CalculatedDamage = EntityBaseData.CoreStats.Intelligence + CardsInHand[i].AbilitiesAndConditions[0].BaseDamage;
		} else {
			CardsInHand[i].AbilitiesAndConditions[0].CalculatedDamage = CardsInHand[i].AbilitiesAndConditions[0].BaseDamage;
		}
	}
}


void ABaseClass_EntityInBattle::UpdateCardWidgets()
{
	if (!GameStateRef)
		GameStateRef = GetWorld()->GetGameState<ALostWorld_422GameStateBase>();

	if (EntityBaseData.IsPlayerControllable && GameStateRef->SortedTurnOrderList[0] == this) {
		for (int i = 0; i < CardsInHand.Num(); i++) {
			if (i == 0)
				PlayerControllerRef->Battle_HUD_Widget->CreatePlayerCardsInHandWidgets(true, CardsInHand[i]);
			else
				PlayerControllerRef->Battle_HUD_Widget->CreatePlayerCardsInHandWidgets(false, CardsInHand[i]);
		}
	}
}


void ABaseClass_EntityInBattle::Begin_Turn()
{
	if (Cast<ABaseClass_PlayerController>(GetWorld()->GetFirstPlayerController())->CustomConsole_Reference->IsValidLowLevel()) {
		Cast<ABaseClass_PlayerController>(GetWorld()->GetFirstPlayerController())->CustomConsole_Reference->AddEntry(EntityBaseData.DisplayName + "'s turn begins.");
	}

	// Draw cards to hand size
	if (CardsInHand.Num() < EntityBaseData.HandSize) {
		for (int i = CardsInHand.Num(); i < EntityBaseData.HandSize; i++) {
			Event_DrawCard();
		}
	}

	// Regenerate mana
	EntityBaseData.ManaValues.X_Value += EntityBaseData.ManaRegenPerTurn;
	if (EntityBaseData.ManaValues.X_Value > EntityBaseData.ManaValues.Y_Value) {
		EntityBaseData.ManaValues.X_Value = EntityBaseData.ManaValues.Y_Value;
	}

	if (EquippedItems.Num() > 0) {
		// Spawn ability actor
		FActorSpawnParameters SpawnParameters;
		SpawnParameters.bNoFail = true;
		SpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

		for (int i = 0; i < EquippedItems.Num(); i++) {
			AItemFunctions_BaseClass* ItemAbilityActor_Reference = GetWorld()->SpawnActor<AItemFunctions_BaseClass>(EquippedItems[i].Functions, FVector::ZeroVector, FRotator::ZeroRotator, SpawnParameters);

			ItemAbilityActor_Reference->TriggeredFunction_StarterOfWearerTurn(this);

			ItemAbilityActor_Reference->ConditionalBeginDestroy();
		}
	}

	// Set camera to focus on this entity?

	// Activate all Status Effect StartOfTurn Functions
	if (StatusEffects.Num() > 0) {
		FActorSpawnParameters SpawnParameters;

		for (int i = StatusEffects.Num() - 1; i >= 0; i--) {
			AStatusFunctions_BaseClass* StatusEffectActor_Reference = GetWorld()->SpawnActor<AStatusFunctions_BaseClass>(StatusEffects[i].StatusFunctions, FVector::ZeroVector, FRotator::ZeroRotator, SpawnParameters);

			StatusEffectActor_Reference->TriggeredFunction_StartOfEntityTurn(this);

			StatusEffectActor_Reference->ConditionalBeginDestroy();
		}
	}


	// If player controllable, take control of the entity
	// Else, cast a random card
	if (EntityBaseData.IsPlayerControllable) {
		Cast<ABaseClass_PlayerController>(GetWorld()->GetFirstPlayerController())->EntityInBattleRef = this;
		PlayerControllerRef = Cast<ABaseClass_PlayerController>(GetWorld()->GetFirstPlayerController());

		PlayerControllerRef->Battle_HUD_Widget->CurrentControlledEntityReference = this;
	} else {
		AI_CastRandomCard();
	}

	UpdateCardIndicesInAllZones();

	UpdateCardWidgets();

	UpdateCardVariables();
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


// ------------------------- Events
void ABaseClass_EntityInBattle::Event_EntitySpawnedInWorld()
{
	// Add Constitution to HP
	EntityBaseData.HealthValues.Y_Value += EntityBaseData.CoreStats.Constitution;
	EntityBaseData.HealthValues.X_Value = EntityBaseData.HealthValues.Y_Value;
}


void ABaseClass_EntityInBattle::Event_DrawCard()
{
	// Check if there are any cards in deck
	// If not, shuffle the graveyard into the deck
	if (CardsInDeck.Num() <= 0) {
		if (CardsInGraveyard.Num() > 0) {
			for (int i = 0; i < CardsInGraveyard.Num(); i++) {
				CardsInDeck.Add(CardsInGraveyard[i]);
			}

			CardsInGraveyard.Empty();
			ShuffleCardsInDeck_BP();
		}
	}

	CardsInHand.Add(CardsInDeck[0]);
	CardsInDeck.RemoveAt(0);

	UpdateCardIndicesInAllZones();
	UpdateCardWidgets();
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

	// Check if all entities are/or the player is dead in the GameState class
}


void ABaseClass_EntityInBattle::Event_StatusEffectIncoming(F_StatusEffect_Base IncomingStatusEffect)
{
	StatusEffects.Add(IncomingStatusEffect);
}


void ABaseClass_EntityInBattle::Event_DamageIncoming(int IncomingDamage, E_Card_Elements ElementType, E_Card_DamageTypes DamageType)
{
	int DamageValue = IncomingDamage;

	if (StatusEffects.Num() > 0) {
		FActorSpawnParameters SpawnParameters;

		for (int i = 0; i < StatusEffects.Num(); i++) {
			AStatusFunctions_BaseClass* StatusFunctionActor_Reference = GetWorld()->SpawnActor<AStatusFunctions_BaseClass>(StatusEffects[i].StatusFunctions, FVector::ZeroVector, FRotator::ZeroRotator, SpawnParameters);
			
			DamageValue = StatusFunctionActor_Reference->TriggeredFunction_EntityAboutToTakeDamage(this, DamageValue);

			StatusFunctionActor_Reference->ConditionalBeginDestroy();
		}
	}

	// Apply damage

	// Barrier
	if (EntityBaseData.Barrier > 0) {
		int TemporaryBarrierVariable = EntityBaseData.Barrier;

		for (int i = 0; i < TemporaryBarrierVariable; i++) {
			if (EntityBaseData.Barrier > 0 && DamageValue > 0) {
				EntityBaseData.Barrier--;
				DamageValue--;
			}
		}
	}

	if (DamageValue > 0) {
		EntityBaseData.HealthValues.X_Value -= DamageValue;

		if (Cast<ABaseClass_PlayerController>(GetWorld()->GetFirstPlayerController())->CustomConsole_Reference->IsValidLowLevel()) {
			Cast<ABaseClass_PlayerController>(GetWorld()->GetFirstPlayerController())->CustomConsole_Reference->AddEntry(EntityBaseData.DisplayName + " takes " + FString::FromInt(DamageValue) + " damage.");
		}

		Event_HealthChanged();
	}
}


void ABaseClass_EntityInBattle::Event_HealthChanged()
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

	// Check if all entities are/or the player is dead in the GameState class
}


void ABaseClass_EntityInBattle::Event_HealingIncoming(int IncomingHealing)
{
	int HealingValue = IncomingHealing;

	EntityBaseData.HealthValues.X_Value += HealingValue;
	Event_CardCastOnThis();
}


void ABaseClass_EntityInBattle::Event_BarrierIncoming(int IncomingBarrier)
{
	int BarrierValue = IncomingBarrier;

	EntityBaseData.Barrier += IncomingBarrier;
	Event_CardCastOnThis();
}


void ABaseClass_EntityInBattle::Event_StatsChanged()
{
	UpdateCardVariables();
}


// ------------------------- AI
void ABaseClass_EntityInBattle::AI_CastRandomCard()
{
	// Get random card in hand
	int32 RandCardIndex = FMath::RandRange(0, CardsInHand.Num() - 1);
	FCardBase RandCard = CardsInHand[RandCardIndex];
	TArray<ABaseClass_EntityInBattle*> RandTargetsArray;

	if (RandCard.SimpleTargetsOverride == E_Card_SetTargets::E_AnyTarget) {
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
	// If this entity still has mana, cast another spell
	if (EntityBaseData.ManaValues.X_Value >= RandCard.ManaCost) {
		EntityBaseData.ManaValues.X_Value -= RandCard.ManaCost;
	} else {
		GameStateRef->EntityEndOfTurn();
	}

	FStackEntry NewStackEntry;
	NewStackEntry.Card = RandCard;

	GameStateRef->AddCardFunctionsToTheStack(NewStackEntry);
	GetWorldTimerManager().SetTimer(EndTurn_TimerHandle, this, &ABaseClass_EntityInBattle::AI_EndTurnDelay, 1.f, false);
}


void ABaseClass_EntityInBattle::AI_EndTurnDelay()
{
	GameStateRef->EntityEndOfTurn();
}