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
	
	void TestCardOne();
};
