#include "LostWorldPlayerControllerBase.h"

#include "ActorEntityBase.h"
#include "LostWorldGameModeBase.h"
#include "LostWorldGameModeBattle.h"
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


void ALostWorldPlayerControllerBase::AddBattleHudToViewport()
{
	if (LevelHudWidget) {
		if (LevelHudWidget->IsInViewport()) {
			LevelHudWidget->RemoveFromViewport();
		}
	}
	
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
	if (BattleHudWidget) {
		if (BattleHudWidget->IsInViewport()) {
			BattleHudWidget->RemoveFromViewport();
		}
	}
	
	if (LevelHudWidgetBlueprintClass && !LevelHudWidget) {
		LevelHudWidget = CreateWidget<UWidgetHudLevelExploration>(GetWorld(), LevelHudWidgetBlueprintClass);
	}

	if (LevelHudWidget) {
		LevelHudWidget->AddToViewport();
	}
}


void ALostWorldPlayerControllerBase::SetControlMode(EPlayerControlModes InControlMode)
{
	ControlMode = InControlMode;

	ALostWorldGameModeBase::DualLog("InControlMode: " + UEnum::GetValueAsName<EPlayerControlModes>(InControlMode).ToString(), 4);
}