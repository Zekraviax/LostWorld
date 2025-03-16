#pragma once


#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Variables.h"
#include "FunctionLibraryCards.generated.h"


UCLASS()
class LOSTWORLD_API AFunctionLibraryCards : public AActor
{
	GENERATED_BODY()
	
public:
	void ExecuteFunction(ECardFunctions InFunction) const;

	AActorEntityBase* GetAttacker() const;
	AActorEntityBase* GetDefender() const;

	static int StandardDamageFormula(const AActorEntityBase* Attacker, const AActorEntityBase* Defender, int AttackBasePower);
	static int ArmourBreakerDamageFormula(const AActorEntityBase* Attacker, const AActorEntityBase* Defender, int AttackBasePower);

	// -------- Specific to one card -------- //
	void TestCardOne() const;
	void TestCardTwo() const;
	void TestCardThree() const;
	void TestCardFour() const;
	void PoisonDart() const;
	void ArmourBreaker() const;
	void HyperBeam() const;
	void TestCardFive() const;
	void TestCardSix() const;
	void HowlOfCommand() const;
	void EnergyAllAround() const;
	void CallForFriends() const;
	void InfectedBite() const;
	// -------- Generic functions -------- //
	void GenericDealDamageToOneTarget() const;
};
