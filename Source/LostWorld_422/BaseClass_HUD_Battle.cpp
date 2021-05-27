#include "BaseClass_HUD_Battle.h"


#include "LostWorld_422GameStateBase.h"
#include "BaseClass_EntityInBattle.h"
#include "Widget_Inventory_Base.h"


void UBaseClass_HUD_Battle::NativeConstruct() 
{
	Super::NativeConstruct();

	GameStateRef = GetWorld()->GetGameState<ALostWorld_422GameStateBase>();
}


// ------------------------- Widgets
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


void UBaseClass_HUD_Battle::OpenInventoryWidget()
{
	if (Inventory_Class) {
		Inventory_Reference = CreateWidget<UWidget_Inventory_Base>(GetWorld(), Inventory_Class);
		Inventory_Reference->AddToViewport();
	}
}


// ------------------------- Battle
void UBaseClass_HUD_Battle::EndTurn_Function()
{
	if (GameStateRef) {
		GameStateRef->EntityEndOfTurn();
	}
}