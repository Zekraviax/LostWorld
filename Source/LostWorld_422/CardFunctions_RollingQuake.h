#pragma once

#include "CoreMinimal.h"
#include "CardAbilityActor_BaseClass.h"
#include "CardFunctions_RollingQuake.generated.h"

// Forward Declarations
class UBaseClass_Widget_SpentMana;


UCLASS()
class LOSTWORLD_422_API ACardFunctions_RollingQuake : public ACardAbilityActor_BaseClass
{
	GENERATED_BODY()

	ACardFunctions_RollingQuake();
	
public:
// Variables
// --------------------------------------------------

// ------------------------- Constructors
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<UBaseClass_Widget_SpentMana> SpentManaWidget_Class;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UBaseClass_Widget_SpentMana* SpentManaWidget_Reference;

// Functions
// --------------------------------------------------

// ------------------------- Base Class Functions
	virtual void RunCardAbilityFunction(FCardBase CardAbility);

// ------------------------- Widget Functions
	//virtual void WidgetFunction_SpendMana();

};