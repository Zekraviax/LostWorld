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
		GetWorld()->GetFirstPlayerController())->BattleHudWidget->CreateCardWidgetInHand(Hand.Last());

	LocalCardReference->CardData = Hand.Last();
	LocalCardReference->IndexInHandArray = Hand.Num() - 1;
	
	return IInterfaceBattle::DrawCard();
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
	
	ALostWorldGameModeBase::DualLog("Player " + EntityData.DisplayName + " is healed for " +
		FString::FromInt(Healing) + " health points.", 2);
	
	// Note: Bear in mind that this actor could use the IInterface's default implementation, but doesn't
	// in order to avoid any unexpected behaviors from calling the same function twice.
	return true;
}

bool AActorEntityPlayer::StartTurn()
{
	Cast<ALostWorldPlayerControllerBattle>(UGameplayStatics::GetPlayerController(GetWorld(), 0))->
		SetControlMode(EPlayerControlModes::Battle);

	ALostWorldGameModeBase::DualLog("Player " + EntityData.DisplayName + "'s turn!", 2);
		
	return Super::StartTurn();
}


bool AActorEntityPlayer::EndTurn()
{
	Cast<ALostWorldPlayerControllerBattle>(UGameplayStatics::GetPlayerController(GetWorld(), 0))->
		SetControlMode(EPlayerControlModes::None);

	ALostWorldGameModeBase::DualLog("Player " + EntityData.DisplayName + " 's turn ends.", 2);

	Cast<ALostWorldGameModeBattle>(GetWorld()->GetAuthGameMode())->EndOfTurn();
	
	return true;
}

