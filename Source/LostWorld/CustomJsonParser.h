#pragma once


#include "CoreMinimal.h"
#include "Json.h"
#include "Kismet/KismetSystemLibrary.h"


class LOSTWORLD_API CustomJsonParser
{
public:
	CustomJsonParser();
	~CustomJsonParser();

	// UE already has built-in functions for writing properly formatted JSON that we can use.
	static FString ParseUStructPropertyIntoJsonString(const FProperty* Property, const void* ValuePointer);
	
	template<typename T>
	void SerializeTArrayWithRowNames(void* InStructData, const UScriptStruct* InStructDefinition, const TArray<T>& InArray, FString& OutJson);

	//void CustomSerializeStruct(void* InStructData, const UScriptStruct* InStructDefinition, FString& OutJson);

	template<typename InStructType>
	void BeginSerializationOfGenericStruct(const InStructType& InStruct)
	{
		SerializeSingleUstructToJsonObject(InStructType::StaticStruct(), &InStruct);
	};
	
	FString SerializeSingleUstructToJsonObject(const UStruct* StructDefinition, const void* Struct);

	/** This function takes a Struct Definition, then creates a formatted JSON string with X array entries,
	then outputs the structured FString.*/
	FString CreateStructuredJsonString(int MaxLoopCount, void* InStructData, const UScriptStruct* InStructDefinition);
};
