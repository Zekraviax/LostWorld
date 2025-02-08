#pragma once


#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Variables.h"
#include "FunctionLibraryStatusEffects.generated.h"

class AActorEntityBase;


UCLASS()
class LOSTWORLD_API AFunctionLibraryStatusEffects : public AActor
{
	GENERATED_BODY()
	
public:
	static void ExecuteFunction(EStatusEffectFunctions InFunction, AActorEntityBase* InEffectedEntity);

	static void Poison (AActorEntityBase* EffectedEntity);
	static void IronShell(AActorEntityBase* EffectedEntity);
};
