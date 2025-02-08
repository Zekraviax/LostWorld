#pragma once


#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "InterfaceEntity.generated.h"


UINTERFACE(MinimalAPI)
class UInterfaceEntity : public UInterface
{
	GENERATED_BODY()
};


class LOSTWORLD_API IInterfaceEntity
{
	GENERATED_BODY()

public:
	virtual bool CalculateTotalStats();
};
