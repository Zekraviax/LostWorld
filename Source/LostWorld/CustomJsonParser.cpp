#include "CustomJsonParser.h"


#include "JsonObjectConverter.h"
#include "LostWorldGameModeBase.h"
#include "PropertyPathHelpers.h"


CustomJsonParser::CustomJsonParser()
{
}

CustomJsonParser::~CustomJsonParser()
{
}


FString CustomJsonParser::ParseUStructPropertyIntoJsonString(const FProperty* Property, const void* ValuePointer)
{
	//float FloatValue;
	//FName NameValue;
	//FText TextValue;

	
	// Strings
	if (Cast<FStrProperty>(Property)) {
		//FString StringValue = "\"" + Cast<UStrProperty>(Property)->GetName() + "\": \"" + Cast<UStrProperty>(Property)->GetPropertyValue(ValuePointer) + "\"";
		//FString StringValue = Cast<UStrProperty>(Property)->GetName() + "\": \"" + Cast<UStrProperty>(Property)->GetPropertyValue(ValuePointer);
		FString StringValue = Cast<FStrProperty>(Property)->GetPropertyValue(ValuePointer);
		return StringValue;
	}

	// Integers
	if (Cast<FIntProperty>(Property)) {
		const int IntValue = Cast<FIntProperty>(Property)->GetPropertyValue(ValuePointer);
		//return "\"" + Cast<UIntProperty>(Property)->GetName() + "\": \"" + FString::FromInt(IntValue) + "\"";
		return FString::FromInt(IntValue);
	}

	// Booleans
	if (Cast<FBoolProperty>(Property)) {
		const bool BoolValue = Cast<FBoolProperty>(Property)->GetPropertyValue(ValuePointer);
		return BoolValue ? "true" : "false";
		//FString BoolValueAsString = BoolValue ? "true" : "false";
		//return "\"" + Cast<FBoolProperty>(Property)->GetName() = "\"" + Cast<FStrProperty>(Property)->GetName() + "\": \"" + BoolValueAsString + "\"";
	}
	
	// To-Do: Enums
	if (Cast<FEnumProperty>(Property)) {
		
	}

	// To-Do: Array handling
	if (Cast<FArrayProperty>(Property)) {
		//JsonWriter->WriteArrayStart();
	}
	
	return "";
}


/*template <typename T>
void CustomJsonParser::SerializeTArrayWithRowNames(void* InStructData, const UScriptStruct* InStructDefinition, const TArray<T>& InArray, FString& OutJson)
{
	FString JsonString;
	TSharedRef <TJsonWriter<TCHAR>> JsonWriter = TJsonWriterFactory<>::Create(&JsonString);
	
	// Start writing the Json string.
	JsonWriter->WriteArrayStart();
	JsonWriter->WriteObjectStart();

	// Write the Row Name to the Json string first, then fetch the value.
	for (TFieldIterator<FProperty> Iterator(InStructDefinition); Iterator; ++Iterator) {
		const FProperty* Property = *Iterator;

		// Get variable name.
		FString VariableName = Property->GetName();

		for (int32 ArrayIndex = 0; ArrayIndex < Property->ArrayDim; ArrayIndex++) {
			// Get the pointer to where the data is stored.
			void* ValuePointer = Property->ContainerPtrToValuePtr<void>(InStructData, ArrayIndex);

			// Parse the variable into two different strings: the name and the value.
			FString ParsedVariable = ParseUStructPropertyIntoJsonString(Property, ValuePointer);
			JsonWriter->WriteValue(VariableName, ParsedVariable);
		}
	}
	
	JsonWriter->WriteObjectEnd();
	JsonWriter->WriteArrayEnd();
	JsonWriter->Close();

	OutJson = JsonString;
	//ALostWorldGameModeBase::DualLog("", 2);
}*/


/*template <typename InStructType>
FString CustomJsonParser::SerializeSingleUstructToJsonObject(const InStructType& InStruct)
{
	const UStruct* StructDefinition = InStruct::StaticStruct();
	const void Struct = &InStruct;

	for (TFieldIterator<FProperty> It(StructDefinition); It; ++It)
	{
		FProperty* Property = *It;

		FString VariableName = StandardizeCase(Property->GetName());
		const void* Value = Property->ContainerPtrToValuePtr<uint8>(Struct);
	}
}*/


/*void CustomJsonParser::CustomSerializeStruct(void* InStructData, const UScriptStruct* InStructDefinition, FString& OutJson)
{
	for (TFieldIterator<FProperty> Iterator(InStructDefinition); Iterator; ++Iterator) {
		const FProperty* Property = *Iterator;

		// Get variable name.
		FString VariableName = Property->GetName();

		for (int32 ArrayIndex = 0; ArrayIndex < Property->ArrayDim; ArrayIndex++) {
			// Get the pointer to where the data is stored.
			void* ValuePointer = Property->ContainerPtrToValuePtr<void>(InStructData, ArrayIndex);

			// Parse the variable into two different strings: the name and the value.
			OutJson = ParseUStructPropertyIntoJsonString(Property, ValuePointer);
			//JsonWriter->WriteValue(VariableName, ParsedVariable);
		}
	}
}*/


FString CustomJsonParser::SerializeSingleUstructToJsonObject(const UStruct* StructDefinition, const void* Struct, FName InRowName, TSharedRef<TJsonWriter<TCHAR>> InJsonWriter, FString& OutFormattedStructAsString)
{
	FString ValueAsString;

	// Before the normal properties can be written to the Json, we need to write the RowName to the json.
	InJsonWriter->WriteValue("Name", InRowName.ToString());
	
	for (TFieldIterator<FProperty> It(StructDefinition); It; ++It) {
		FProperty* Property = *It;

		FString VariableName = Property->GetName();
		const void* Value = Property->ContainerPtrToValuePtr<uint8>(Struct);
		
		ValueAsString = ParseUStructPropertyIntoJsonString(Property, Value);
		InJsonWriter->WriteValue(VariableName, ValueAsString);
		//OutUnformattedStructAsString = ValueAsString;
	}
	
	return ValueAsString;
}


/*FString CustomJsonParser::CreateStructuredJsonString()
{
	FString ReturnStructuredJsonString;
	TSharedRef <TJsonWriter<TCHAR>> JsonWriter = TJsonWriterFactory<>::Create(&ReturnStructuredJsonString);
	
	// Start writing the Json string.
	JsonWriter->WriteArrayStart();
	JsonWriter->WriteObjectStart();

	/*for (int LoopCount = 0; LoopCount < MaxLoopCount; LoopCount++) {
		JsonWriter->WriteObjectStart();

		// Write the Row Name to the Json string first, then fetch the value.
		/*for (TFieldIterator<FProperty> Iterator(InStructDefinition); Iterator; ++Iterator) {
			const FProperty* Property = *Iterator;

			// Get variable name.
			FString VariableName = Property->GetName();

			for (int32 ArrayIndex = 0; ArrayIndex < Property->ArrayDim; ArrayIndex++) {
				// Get the pointer to where the data is stored.
				void* ValuePointer = Property->ContainerPtrToValuePtr<void>(InStructData, ArrayIndex);

				// Parse the variable into two different strings: the name and the value.
				FString ParsedVariable = ParseUStructPropertyIntoJsonString(Property, ValuePointer);
				JsonWriter->WriteValue(VariableName, ParsedVariable);
			}
		}
		
		FString SerializedStruct = "";
	
		JsonWriter->WriteObjectEnd();
	}

	JsonWriter->WriteObjectEnd();
	JsonWriter->WriteArrayEnd();
	JsonWriter->Close();
	
	return ReturnStructuredJsonString;
}*/


// Ongoing To-Do: Functions that use templates need to be explicitly instantiated with all supported types,
// in order to prevent the error "LNK2019: unresolved external symbol".
//template LOSTWORLD_API void CustomJsonParser::SerializeSingleUstructToJsonObject(const FCard& InStruct);
template LOSTWORLD_API void CustomJsonParser::SerializeTArrayWithRowNames(void* InStructData, const UScriptStruct* InStructDefinition, const TArray<FCard>& InArray, FString& OutJson);
