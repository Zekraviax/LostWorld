#pragma once

#include "CoreMinimal.h"
#include "CardAbilityActor_BaseClass.h"
#include "CardFunctions_LayOnHands.generated.h"

// Forward Declarations
class UBaseClass_Widget_SpentMana;


UCLASS()
class LOSTWORLD_422_API ACardFunctions_LayOnHands : public ACardAbilityActor_BaseClass
{
	GENERATED_BODY()

	ACardFunctions_LayOnHands();

public:

// Variables
// --------------------------------------------------

// ------------------------- Constructors
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<UBaseClass_Widget_SpentMana> SpentManaWidget_Class;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UBaseClass_Widget_SpentMana* SpentManaWidget_Reference;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UDataTable* CardsTable;

// Functions
// --------------------------------------------------

// ------------------------- Base Class Functions
	virtual void RunCardAbilityFunction(FStackEntry StackEntry) override;

// ------------------------- Widget Functions
	virtual void WidgetFunction_SpendMana(int ManaSpent, FStackEntry StackEntry);
};
