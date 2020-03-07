#include "BaseClass_CardUserWidget.h"

#include "BaseClass_PlayerController.h"
#include "BaseClass_CardFunctionsLibrary.h"
#include "BaseClass_Widget_ZoneSearch.h"
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

	//if (CardData.CurrentSelectMode == E_Card_UserSelectModes::E_Cast) {
	CardDragWidgetRef = CreateWidget<UBaseClass_CardUserWidget>(GetWorld(), this->GetClass());
	CardDragWidgetRef->CardData = CardData;
	CardDragWidgetRef->IsDragging = true;

	CardDragWidgetRef->AddToViewport();
	LocalPlayerControllerRef->CurrentDragCardRef = CardDragWidgetRef;
	//}
	//else if (CardData.CurrentSelectMode == E_Card_UserSelectModes::E_Select) {
	//	UBaseClass_Widget_ZoneSearch* FoundWidget = NULL;
	//	for (TObjectIterator<UBaseClass_Widget_ZoneSearch> Itr; Itr; ++Itr) {
	//		FoundWidget = *Itr;
	//	}
	//	if (FoundWidget->ChosenCards.Contains(CardData)) {
	//		FoundWidget->ChosenCards.Remove(CardData);
	//	}
	//	else if (!FoundWidget->ChosenCards.Contains(CardData) && FoundWidget->ChosenCards.Num() < FoundWidget->CurrentMaxCardSelectCount) {
	//		FoundWidget->ChosenCards.Add(CardData);
	//	}
	//	else if (FoundWidget->ChosenCards.Num() >= FoundWidget->CurrentMaxCardSelectCount) {
	//		//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Max number of choosable cards reached."));
	//	}
	//}
}


void UBaseClass_CardUserWidget::CastCard()
{
	if (!GameModeRef)
		GameModeRef = Cast<ALostWorld_422GameModeBase>(GetWorld()->GetAuthGameMode());

	//GameModeRef->CardFunctionLibraryReference->AddCardFunctionsToTheStack(CardData);
	UE_LOG(LogTemp, Warning, TEXT("Cast Card"));
}