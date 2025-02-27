#include "LostWorldPlayerControllerBase.h"

#include "ActorEntityBase.h"
#include "ActorEntityPlayer.h"
#include "LostWorldGameModeBase.h"
#include "LostWorldGameModeBattle.h"
#include "WidgetDeckEditor.h"
#include "WidgetDevTestMenu.h"
#include "WidgetEquipment.h"
#include "WidgetHudBattle.h"
#include "WidgetHudLevelExploration.h"


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
				Cast<ALostWorldGameModeBattle>(GetWorld()->GetAuthGameMode())->TempStackEntry.SelectedTargets.Add(Cast<AActorEntityBase>(Hit.GetActor()));

				SetControlMode(EPlayerControlModes::Battle);
				
				// Execute the first stack entry
				Cast<ALostWorldGameModeBattle>(GetWorld()->GetAuthGameMode())->FinishedGettingTargetsForCard();
			}
			break;
		default:
			break;
	}
}


void ALostWorldPlayerControllerBase::SetControlMode(EPlayerControlModes InControlMode)
{
	ControlMode = InControlMode;

	ALostWorldGameModeBase::DualLog("InControlMode: " + UEnum::GetValueAsName<EPlayerControlModes>(InControlMode).ToString(), 4);
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
