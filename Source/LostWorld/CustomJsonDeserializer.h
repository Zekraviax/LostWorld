#pragma once


#include "CoreMinimal.h"
#include "Variables.h"


class LOSTWORLD_API CustomJsonDeserializer
{

private:
	TSharedPtr<FJsonValue> JsonValue;
	
public:
	FEncounter EncounterAsStruct;
	FString EncounterAsString;
	
	CustomJsonDeserializer();
	~CustomJsonDeserializer();

	FEncounter DeserializeEncounterJson(const FString& InEncounterAsString, const FString& EncounterRowName);
};
