#include "WidgetDevTestMenu.h"


#include "ActorEntityPlayer.h"
#include "JsonObjectConverter.h"
#include "LostWorldGameInstanceBase.h"
#include "LostWorldPlayerControllerBattle.h"
#include "Variables.h"


void UWidgetDevTestMenu::OnDevTestMenuWidgetOpened() const
{
	// This function will provide an easy way to run every function that needs to be run
	// when this widget is opened.
	AddCardNamesToCardDropDown();
}


void UWidgetDevTestMenu::AddCardNamesToCardDropDown() const
{
	// Load card data json
	TArray<FCard> CardsArray;
	FString CardJsonAsString = Cast<ULostWorldGameInstanceBase>(GetWorld()->GetGameInstance())->LoadFileFromJson("CardsData");
	FJsonObjectConverter::JsonArrayStringToUStruct(CardJsonAsString, &CardsArray, 0, 0);

	for (FCard Card : CardsArray) {
		AddCardsToCollectionDropDown->AddOption(Card.DisplayName);
	}

	AddCardsToCollectionDropDown->SetSelectedOption(AddCardsToCollectionDropDown->GetOptionAtIndex(0));
}


void UWidgetDevTestMenu::AddCardToDeck(const FString& CardDisplayName) const
{
	// Should add the card to the players' deck both in the JSON file
	// and in the game.
	// (If they're in the middle of a battle, it should be accessible within battle.)
	TArray<FCard> CardsArray;
	FString CardJsonAsString = Cast<ULostWorldGameInstanceBase>(GetWorld()->GetGameInstance())->LoadFileFromJson("CardsData");
	FJsonObjectConverter::JsonArrayStringToUStruct(CardJsonAsString, &CardsArray, 0, 0);

	for (FCard Card : CardsArray) {
		if (CardDisplayName == Card.DisplayName) {
			Cast<ALostWorldPlayerControllerBattle>(GetWorld()->GetFirstPlayerController())->
				ControlledPlayerEntity->Deck.Add(Card);
			Cast<ALostWorldPlayerControllerBattle>(GetWorld()->GetFirstPlayerController())->
				ControlledPlayerEntity->EntityData.CardsInDeckDisplayNames.Add(FName(CardDisplayName));

			Cast<ULostWorldGameInstanceBase>(GetWorld()->GetGameInstance())->CurrentPlayerSave.EntityData =
				Cast<ALostWorldPlayerControllerBattle>(GetWorld()->GetFirstPlayerController())->ControlledPlayerEntity->EntityData;
			Cast<ULostWorldGameInstanceBase>(GetWorld()->GetGameInstance())->SavePlayerDataJson();
			break;
		}
	}
}
