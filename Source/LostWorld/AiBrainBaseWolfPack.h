#pragma once


#include "CoreMinimal.h"
#include "AiBrainBase.h"
#include "AiBrainBaseWolfPack.generated.h"


UCLASS()
class LOSTWORLD_API UAiBrainBaseWolfPack : public UAiBrainBase
{
	GENERATED_BODY()

public:
	virtual void StartTurn() override;
	virtual void SelectCardToCast() override;
	virtual void GetTargetsForCard(int IndexInHand) override;
	virtual void EndTurn() override;
};
