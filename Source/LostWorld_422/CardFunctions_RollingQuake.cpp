#include "CardFunctions_RollingQuake.h"

#include "BaseClass_EntityInBattle.h"
#include "BaseClass_Widget_SpentMana.h"
#include "Blueprint/WidgetBlueprintLibrary.h"


ACardFunctions_RollingQuake::ACardFunctions_RollingQuake()
{
	// SpentMana Widget
	static ConstructorHelpers::FClassFinder<UUserWidget> SpentManaWidget_ClassFinder(TEXT("WidgetBlueprint'/Game/Widget_SpentMana_Blueprint.Widget_SpentMana_Blueprint_C'"));
	if (SpentManaWidget_ClassFinder.Class) {
		SpentManaWidget_Class = SpentManaWidget_ClassFinder.Class;
	}

	// Cards DataTable
	static ConstructorHelpers::FObjectFinder<UDataTable> CardsDataTable_Object(TEXT("DataTable'/Game/DataTables/Cards_List.Cards_List'"));
	if (CardsDataTable_Object.Succeeded()) {
		CardsTable = CardsDataTable_Object.Object;
	}
}


// ------------------------- Base Class Functions
void ACardFunctions_RollingQuake::RunCardAbilityFunction(FStackEntry StackEntry)
{
	int DamageValue = StackEntry.Card.AbilitiesAndConditions[0].BaseDamage;

	//SpentMana_Widget Check
	if (StackEntry.RunWidgetFunction) {
		if (SpentManaWidget_Class) {
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, TEXT("Execute Card Function: Rolling Quake (Spend Mana)"));

			SpentManaWidget_Reference = CreateWidget<UBaseClass_Widget_SpentMana>(GetWorld(), SpentManaWidget_Class);
			SpentManaWidget_Reference->CardsTableRowName = "RollingQuake";
			SpentManaWidget_Reference->StackEntry = StackEntry;
			SpentManaWidget_Reference->AddToViewport();
		}
	} else {
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, TEXT("Execute Card Function: Rolling Quake (Deal Damage)"));

		// Get random targets here so that we avoid hitting an entity that's already dead
		StackEntry.Card.CurrentTargets.Empty();
		for (TActorIterator<ABaseClass_EntityInBattle> ActorItr(GetWorld()); ActorItr; ++ActorItr)
		{
			ABaseClass_EntityInBattle* FoundEntity = *ActorItr;

			if (FoundEntity->IsValidLowLevel())
				if (!FoundEntity->EntityBaseData.IsPlayerControllable && FoundEntity->EntityBaseData.HealthValues.X_Value > 0)
					StackEntry.Card.CurrentTargets.Add(FoundEntity);
		}

		if (StackEntry.Card.CurrentTargets.Num() > 0) {
			for (int i = StackEntry.Card.CurrentTargets.Num() - 1; i >= 0; i--) {
				if (Cast<ABaseClass_EntityInBattle>(StackEntry.Card.CurrentTargets[i])->EntityBaseData.HealthValues.X_Value <= 0)
					StackEntry.Card.CurrentTargets.RemoveAt(i);
			}

			ABaseClass_EntityInBattle* RandEnemy = Cast<ABaseClass_EntityInBattle>(StackEntry.Card.CurrentTargets[FMath::RandRange(0, StackEntry.Card.CurrentTargets.Num() - 1)]);

			RandEnemy->Event_DamageIncoming(DamageValue, StackEntry.Card.Elements[0], E_Card_DamageTypes::E_Magical);
		}
	}
}


// ------------------------- Widget Functions
void ACardFunctions_RollingQuake::WidgetFunction_SpendMana(int ManaSpent, FStackEntry StackEntry)
{
	FString ContextString;
	FStackEntry DuplicateCardStackEntry = StackEntry;

	for (int r = 0; r < ManaSpent; r++) {
		DuplicateCardStackEntry.Card = *CardsTable->FindRow<FCardBase>("RollingQuake", ContextString, true);
		DuplicateCardStackEntry.RunWidgetFunction = false;

		Cast<ALostWorld_422GameStateBase>(GetWorld()->GetGameState())->AddCardFunctionsToTheStack(DuplicateCardStackEntry);
	}

	// Subtract mana
	StackEntry.Card.Controller->EntityBaseData.ManaValues.X_Value -= ManaSpent;

	ConditionalBeginDestroy();
}