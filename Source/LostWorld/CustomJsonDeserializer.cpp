#include "CustomJsonDeserializer.h"


#include "CoreMinimal.h"
#include "Json.h"
#include "JsonObjectConverter.h"
#include "LostWorldGameInstanceBase.h"
#include "LostWorldGameModeBase.h"


CustomJsonDeserializer::CustomJsonDeserializer()
{
}


CustomJsonDeserializer::~CustomJsonDeserializer()
{
}


FEncounter CustomJsonDeserializer::DeserializeEncounterJson(const FString& InEncounterAsString, const FString& EncounterRowName)
{
	TSharedRef<TJsonReader<>> JsonReader = TJsonReaderFactory<>::Create(InEncounterAsString);

	if (FJsonSerializer::Deserialize(JsonReader, JsonValue) && JsonValue.IsValid()) {
		ALostWorldGameModeBase::DualLog("Deserialized Encounters json.", 2);
		TSharedPtr<FJsonObject> FirstObject = JsonValue->AsArray()[0]->AsObject();

		for (int i = 0; i < JsonValue->AsArray().Num(); i++) {
			if (JsonValue->AsArray()[i]->AsObject()->GetStringField("Name") == EncounterRowName) {
				TSharedPtr<FJsonObject> ObjectSharedPtr = JsonValue->AsArray()[i]->AsObject();
				FEncounter ReturnEncounter = FEncounter();

				// Encounter Type
				FString EncounterTypeString = ObjectSharedPtr->GetStringField("EncounterType");
				int EncounterTypeIndex = StaticEnum<EEncounterTypes>()->GetValueByNameString(EncounterTypeString);
				ReturnEncounter.EncounterType = static_cast<EEncounterTypes>(EncounterTypeIndex);

				// Array of Entity Types
				ReturnEncounter.EntityTypes.Empty();
				for (int EnemyCount = 0; EnemyCount < ObjectSharedPtr->GetArrayField("EntityTypes").Num(); EnemyCount++) {
					const TSharedPtr<FJsonValue>& ArrayObject = ObjectSharedPtr->GetArrayField("EntityTypes")[EnemyCount];
					FString ObjectAsString = "";
					ArrayObject->TryGetString(ObjectAsString);
					
					ReturnEncounter.EntityTypes.Add(ULostWorldGameInstanceBase::EntityTypeStringToEnumValue(ObjectAsString));
				}

				// To-Do: Minimum and maximum floor
				
				return ReturnEncounter;
			}
		}
	} else {
		ALostWorldGameModeBase::DualLog("Error! Could not deserialize Encounters json.", 2);
	}
	
	return FEncounter();
}
