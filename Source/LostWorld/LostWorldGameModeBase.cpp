#include "LostWorldGameModeBase.h"



void ALostWorldGameModeBase::DualLog(const FString& PreBuiltString)
{
	GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Orange, FString::Printf(TEXT("%s"), *PreBuiltString));
	UE_LOG(LogTemp, Log, TEXT("%s"), *PreBuiltString);
}


FString ALostWorldGameModeBase::ParseVariablesInText(const FCard& InCard, const FString& InString)
{
	FString ReturnString = InString.Replace(TEXT("${TotalPower}"), *FString::FromInt(InCard.TotalDamage));
	ReturnString = ReturnString.Replace(TEXT("${BasePower}"), *FString::FromInt(InCard.BaseDamage));
	
	return ReturnString;
}
