#pragma once


#include "CoreMinimal.h"
#include "AiBrainBase.h"
#include "AiBrainRabidRat.generated.h"


UCLASS()
class LOSTWORLD_API UAiBrainRabidRat : public UAiBrainBase
{
	GENERATED_BODY()

public:
	int TurnCount = 0;
	
	virtual void StartTurn() override;
	virtual void SelectCardToCast() override;
	virtual void GetTargetsForCard(int IndexInHand) override;
	virtual void EndTurn() override;
};
