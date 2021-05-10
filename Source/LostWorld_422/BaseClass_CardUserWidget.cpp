#include "BaseClass_CardUserWidget.h"

#include "BaseClass_PlayerController.h"
#include "BaseClass_CardFunctionsLibrary.h"
#include "BaseClass_Widget_ZoneSearch.h"
#include "LostWorld_422GameStateBase.h"
#include "CardAbilityActor_BaseClass.h"


void UBaseClass_CardUserWidget::NativeTick(const FGeometry& MyGeometry, float DeltaTime)
{
	Super::NativeTick(MyGeometry, DeltaTime);

	float MousePosX;
	float MousePosY;

	if (IsDragging)
	{
		if (!LocalPlayerControllerRef)
			LocalPlayerControllerRef = Cast<ABaseClass_PlayerController>(GetWorld()->GetFirstPlayerController());

		LocalPlayerControllerRef->GetMousePosition(MousePosX, MousePosY);

		// Set position to be equal to MousePos plus (5% of viewport width/height)
		SetPositionInViewport(FVector2D(MousePosX + 10, MousePosY + 10), true);
	}
}


void UBaseClass_CardUserWidget::OnMouseButtonDownEvent(UBaseClass_CardUserWidget* CardDragWidgetInstance)
{
	if (!LocalPlayerControllerRef)
		LocalPlayerControllerRef = Cast<ABaseClass_PlayerController>(GetWorld()->GetFirstPlayerController());

	UBaseClass_CardUserWidget* CardDragWidgetRef;

	CardDragWidgetRef = CreateWidget<UBaseClass_CardUserWidget>(GetWorld(), this->GetClass());
	CardDragWidgetRef->CardData = CardData;
	CardDragWidgetRef->IsDragging = true;

	CardDragWidgetRef->AddToViewport();
	LocalPlayerControllerRef->CurrentDragCardRef = CardDragWidgetRef;
}


void UBaseClass_CardUserWidget::CastCard()
{
	FStackEntry NewStackEntry;

	if (!GameStateRef) {
		GameStateRef = Cast<ALostWorld_422GameStateBase>(GetWorld()->GetGameState());
	}

	NewStackEntry.Card = CardData;

	GameStateRef->AddCardFunctionsToTheStack(NewStackEntry);
}