#pragma once


#include "CoreMinimal.h"
#include "AiBrainBase.h"
#include "AiBrainIronShellAutomaton.generated.h"


UCLASS()
class LOSTWORLD_API UAiBrainIronShellAutomaton : public UAiBrainBase
{
	GENERATED_BODY()

public:
	virtual void StartTurn() override;
	virtual void SelectCardToCast() override;
	virtual void GetTargetsForCard(int StackEntryIndex) override;
	virtual void EndTurn() override;
};
