// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseClass_Widget_ZoneSearch.h"

#include "BaseClass_EntityInBattle.h"


void UBaseClass_Widget_ZoneSearch::PopulateWidget(TArray<FCardBase> Cards, int32 MaxCardSelectCount, E_ZoneSearch_Functions ConfirmButtonFunction, E_Card_Zones SearchZone)
{
	UBaseClass_CardUserWidget* CardWidget_Reference;
	CurrentMaxCardSelectCount = MaxCardSelectCount;

	for (int i = 0; i < Cards.Num(); i++) {
		CardWidget_Reference = CreateWidget<UBaseClass_CardUserWidget>(GetWorld(), CardWidget_Class);
		CardWidget_Reference->CardData = Cards[i];
		CardWidget_Reference->CardData.CurrentSelectMode = E_Card_UserSelectModes::E_Select;
		CardScrollBox->AddChild(CardWidget_Reference);
	}
}


void UBaseClass_Widget_ZoneSearch::ConfirmButton_Function(TArray<FCardBase> &ReturnChosenCards)
{
	if (ChosenCards.Num() > 0) {
		switch (Function) {
		case(E_ZoneSearch_Functions::E_DrawCards):
			for (int i = 0; i < ChosenCards.Num(); i++)
			{
				if (ChosenCards[i].Controller->CardsInDeck.Num() > 0) {
					ChosenCards[i].Controller->CardsInHand.Add(ChosenCards[i].Controller->CardsInDeck[0]);

					// Set ownership
					//ChosenCards[i].Controller->CardsInHand.Last().Owner = ChosenCards[i].Controller;
					//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("Set Card Owner"));

					ChosenCards[i].Controller->CardsInHand.Last().Controller = ChosenCards[i].Controller;
					GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("Set Card Controller"));

					ChosenCards[i].Controller->CardsInDeck.RemoveAt(0);
				}
			}

			// Refresh hand
			ChosenCards[0].Controller->UpdateCardIndicesInAllZones();
			ChosenCards[0].Controller->UpdateCardWidgets();

			// Remove widget
			this->RemoveFromParent();
			break;
		}
	}
	else {
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("No Cards Selected."));
	}
}