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

	static int StandardDamageFormula(AActorEntityBase* Attacker, AActorEntityBase* Defender, int AttackBasePower);
	
	void TestCardOne() const;
	void TestCardTwo() const;
};
