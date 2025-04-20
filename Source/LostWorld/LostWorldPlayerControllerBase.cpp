#include "LostWorldPlayerControllerBase.h"

#include "ActorEntityBase.h"
#include "ActorEntityPlayer.h"
#include "LostWorldGameModeBase.h"
#include "LostWorldGameModeBattle.h"
#include "LostWorldPlayerControllerBattle.h"
#include "WidgetDeckEditor.h"
#include "WidgetDevTestMenu.h"
#include "WidgetEquipment.h"
#include "WidgetHudBattle.h"
#include "WidgetHudLevelExploration.h"
#include "WidgetPauseMenu.h"
#include "WidgetPlayerPrompt.h"


void ALostWorldPlayerControllerBase::SetupInputComponent()
{
	Super::SetupInputComponent();

	InputComponent->BindAction("LeftMouseButtonClick", IE_Released, this, &ALostWorldPlayerControllerBase::OnLeftMouseButtonClick);
}


void ALostWorldPlayerControllerBase::OnLeftMouseButtonClick()
{
	FHitResult Hit;
	
	switch (ControlMode)
	{
	case (EPlayerControlModes::TargetSelectionSingleEntity):
		GetHitResultUnderCursor(ECC_WorldDynamic, false, Hit);
		ALostWorldGameModeBase::DualLog("Hit: " + Hit.GetActor()->GetName(), 3);

		if (Cast<AActorEntityBase>(Hit.GetActor())) {
			SetControlMode(EPlayerControlModes::Battle);

			// Continue with stack entry execution.
			TArray<AActorEntityBase*> HitTargetsForStackEntry;
			HitTargetsForStackEntry.Add(Cast<AActorEntityBase>(Hit.GetActor()));

			int StackEntryIndex = Cast<ALostWorldPlayerControllerBattle>(this)->StackEntryIndexForManualTargetSelection;
			
			Cast<ALostWorldGameModeBattle>(GetWorld()->GetAuthGameMode())->FinishedGettingTargetsForCard(
				StackEntryIndex, HitTargetsForStackEntry);
		}
		break;
	default:
		break;
	}
}


void ALostWorldPlayerControllerBase::SetControlMode(EPlayerControlModes InControlMode)
{
	ControlMode = InControlMode;

	// Ongoing To-Do: Remember to use UEnum::GetDisplayValueAsText().
	ALostWorldGameModeBase::DualLog("InControlMode: " +
		UEnum::GetDisplayValueAsText(InControlMode).ToString(), 3);

	// Handle each control mode.
	if (InControlMode == EPlayerControlModes::BottomOneCardInHand) {
		// Prompt the player to pick a card.
		BattleHudWidget->CardTargetText->SetVisibility(ESlateVisibility::HitTestInvisible);
		BattleHudWidget->CardTargetText->SetText(
			FText::FromString("Select 1 card to put on the bottom of your Draw Pile"));
	}
}


void ALostWorldPlayerControllerBase::CloseAllWidgets() const
{
	if (LevelHudWidget) {
		if (LevelHudWidget->IsInViewport()) {
			LevelHudWidget->RemoveFromViewport();
		}
	}

	if (BattleHudWidget) {
		if (BattleHudWidget->IsInViewport()) {
			BattleHudWidget->RemoveFromViewport();
		}
	}

	if (DeckEditorWidget) {
		if (DeckEditorWidget->IsInViewport()) {
			DeckEditorWidget->RemoveFromViewport();
		}
	}

	if (EquipmentWidget) {
		if (EquipmentWidget->IsInViewport()) {
			EquipmentWidget->RemoveFromViewport();
		}
	}

	if (PauseMenuWidget) {
		if (PauseMenuWidget->IsInViewport()) {
			PauseMenuWidget->RemoveFromViewport();
		}
	}
}


void ALostWorldPlayerControllerBase::AddBattleHudToViewport()
{
	CloseAllWidgets();
	
	if (BattleHudWidgetBlueprintClass && !BattleHudWidget) {
		BattleHudWidget = CreateWidget<UWidgetHudBattle>(GetWorld(), BattleHudWidgetBlueprintClass);
	}

	if (BattleHudWidget) {
		BattleHudWidget->CardsInHandScrollBox->ClearChildren();
		BattleHudWidget->AddToViewport();
	}
}


void ALostWorldPlayerControllerBase::AddLevelHudToViewport()
{
	CloseAllWidgets();
	
	if (LevelHudWidgetBlueprintClass && !LevelHudWidget) {
		LevelHudWidget = CreateWidget<UWidgetHudLevelExploration>(GetWorld(), LevelHudWidgetBlueprintClass);
	}

	if (LevelHudWidget) {
		LevelHudWidget->AddToViewport();
	}
}


void ALostWorldPlayerControllerBase::AddDeckEditorToViewport()
{
	CloseAllWidgets();
	
	if (DeckEditorWidgetBlueprintClass && !DeckEditorWidget) {
		DeckEditorWidget = CreateWidget<UWidgetDeckEditor>(GetWorld(), DeckEditorWidgetBlueprintClass);
	}

	if (DeckEditorWidget) {
		DeckEditorWidget->AddToViewport();
		DeckEditorWidget->PopulateCardsInDeckUniformGridPanel(ControlledPlayerEntity->EntityData.Deck);
		DeckEditorWidget->PopulateCardsInCollectionUniformGridPanel(ControlledPlayerEntity->EntityData.Collection);
	}
}


void ALostWorldPlayerControllerBase::AddDevTestMenuToViewport()
{
	// Don't close anything when opening this menu.
	// Just overlay this menu on top of everything else.
	if (DevTestWidgetBlueprintClass && !DevTestWidget) {
		DevTestWidget = CreateWidget<UWidgetDevTestMenu>(GetWorld(), DevTestWidgetBlueprintClass);
	}

	if (DevTestWidget) {
		DevTestWidget->AddToViewport();
		DevTestWidget->OnDevTestMenuWidgetOpened();
	}
}


void ALostWorldPlayerControllerBase::AddEquipmentToViewport()
{
	CloseAllWidgets();
	
	if (EquipmentWidgetBlueprintClass && !EquipmentWidget) {
		EquipmentWidget = CreateWidget<UWidgetEquipment>(GetWorld(), EquipmentWidgetBlueprintClass);
	}

	if (EquipmentWidget) {
		EquipmentWidget->AddToViewport();
		EquipmentWidget->PopulateEquippedItemsScrollBox(ControlledPlayerEntity->EntityData.EquippedItems);
		EquipmentWidget->PopulateUnequippedItemsScrollBox(ControlledPlayerEntity->EntityData.EquipmentInventory);
	}
}


void ALostWorldPlayerControllerBase::AddPauseMenuToViewport()
{
	// We won't close all widgets first. Instead we will just overlay this one on top.
	if (PauseMenuWidgetBlueprintClass && !PauseMenuWidget) {
		PauseMenuWidget = CreateWidget<UWidgetPauseMenu>(GetWorld(), PauseMenuWidgetBlueprintClass);
	}

	if (PauseMenuWidget) {
		// To-Do: Pause execution of the game.
		PauseMenuWidget->AddToViewport();
	}
}


void ALostWorldPlayerControllerBase::AddPlayerPromptToViewport(const EPromptType InPromptType, const FCard& InCard, const int IndexInHand)
{
	// We won't close all widgets first. Instead we will just overlay this one on top.
	if (PlayerPromptWidgetBlueprintClass && !PlayerPromptWidget) {
		PlayerPromptWidget = CreateWidget<UWidgetPlayerPrompt>(GetWorld(), PlayerPromptWidgetBlueprintClass);
	}

	if (PlayerPromptWidget) {
		PlayerPromptWidget->SetUpPrompt(InPromptType, InCard, IndexInHand);
		PlayerPromptWidget->AddToViewport();
	}
}
