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
	void ExecuteFunction(ECardFunctions InFunction);

	AActorEntityBase* GetAttacker() const;
	AActorEntityBase* GetDefender() const;
	FStackEntry GetFirstStackEntry() const;

	int StandardDamageFormula(const AActorEntityBase* Attacker,  AActorEntityBase* Defender, int AttackBasePower) const;
	int ArmourBreakerDamageFormula(const AActorEntityBase* Attacker,  AActorEntityBase* Defender, int AttackBasePower) const;

	// -------- Specific to one card -------- //
	void TestCardOne() const;
	void TestCardTwo();
	void TestCardThree() const;
	void TestCardFour() const;
	void PoisonDart() const;
	void ArmourBreaker() const;
	void HyperBeam() const;
	void TestCardFive() const;
	void TestCardSix() const;
	void HowlOfCommand() const;
	void EnergyAllAround() const;
	void CallForFriends();
	void InfectedBite();
	void Vomit() const;
	void HammerBlow() const;
	void Demi() const;
	// -------- Generic functions -------- //
	void GenericDealDamageToOneTarget() const;
	void DrawOneCard() const;
	void ApplyToughnessDown() const;
};
