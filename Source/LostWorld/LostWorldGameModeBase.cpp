#include "LostWorldGameModeBase.h"


#include "LostWorldGameInstanceBase.h"
#include "Kismet/GameplayStatics.h"
#include "SaveGameDeveloperSettings.h"


void ALostWorldGameModeBase::DualLog(const FString& PreBuiltString, int InLogLevel)
{
	if (Cast<ULostWorldGameInstanceBase>(GEngine->GameViewport->GetWorld()->GetGameInstance())->
		DeveloperSettingsSaveGame->DeveloperSettingsAsStruct.LogLevel >= InLogLevel) {
		GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Orange, FString::Printf(TEXT("%s"), *PreBuiltString));
		UE_LOG(LogTemp, Log, TEXT("%s"), *PreBuiltString);
	}
}


FString ALostWorldGameModeBase::ParseVariablesInText(const FCard& InCard, const FString& InString)
{
	FString ReturnString = InString.Replace(TEXT("${TotalPower}"), *FString::FromInt(InCard.TotalDamage));
	ReturnString = ReturnString.Replace(TEXT("${BasePower}"), *FString::FromInt(InCard.BaseDamage));
	
	return ReturnString;
}
