#pragma once


#include "CoreMinimal.h"
#include "LostWorld_422GameModeBase.h"


// ------------------------- The Stack
USTRUCT(BlueprintType)
struct LOSTWORLD_422_API FCardOnStack
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FCardBase Card;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int CardFunctionIndex;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Delay;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool RunWidgetFunction;

	FCardOnStack(FCardBase InCard, int InCardFunctionIndex, float InDelay, bool InRunWidgetFunction)
	{
		Card = InCard;
		CardFunctionIndex = InCardFunctionIndex;
		Delay = InDelay;
		RunWidgetFunction = InRunWidgetFunction;
	}

	FCardOnStack()
	{
		Delay = 1.5f;
		RunWidgetFunction = true;
	}
};


class LOSTWORLD_422_API LostWorld_Variables
{
public:
	LostWorld_Variables();
	~LostWorld_Variables();
};
