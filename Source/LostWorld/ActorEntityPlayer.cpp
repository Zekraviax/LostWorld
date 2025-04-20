#include "ActorEntityPlayer.h"


#include "Kismet/GameplayStatics.h"
#include "LostWorldGameModeBase.h"
#include "LostWorldGameModeBattle.h"
#include "LostWorldPlayerControllerBattle.h"
#include "WidgetCard.h"
#include "WidgetHudBattle.h"


// Sets default values
AActorEntityPlayer::AActorEntityPlayer()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Initialize actors components
	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>("StaticMesh");
	SpringArm = CreateDefaultSubobject<USpringArmComponent>("SpringArm");
	Camera = CreateDefaultSubobject<UCameraComponent>("Camera");
	EntityBillboard = CreateDefaultSubobject<UWidgetComponent>("EntityBillboard");

	SetRootComponent(StaticMesh);
	SpringArm->SetupAttachment(RootComponent);
	Camera->SetupAttachment(SpringArm);
	EntityBillboard->SetupAttachment(StaticMesh);
	EntityBillboard->SetPivot(FVector2D(0.1f, 0.f));
}


// -------------------------------- Battle Interface functions
bool AActorEntityPlayer::DrawCard()
{
	Super::DrawCard();

	// To-Do: Only create the widget if it's the entity's turn.
	// Create a widget for the card and add it to the players' HUD.
	UWidgetCard* LocalCardReference = Cast<ALostWorldPlayerControllerBattle>(
		GetWorld()->GetFirstPlayerController())->BattleHudWidget->CreateCardWidgetInHand(EntityData.Hand.Last());

	LocalCardReference->CardData = EntityData.Hand.Last();
	LocalCardReference->IndexInHandArray = EntityData.Hand.Num() - 1;
	
	return true;
}


bool AActorEntityPlayer::DiscardCard(int IndexInHand)
{
	Super::DiscardCard(IndexInHand);

	Cast<ALostWorldPlayerControllerBattle>(UGameplayStatics::GetPlayerController(GetWorld(), 0))->
		BattleHudWidget->PlayerFinishCastingCard(IndexInHand);

	Cast<ALostWorldPlayerControllerBattle>(
		GetWorld()->GetFirstPlayerController())->BattleHudWidget->ResetAllCardWidgetIndices();

	// Note: Bear in mind that this actor could use the IInterface's default implementation, but doesn't
	// in order to avoid any unexpected behaviors from calling the same function twice.
	return true;
}


bool AActorEntityPlayer::BottomCard(FCard InCard)
{
	Super::BottomCard(InCard);

	// Refresh all card-in-hand widgets.
	Cast<ALostWorldPlayerControllerBattle>(ReturnThisPlayersController())->RefreshAllCardInHandWidgets();

	// Clear 'Bottom Card' prompt.
	Cast<ALostWorldPlayerControllerBattle>(ReturnThisPlayersController())->BattleHudWidget->CardTargetText->
		SetVisibility(ESlateVisibility::Collapsed);
	Cast<ALostWorldPlayerControllerBattle>(ReturnThisPlayersController())->BattleHudWidget->CardTargetText->SetText(
		FText::FromString(""));

	Cast<ALostWorldPlayerControllerBattle>(ReturnThisPlayersController())->SetControlMode(EPlayerControlModes::Battle);
	
	return true;
}


bool AActorEntityPlayer::ExileCardFromZone(FString InZoneName, FCard InCard)
{
	Super::ExileCardFromZone(InZoneName, InCard);

	// Refresh all card-in-hand widgets.
	Cast<ALostWorldPlayerControllerBattle>(ReturnThisPlayersController())->RefreshAllCardInHandWidgets();

	ALostWorldGameModeBase::DualLog("Your ephemeral " + InCard.DisplayName + " disappeared.", 2);

	return true;
}


bool AActorEntityPlayer::TakeDamage(float Damage)
{
	Super::TakeDamage(Damage);

	ALostWorldGameModeBase::DualLog("Player " + EntityData.DisplayName + " takes " +
		FString::FromInt(Damage) + " damage.", 2);

	// Note: Bear in mind that this actor could use the IInterface's default implementation, but doesn't
	// in order to avoid any unexpected behaviors from calling the same function twice.
	return true;
}


bool AActorEntityPlayer::EntityDefeated()
{
	ALostWorldGameModeBase::DualLog("Game Over", 0);

	// To-Do: Implement game overs.
	return true;
}


bool AActorEntityPlayer::ReceiveHealing(float Healing)
{
	Super::ReceiveHealing(Healing);
	
	// Note: Bear in mind that this actor could use the IInterface's default implementation, but doesn't
	// in order to avoid any unexpected behaviors from calling the same function twice.
	return true;
}

bool AActorEntityPlayer::StartTurn()
{
	Super::StartTurn();
	
	if (HasStatusEffect(EStatusEffectFunctions::Stun)) {
		EndTurnTimerDelegate.BindUFunction(this, FName("EndTurn"));
		
		GetWorld()->GetTimerManager().SetTimer(EndTurnTimerHandle, EndTurnTimerDelegate, 1.5f, false);
	} else {
		ALostWorldGameModeBase::DualLog("Player " + EntityData.DisplayName + "'s turn!", 2);
		
		Cast<ALostWorldPlayerControllerBattle>(UGameplayStatics::GetPlayerController(GetWorld(), 0))->
			SetControlMode(EPlayerControlModes::Battle);
	}
	
	return true;
}


bool AActorEntityPlayer::EndTurn()
{
	Cast<ALostWorldPlayerControllerBattle>(UGameplayStatics::GetPlayerController(GetWorld(), 0))->
		SetControlMode(EPlayerControlModes::None);

	ALostWorldGameModeBase::DualLog("Player " + EntityData.DisplayName + " 's turn ends.", 2);

	Cast<ALostWorldGameModeBattle>(GetWorld()->GetAuthGameMode())->EndOfTurn();
	
	return Super::EndTurn();
}


ALostWorldPlayerControllerBase* AActorEntityPlayer::ReturnThisPlayersController()
{
	TArray<AActor*> FoundControllers;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ALostWorldPlayerControllerBase::StaticClass(), FoundControllers);

	for (AActor* Actor : FoundControllers) {
		if (Cast<ALostWorldPlayerControllerBase>(Actor)) {
			if (Cast<ALostWorldPlayerControllerBase>(Actor)->ControlledPlayerEntity == this) {
				return Cast<ALostWorldPlayerControllerBase>(Actor);
			}
		}
	}

	return nullptr;
}

