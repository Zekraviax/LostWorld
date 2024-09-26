#include "LostWorldGameModeBase.h"


void ALostWorldGameModeBase::DualLog(const FString& PreBuiltString)
{
	GEngine->AddOnScreenDebugMessage(-1, 20.f, FColor::Orange, FString::Printf(TEXT("%s"), *PreBuiltString));
	UE_LOG(LogTemp, Log, TEXT("%s"), *PreBuiltString);
}
