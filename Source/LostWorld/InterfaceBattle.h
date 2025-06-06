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
	virtual bool AddCardToDeck(FCard InCard);
	virtual bool AddCardToDrawPile(FCard InCard);
	virtual TArray<FCard> ShuffleDrawPile(TArray<FCard> InDeck);
	virtual bool DrawCard();
	virtual bool DiscardCard(int IndexInHand);
	virtual bool PayCostsForCard(int IndexInHand);
	virtual bool ShuffleDiscardPileIntoDrawPile();
	virtual bool BottomCard(FCard InCard);
	virtual bool DrawCreatedCard(FCard InCard);
	
	virtual bool ExileCardFromZone(FString InZoneName, FCard InCard);

	virtual bool EntityTakeDamage(float Damage);
	virtual bool EntityDefeated();

	virtual bool ReceiveHealing(float Healing);
	virtual bool GainMana(int InMana);
	virtual bool GainBarrier(int InBarrier);

	virtual bool AddStatusEffect(FStatusEffect StatusEffect);
	virtual bool HasStatusEffect(EStatusEffectFunctions Function);
	virtual bool GetStatusEffectStacks(EStatusEffectFunctions Function, int& OutStacks);

	virtual bool ReturnOffensiveElementalAffinity(ECardElements Element, int& OutAffinity);
	virtual bool ReturnDefensiveElementalAffinity(ECardElements Element, int& OutAffinity);

	virtual bool StartTurn();
	virtual bool EndTurn();
};
