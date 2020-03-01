#include "BaseClass_Widget_DeckBuilder.h"

#include "Runtime/UMG/Public/Blueprint/WidgetTree.h"
#include "Components/CanvasPanel.h"
#include "BaseClass_PlayerController.h"


void UBaseClass_Widget_DeckBuilder::NativeConstruct()
{
	Super::NativeConstruct();
}

void UBaseClass_Widget_DeckBuilder::PopulateScrollBoxes()
{
	if (!PlayerControllerRef)
		PlayerControllerRef = Cast<ABaseClass_PlayerController>(GetWorld()->GetFirstPlayerController());

	bool FoundCardWidget;
	UBaseClass_Widget_DeckBuilderCard* LocalCardWidgetRef;


	// Collection
	if (CurrentCollection_ScrollBox)
	{
		CurrentCollection_ScrollBox->ClearChildren();

		if (TestUnlimitedCardsMode)
			Test_Activate_UnlimitedCards();

		else
		{
			for (int i = 0; i < PlayerControllerRef->CurrentCollection.Num(); i++)
			{
				FoundCardWidget = false;
				DeckBuilderCard_Widget = nullptr;

				for (int j = 0; j < CurrentCollection_ScrollBox->GetChildrenCount(); j++)
				{
					LocalCardWidgetRef = Cast<UBaseClass_Widget_DeckBuilderCard>(CurrentCollection_ScrollBox->GetChildAt(j));

					if (LocalCardWidgetRef->CardDataRef.DisplayName == PlayerControllerRef->CurrentCollection[i].DisplayName)
					{
						FoundCardWidget = true;
						DeckBuilderCard_Widget = LocalCardWidgetRef;
						break;
					}
				}

				if (DeckBuilderCard_Widget)
				{
					DeckBuilderCard_Widget->QuantityBind++;

					if(DeckBuilderCard_Widget->DeckBuilderZone != E_DeckBuilder_Zone::E_Collection)
						DeckBuilderCard_Widget->DeckBuilderZone = E_DeckBuilder_Zone::E_Collection;
				}
				else
				{
					DeckBuilderCard_Widget = CreateWidget<UBaseClass_Widget_DeckBuilderCard>(GetWorld(), DeckBuilderCard_Class);

					DeckBuilderCard_Widget->CardDataRef = PlayerControllerRef->CurrentCollection[i];
					DeckBuilderCard_Widget->DeckBuilderZone = E_DeckBuilder_Zone::E_Collection;
					DeckBuilderCard_Widget->PlayerControllerRef = PlayerControllerRef;
					DeckBuilderCard_Widget->DeckBuilderWidgetRef = this;
					DeckBuilderCard_Widget->QuantityBind = 1;
					CurrentCollection_ScrollBox->AddChild(DeckBuilderCard_Widget);
				}
			}
		}
	}

	// Deck
	if (CurrentDeck_ScrollBox)
	{
		CurrentDeck_ScrollBox->ClearChildren();

		for (int i = 0; i < PlayerControllerRef->CurrentEntityData.CurrentDeck.Num(); i++)
		{
			FoundCardWidget = false;
			DeckBuilderCard_Widget = nullptr;

			for (int j = 0; j < CurrentDeck_ScrollBox->GetChildrenCount(); j++)
			{
				LocalCardWidgetRef = Cast<UBaseClass_Widget_DeckBuilderCard>(CurrentDeck_ScrollBox->GetChildAt(j));

				if (LocalCardWidgetRef->CardDataRef.DisplayName == PlayerControllerRef->CurrentEntityData.CurrentDeck[i].DisplayName && !FoundCardWidget)
				{
					FoundCardWidget = true;
					DeckBuilderCard_Widget = LocalCardWidgetRef;
				}
			}

			if (DeckBuilderCard_Widget)
			{
				DeckBuilderCard_Widget->QuantityBind++;
				DeckBuilderCard_Widget->BindInfo();
			}
			else
			{
				DeckBuilderCard_Widget = CreateWidget<UBaseClass_Widget_DeckBuilderCard>(GetWorld(), DeckBuilderCard_Class);
				DeckBuilderCard_Widget->CardDataRef = PlayerControllerRef->CurrentEntityData.CurrentDeck[i];
				DeckBuilderCard_Widget->DeckBuilderZone = E_DeckBuilder_Zone::E_Deck;
				DeckBuilderCard_Widget->PlayerControllerRef = PlayerControllerRef;
				DeckBuilderCard_Widget->DeckBuilderWidgetRef = this;
				DeckBuilderCard_Widget->QuantityBind = 1;
				CurrentDeck_ScrollBox->AddChild(DeckBuilderCard_Widget);
			}
		}
	}
}

void UBaseClass_Widget_DeckBuilder::AddSingleCardToZone(FCardBase ChosenCard, E_DeckBuilder_Zone ChosenZone)
{
	if (!PlayerControllerRef)
		PlayerControllerRef = Cast<ABaseClass_PlayerController>(GetWorld()->GetFirstPlayerController());

	FString ContextString;

	DeckBuilderCard_Widget = CreateWidget<UBaseClass_Widget_DeckBuilderCard>(GetWorld(), DeckBuilderCard_Class);
	DeckBuilderCard_Widget->CardDataRef = *GameModeRef->CardDataTableRef->FindRow<FCardBase>(FName(*ChosenCard.DisplayName), ContextString);
	DeckBuilderCard_Widget->PlayerControllerRef = PlayerControllerRef;
	DeckBuilderCard_Widget->DeckBuilderWidgetRef = this;
	DeckBuilderCard_Widget->QuantityBind = 1;
	DeckBuilderCard_Widget->BindInfo();

	switch (ChosenZone)
	{

	case(E_DeckBuilder_Zone::E_Collection):
		DeckBuilderCard_Widget->DeckBuilderZone = E_DeckBuilder_Zone::E_Collection;
		CurrentCollection_ScrollBox->AddChild(DeckBuilderCard_Widget);
		break;

	case(E_DeckBuilder_Zone::E_Deck):
		DeckBuilderCard_Widget->DeckBuilderZone = E_DeckBuilder_Zone::E_Deck;
		CurrentDeck_ScrollBox->AddChild(DeckBuilderCard_Widget);
		break;

	default:
		break;
	}
}

void UBaseClass_Widget_DeckBuilder::Test_Activate_UnlimitedCards()
{
	ALostWorld_422GameModeBase* LocalGameModeRef = (ALostWorld_422GameModeBase*)GetWorld()->GetAuthGameMode();
	TArray<FName> CardRowNames;
	FString ContextString;

	if (!PlayerControllerRef)
		PlayerControllerRef = Cast<ABaseClass_PlayerController>(GetWorld()->GetFirstPlayerController());

	if (CurrentCollection_ScrollBox)
	{
		if (CurrentCollection_ScrollBox->GetChildrenCount() > 0)
		{
			CurrentCollection_ScrollBox->ClearChildren();
		}

		if (LocalGameModeRef)
		{
			CardRowNames = LocalGameModeRef->CardDataTableRef->GetRowNames();


			for (int i = 0; i < CardRowNames.Num(); i++)
			{
				DeckBuilderCard_Widget = CreateWidget<UBaseClass_Widget_DeckBuilderCard>(GetWorld(), DeckBuilderCard_Class);
				DeckBuilderCard_Widget->CardDataRef = *LocalGameModeRef->CardDataTableRef->FindRow<FCardBase>(CardRowNames[i], ContextString);
				DeckBuilderCard_Widget->DeckBuilderZone = E_DeckBuilder_Zone::E_Collection;
				DeckBuilderCard_Widget->PlayerControllerRef = PlayerControllerRef;
				DeckBuilderCard_Widget->DeckBuilderWidgetRef = this;
				DeckBuilderCard_Widget->QuantityBind = 255;
				CurrentCollection_ScrollBox->AddChild(DeckBuilderCard_Widget);
				TestUnlimitedCardsMode = true;
			}
		}
	}
}

void UBaseClass_Widget_DeckBuilder::Test_Dectivate_UnlimitedCards()
{
	PopulateScrollBoxes();
	TestUnlimitedCardsMode = false;
}

void UBaseClass_Widget_DeckBuilder::ExitDeckBuilder()
{
	HUDRef->DeckBuilderRef = nullptr;

	// Update player's deck everywhere
	PlayerControllerRef->EntityInBattleRef->CardsInDeck = PlayerControllerRef->CurrentEntityData.CurrentDeck;

	RemoveFromParent();
}