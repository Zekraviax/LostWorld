#pragma once


#include "CoreMinimal.h"
#include "AiBrainBase.h"
#include "AiBrainTestEnemyOne.generated.h"


UCLASS()
class LOSTWORLD_API UAiBrainTestEnemyOne : public UAiBrainBase
{
	GENERATED_BODY()

public:
	virtual void BeginTurn() override;
	virtual void SelectCardToCast() override;
};
