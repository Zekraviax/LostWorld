#include "BaseClass_HUD_Battle.h"


#include "BaseClass_EntityInBattle.h"
#include "BaseClass_PlayerController.h"
#include "Kismet/GameplayStatics.h"
#include "LostWorld_422GameStateBase.h"
#include "Widget_Inventory_Base.h"


void UBaseClass_HUD_Battle::NativeConstruct() 
{
	Super::NativeConstruct();

	GameStateRef = GetWorld()->GetGameState<ALostWorld_422GameStateBase>();
}


// ------------------------- Widgets
void UBaseClass_HUD_Battle::CreatePlayerCardsInHandWidgets(bool ClearHand, FCard CardInHand)
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
	Inventory_Reference = Cast<ULostWorld_422GameInstanceBase>(UGameplayStatics::GetGameInstance(GetWorld()))->GetInventory();

	Inventory_Reference->OnInventoryOpened(Cast<ABaseClass_PlayerController>(GetWorld()->GetFirstPlayerController()), true);
	Inventory_Reference->AddToViewport();
}


// ------------------------- Battle
void UBaseClass_HUD_Battle::EndTurn_Function()
{
	if (GameStateRef) {
		GameStateRef->EntityEndOfTurn();
	}
}


void UBaseClass_HUD_Battle::ViewCardsInZone(E_Card_Zones Zone)
{
	//switch (Zone)
	//{
	//	case(E_Card_Zones::E_Deck):
	//		break;
	//	default:
	//		break;
	//}
}