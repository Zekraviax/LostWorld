#include "BaseClass_PlayerController.h"

#include "EngineUtils.h"
#include "BaseClass_DefaultPawn.h"
#include "BaseClass_GridTile.h"
#include "BaseClass_Widget_Minimap.h"
#include "ItemFunctions_BaseClass.h"
#include "WidgetComponent_MinimapRoom.h"
#include "Widget_CustomConsole_Base.h"
#include "Components/SceneComponent.h"


void ABaseClass_PlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	// Setup proper mouse controls
	SetInputMode(FInputModeGameAndUI());
	bShowMouseCursor = true;
	ClickEventKeys.Add(EKeys::RightMouseButton);

	// Mouse Up event for when players drag, and then let go of cards
	InputComponent->BindAction("MouseLeftClicked", IE_Pressed, this, &ABaseClass_PlayerController::CustomOnLeftMouseButtonUpEvent);

	// Keyboard controls
	InputComponent->BindAction("MoveNorth", IE_Pressed, this, &ABaseClass_PlayerController::PlayerMoveNorth);
	InputComponent->BindAction("MoveEast", IE_Pressed, this, &ABaseClass_PlayerController::PlayerMoveEast);
	InputComponent->BindAction("MoveSouth", IE_Pressed, this, &ABaseClass_PlayerController::PlayerMoveSouth);
	InputComponent->BindAction("MoveWest", IE_Pressed, this, &ABaseClass_PlayerController::PlayerMoveWest);

	ControlMode = E_Player_ControlMode::E_Move;
}


void ABaseClass_PlayerController::BeginPlay()
{
	Super::BeginPlay();

	// Create the Level HUD widget
	if (!Level_HUD_Widget && Level_HUD_Class) {
		Level_HUD_Widget = CreateWidget<UBaseClass_HUD_Level>(GetWorld(), Level_HUD_Class);
		Level_HUD_Widget->AddToViewport();
	}

	// Create the Custom Console widget
	if (!CustomConsole_Reference && CustomConsole_Class) {
		CustomConsole_Reference = CreateWidget<UWidget_CustomConsole_Base>(GetWorld(), CustomConsole_Class);
		CustomConsole_Reference->AddToViewport();
	}

	// Add some cards to the players' collection
	// (Add the same amount of each card because it's easier and more fun this way)
	FString ContextString;
	TArray<FName> Card_ListNames = CardsTable->GetRowNames();
	FCardBase* Card;

	for (int i = 0; i < Card_ListNames.Num(); i++) {
		Card = CardsTable->FindRow<FCardBase>(Card_ListNames[i], ContextString, true);

		// DOn't add any cards that aren't done yet
		if (Card->AbilitiesAndConditions.Num() > 0) {
			for (int x = 0; x < 2; x++) {
				CurrentCollection.Add(*Card);
			}
		}
	}

	// Add one of each item to the player's inventory
	TArray<FName> Item_ListNames = ItemsTable->GetRowNames();
	F_Item_Base* Item;

	for (int i = 0; i < Item_ListNames.Num(); i++) {
		Item = ItemsTable->FindRow<F_Item_Base>(Item_ListNames[i], ContextString, true);

		if (Item->Functions > 0) {
			PlayerInventory.Add(*Item);
		}
	}

	ManualBeginPlay();
}


void ABaseClass_PlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}


void ABaseClass_PlayerController::ManualBeginPlay()
{
	// Create the player EntityInBattle
	if (EntityInBattle_Class) {
		UWorld* const World = GetWorld();
		FActorSpawnParameters SpawnParameters;

		EntityInBattleRef = World->SpawnActor<ABaseClass_EntityInBattle>(EntityInBattle_Class, SpawnParameters);
		EntityInBattleRef->EntityBaseData = CurrentEntityData;
		EntityInBattleRef->PlayerControllerRef = this;

		// Variables
		EntityInBattleRef->EntityBaseData.GameOverOnDeath.GameOverOnDeath = true;
		EntityInBattleRef->EntityBaseData.IsPlayerControllable = true;
		EntityInBattleRef->EntityBaseData.IsPlayer = true;

		EntityInBattleRef->Event_EntitySpawnedInWorld();

		// Set Camera Target
		FViewTargetTransitionParams Params;
		SetViewTarget(EntityInBattleRef, Params);
		EntityInBattleRef->Camera->SetActive(true);

		// Move player to first tile
		for (TObjectIterator<ABaseClass_GridTile> Itr; Itr; ++Itr) {
			ABaseClass_GridTile* FoundTile = *Itr;
			if (FoundTile->PlayerRestPointReference && FoundTile->X_Coordinate == 0 && FoundTile->Y_Coordinate == 0) {
				FoundTile->MinimapRoomReference->SetColour();
				break;
			}
		}
	}

	// Generate Level
	Level_HUD_Widget->Minimap->GenerateLevel();
}


// ------------------------- Controls
void ABaseClass_PlayerController::CustomOnLeftMouseButtonUpEvent()
{
	EntityInBattleRef->UpdateCardVariables();

	// Get any actors under cursor
	FHitResult HitResult(ForceInit);
	GetHitResultUnderCursor(ECollisionChannel::ECC_WorldDynamic, false, HitResult);

	// Delete CardDrag widget
	if (CurrentDragCardRef && Battle_HUD_Widget)
	{
		// Set rudimentary targets based on cast mode
		if (Cast<ABaseClass_EntityInBattle>(HitResult.GetActor()) && CurrentDragCardRef->CardData.SimpleTargetsOverride == E_Card_SetTargets::E_AnyTarget)
		{
			// Any Single (Entity) Target
			CurrentDragCardRef->CardData.CurrentTargets.Add(Cast<ABaseClass_EntityInBattle>(HitResult.GetActor()));
		} else if (CurrentDragCardRef->CardData.SimpleTargetsOverride == E_Card_SetTargets::E_Self) {
			// Self Target
			CurrentDragCardRef->CardData.CurrentTargets.Add(CurrentDragCardRef->CardData.Controller);

		} else if (Cast<ABaseClass_GridTile>(HitResult.GetActor()) && CurrentDragCardRef->CardData.SimpleTargetsOverride == E_Card_SetTargets::E_UnoccupiedGridTile) {
			// Any Unoccupied Tile
			CurrentDragCardRef->CardData.CurrentTargets.Add(HitResult.GetActor());
		} else if (!(Cast<ABaseClass_EntityInBattle>(HitResult.GetActor())) && CurrentDragCardRef->CardData.SimpleTargetsOverride == E_Card_SetTargets::E_AnyTarget) {
			// Stop the spell from being cast if the player hit an invalid target
			CurrentDragCardRef->RemoveFromParent();
			CurrentDragCardRef = NULL;
			return;
		}

		if (!CurrentDragCardRef->CardData.Controller) {
			GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Red, TEXT("Error: No Controller"));
		} else {
			if (EntityInBattleRef->EntityBaseData.ManaValues.X_Value >= CurrentDragCardRef->CardData.ManaCost) {
				if (CurrentDragCardRef->CardData.ManaCost >= 1) {
					EntityInBattleRef->EntityBaseData.ManaValues.X_Value -= CurrentDragCardRef->CardData.ManaCost;
				}
			} else {
				CurrentDragCardRef->RemoveFromParent();
				CurrentDragCardRef = NULL;
				GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Red, TEXT("Error: Failed to cast card"));
				return;
			}
			CurrentDragCardRef->CastCard();
			
			// Remove card from hand and add to graveyard
			for (int i = 0; i < CurrentDragCardRef->CardData.Controller->CardsInHand.Num(); i++)
			{
				if (CurrentDragCardRef->CardData.Controller->CardsInHand.IsValidIndex(i) && CurrentDragCardRef->CardData.Controller->CardsInHand[i].ZoneIndex == CurrentDragCardRef->CardData.ZoneIndex) {
					CurrentDragCardRef->CardData.Controller->CardsInHand.RemoveAt(i);
					CurrentDragCardRef->CardData.Controller->CardsInGraveyard.Add(CurrentDragCardRef->CardData);
				}
			}

			for (int j = 0; j < CurrentDragCardRef->CardData.Controller->CardsInHand.Num() - 1; j++)
			{
				if (j == 0)
					Battle_HUD_Widget->CreatePlayerCardsInHandWidgets(true, CurrentDragCardRef->CardData.Controller->CardsInHand[j]);
				else
					Battle_HUD_Widget->CreatePlayerCardsInHandWidgets(false, CurrentDragCardRef->CardData.Controller->CardsInHand[j]);
			}

			CurrentDragCardRef->CardData.Controller->UpdateCardIndicesInAllZones();
			CurrentDragCardRef->CardData.Controller->UpdateCardWidgets();

			CurrentDragCardRef->RemoveFromParent();
			CurrentDragCardRef = NULL;
		}
	}
}


void ABaseClass_PlayerController::PlayerMoveNorth()
{
	if (ControlMode == E_Player_ControlMode::E_Move) {
		for (TObjectIterator<ABaseClass_GridTile> Itr; Itr; ++Itr) {
			ABaseClass_GridTile* FoundTile = *Itr;

			if (FoundTile) {
				if (FoundTile->X_Coordinate == EntityInBattleRef->X_Coordinate + 1 && FoundTile->Y_Coordinate == EntityInBattleRef->Y_Coordinate) {
					MoveToTile(FoundTile);
					break;
				}
			}
		}
	}
}


void ABaseClass_PlayerController::PlayerMoveEast()
{
	if (ControlMode == E_Player_ControlMode::E_Move) {
		for (TObjectIterator<ABaseClass_GridTile> Itr; Itr; ++Itr) {
			ABaseClass_GridTile* FoundTile = *Itr;

			if (FoundTile) {
				if (FoundTile->X_Coordinate == EntityInBattleRef->X_Coordinate && FoundTile->Y_Coordinate == EntityInBattleRef->Y_Coordinate + 1) {
					MoveToTile(FoundTile);
					break;
				}
			}
		}
	}
}


void ABaseClass_PlayerController::PlayerMoveSouth()
{
	if (ControlMode == E_Player_ControlMode::E_Move) {
		for (TObjectIterator<ABaseClass_GridTile> Itr; Itr; ++Itr) {
			ABaseClass_GridTile* FoundTile = *Itr;

			if (FoundTile) {
				if (FoundTile->X_Coordinate == EntityInBattleRef->X_Coordinate - 1 && FoundTile->Y_Coordinate == EntityInBattleRef->Y_Coordinate) {
					MoveToTile(FoundTile);
					break;
				}
			}
		}
	}
}


void ABaseClass_PlayerController::PlayerMoveWest()
{
	if (ControlMode == E_Player_ControlMode::E_Move) {
		for (TObjectIterator<ABaseClass_GridTile> Itr; Itr; ++Itr) {
			ABaseClass_GridTile* FoundTile = *Itr;

			if (FoundTile) {
				if (FoundTile->X_Coordinate == EntityInBattleRef->X_Coordinate && FoundTile->Y_Coordinate == EntityInBattleRef->Y_Coordinate - 1) {
					MoveToTile(FoundTile);
					break;
				}
			}
		}
	}
}


// ------------------------- Gameplay
void ABaseClass_PlayerController::BeginBattle()
{
	if (Level_HUD_Widget)
		Level_HUD_Widget->SetVisibility(ESlateVisibility::Collapsed);

	// Create the Battle HUD widget
	if (Battle_HUD_Widget) {
		Battle_HUD_Widget->SetVisibility(ESlateVisibility::Visible);
	} else if (Battle_HUD_Class && !Battle_HUD_Widget) {
		Battle_HUD_Widget = CreateWidget<UBaseClass_HUD_Battle>(GetWorld(), Battle_HUD_Class);
		Battle_HUD_Widget->AddToViewport();
	}
}


void ABaseClass_PlayerController::ExitBattle()
{
	if (Battle_HUD_Widget)
		Battle_HUD_Widget->SetVisibility(ESlateVisibility::Collapsed);

	// Create the Level HUD widget
	if (Level_HUD_Widget) {
		Level_HUD_Widget->SetVisibility(ESlateVisibility::Visible);
	} else if (Level_HUD_Class && !Level_HUD_Widget) {
		Level_HUD_Widget = CreateWidget<UBaseClass_HUD_Level>(GetWorld(), Level_HUD_Class);
		Level_HUD_Widget->AddToViewport();
	}

	// Restore the players' MP, but not HP
	EntityInBattleRef->EntityBaseData.ManaValues.X_Value = EntityInBattleRef->EntityBaseData.ManaValues.Y_Value;

	// Remove all cards from the Hand and Deck,
	// and make sure they end up in the Collection
	EntityInBattleRef->CardsInGraveyard.Empty();
	EntityInBattleRef->CardsInHand.Empty();

	ControlMode = E_Player_ControlMode::E_Move;
	Level_HUD_Widget->Minimap->UpdateMinimap(CurrentLocationInLevel);
}


void ABaseClass_PlayerController::MoveToTile(ABaseClass_GridTile* TileReference)
{
	// Clear the previous occupying tile
	if (CurrentLocationInLevel) {
		if (CurrentLocationInLevel->OccupyingEntity == EntityInBattleRef) {
			CurrentLocationInLevel->OccupyingEntity = nullptr;
		}
	}

	// Set new occupying tile
	CurrentLocationInLevel = TileReference;
	CurrentLocationInLevel->OccupyingEntity = EntityInBattleRef;

	// Set Player's Entity location
	EntityInBattleRef->SetActorLocation(TileReference->PlayerRestPointReference->GetComponentLocation());
	EntityInBattleRef->X_Coordinate = TileReference->X_Coordinate;
	EntityInBattleRef->Y_Coordinate = TileReference->Y_Coordinate;

	CurrentRoom = TileReference->RoomReference;
	Level_HUD_Widget->Minimap->UpdateMinimap(TileReference);

	// Run OnTileEnter Functions
	TileReference->OnPlayerEnterTile(this);
}