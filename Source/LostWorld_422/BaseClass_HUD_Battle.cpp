// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseClass_HUD_Battle.h"

#include "LostWorld_422GameStateBase.h"


void UBaseClass_HUD_Battle::NativeConstruct() {

	Super::NativeConstruct();

	GameStateRef = GetWorld()->GetGameState<ALostWorld_422GameStateBase>();
}

void UBaseClass_HUD_Battle::DebugBeginBattle()
{
	GameStateRef->DebugBattleStart();
}

void UBaseClass_HUD_Battle::Test_SetPlayerData()
{
	if(GameStateRef->PlayerControllerRef)
		GameStateRef->PlayerControllerRef->CurrentEntityData.DisplayName = "Player";

	if(GameStateRef->PlayerControllerRef->EntityInBattleRef)
		GameStateRef->PlayerControllerRef->EntityInBattleRef->EntityBaseData = GameStateRef->PlayerControllerRef->CurrentEntityData;
}

void UBaseClass_HUD_Battle::OpenDeckBuilder()
{
	//if (DeckBuilder_Class && !DeckBuilderRef)
	//{
	//	DeckBuilderRef = CreateWidget<UBaseClass_Widget_DeckBuilder>(GetWorld(), DeckBuilder_Class);
	//	DeckBuilderRef->HUDRef = this;
	//	DeckBuilderRef->PopulateScrollBoxes();
	//	DeckBuilderRef->AddToViewport();
	//}
}

void UBaseClass_HUD_Battle::CreatePlayerCardsInHandWidgets(bool ClearHand, FCardBase CardInHand)
{
	if (ClearHand)
		CardsInHand_ScrollBox->ClearChildren();

	CardWidgetRef = CreateWidget<UBaseClass_CardUserWidget>(GetWorld(), Card_Class);
	CardWidgetRef->CardData = CardInHand;
	CardWidgetRef->IndexInZone = CardsInHand_ScrollBox->GetChildrenCount();
	CardWidgetRef->CardData.ZoneIndex = CardWidgetRef->IndexInZone;
	CardsInHand_ScrollBox->AddChild(CardWidgetRef);
}

void UBaseClass_HUD_Battle::EndTurn_Function()
{
	if (GameStateRef) {
		GameStateRef->EntityEndOfTurn();
	}
}