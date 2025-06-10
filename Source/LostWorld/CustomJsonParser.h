#pragma once


#include "CoreMinimal.h"


class LOSTWORLD_API CustomJsonParser
{
public:
	CustomJsonParser();
	~CustomJsonParser();

	// UE already has built-in functions for writing properly formatted JSON that we can use.
	static FString ParseUStructPropertyIntoJsonString(const FProperty* Property, const void* ValuePointer, const TSharedRef<TJsonWriter<TCHAR>>& InJsonWriter, bool InWriteToJson, bool InWriteVariableName);
	
	template<typename InStructType>
	void BeginSerializationOfGenericStruct(const InStructType& InStruct, FName InRowName, TSharedRef<TJsonWriter<TCHAR>> InJsonWriter, FString& OutFormattedStructAsString)
	{
		SerializeSingleUstructToJsonObject(InStructType::StaticStruct(), &InStruct, InRowName, InJsonWriter, OutFormattedStructAsString);
	};
	
	FString SerializeSingleUstructToJsonObject(const UStruct* StructDefinition, const void* Struct, FName InRowName, const TSharedRef<TJsonWriter<TCHAR>>& InJsonWriter, FString& OutFormattedStructAsString);

	
	template<typename InStructType>
	void BeginCreationOfStructuredJsonString(const TArray<InStructType>& InStruct, TArray<FName> InRowNames, FString& OutFormattedJsonString) {
		FString UnformattedStructAsString;
		
		TSharedRef<TJsonWriter<TCHAR>> JsonWriter = TJsonWriterFactory<>::Create(&OutFormattedJsonString);
		JsonWriter = TJsonWriterFactory<>::Create(&OutFormattedJsonString);
	
		// Start writing the Json string.
		JsonWriter->WriteArrayStart();

		for (int Index = 0; Index < InStruct.Num(); Index++) {
			JsonWriter->WriteObjectStart();
			
			BeginSerializationOfGenericStruct(InStruct[Index], InRowNames[Index], JsonWriter,OutFormattedJsonString);

			JsonWriter->WriteObjectEnd();
		}
		
		JsonWriter->WriteArrayEnd();
		JsonWriter->Close();
	}
};
