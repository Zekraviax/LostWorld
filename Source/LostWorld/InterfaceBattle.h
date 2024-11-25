#pragma once


#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Variables.h"
#include "InterfaceBattle.generated.h"


// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UInterfaceBattle : public UInterface
{
	GENERATED_BODY()
};


class LOSTWORLD_API IInterfaceBattle
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	virtual bool OverrideDeck(TArray<FCard> InDeck);
	virtual bool AddCardToDeck(FCard InCard);
	virtual TArray<FCard> ShuffleDeck(TArray<FCard> InDeck);
	virtual bool DrawCard();
	virtual bool DiscardCard(int IndexInHand);
	virtual bool PayCostsForCard(int IndexInHand);

	virtual bool TakeDamage(float Damage);
	virtual bool EntityDefeated();
};
