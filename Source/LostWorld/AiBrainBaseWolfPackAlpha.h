#pragma once


#include "CoreMinimal.h"
#include "AiBrainBase.h"
#include "AiBrainBaseWolfPackAlpha.generated.h"


UCLASS()
class LOSTWORLD_API UAiBrainBaseWolfPackAlpha : public UAiBrainBase
{
	GENERATED_BODY()
	
	virtual void StartTurn() override;
	virtual void SelectCardToCast() override;
	virtual void GetTargetsForCard(int IndexInHand) override;
	virtual void EndTurn() override;
};
