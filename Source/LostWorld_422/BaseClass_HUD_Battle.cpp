#include "BaseClass_HUD_Battle.h"


#include "LostWorld_422GameStateBase.h"
#include "BaseClass_EntityInBattle.h"


void UBaseClass_HUD_Battle::NativeConstruct() {

	Super::NativeConstruct();

	GameStateRef = GetWorld()->GetGameState<ALostWorld_422GameStateBase>();
}


void UBaseClass_HUD_Battle::CreatePlayerCardsInHandWidgets(bool ClearHand, FCardBase CardInHand)
{
	if (ClearHand && CardsInHand_ScrollBox)
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