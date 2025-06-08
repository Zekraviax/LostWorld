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


FString CustomJsonParser::ParseUStructPropertyIntoJsonString(const FProperty* Property, const void* ValuePointer, const TSharedRef<TJsonWriter<TCHAR>>& InJsonWriter, bool WriteToJson)
{
	FString VariableName = Property->GetName();
	FString ValueAsString;
	//float FloatValue;
	//FName NameValue;
	//FText TextValue;

	
	// Strings
	if (Cast<FStrProperty>(Property)) {
		ValueAsString = Cast<FStrProperty>(Property)->GetPropertyValue(ValuePointer);

		if (WriteToJson) {
			InJsonWriter->WriteValue(VariableName, ValueAsString);
		}
	}

	// Integers
	if (Cast<FIntProperty>(Property)) {
		const int IntValue = Cast<FIntProperty>(Property)->GetPropertyValue(ValuePointer);
		
		if (WriteToJson) {
			ValueAsString = FString::FromInt(IntValue);
			InJsonWriter->WriteValue(VariableName, IntValue);
		}
	}

	// Floats
	if (Cast<FFloatProperty>(Property)) {
		const float FloatValue = Cast<FFloatProperty>(Property)->GetPropertyValue(ValuePointer);

		if (WriteToJson) {
			ValueAsString = FString::SanitizeFloat(FloatValue);
			InJsonWriter->WriteValue(VariableName, FloatValue);
		}
	}

	// Booleans
	if (Cast<FBoolProperty>(Property)) {
		const bool BoolValue = Cast<FBoolProperty>(Property)->GetPropertyValue(ValuePointer);

		if (WriteToJson) {
			ValueAsString = BoolValue ? "true" : "false";
			InJsonWriter->WriteValue(VariableName, BoolValue);
		}
	}
	
	// To-Do: Enums
	if (Cast<FEnumProperty>(Property)) {
		const UEnum* EnumTypeProperty = Cast<FEnumProperty>(Property)->GetEnum();
		const FEnumProperty* EnumProperty = CastField<FEnumProperty>(Property);
		
		int64 Value = EnumProperty->GetUnderlyingProperty()->GetSignedIntPropertyValue(ValuePointer);
		TOptional<int64> Result = Value;
		FString EnumAsNameString = EnumTypeProperty->GetNameStringByValue(Result.GetValue());
		
		if (WriteToJson) {
			bool WriteVariableName = false;
			ValueAsString = EnumAsNameString;

			if (WriteVariableName) {
				InJsonWriter->WriteValue(VariableName, ValueAsString);
			} else {
				InJsonWriter->WriteValue(ValueAsString);
			}
		}
	}

	// To-Do: Array handling
	if (Cast<FArrayProperty>(Property)) {
		const FArrayProperty* ArrayProperty = Cast<FArrayProperty>(Property);

		InJsonWriter->WriteArrayStart(VariableName);
		
		FScriptArrayHelper ArrayHelper(ArrayProperty, ValuePointer);
		for (int32 ArrayEntryIndex = 0; ArrayEntryIndex < ArrayHelper.Num(); ++ArrayEntryIndex) {

			const uint8* ArrayEntryData = ArrayHelper.GetRawPtr(ArrayEntryIndex);
			ParseUStructPropertyIntoJsonString(ArrayProperty->Inner, ArrayEntryData, InJsonWriter, true);
		}
		
		InJsonWriter->WriteArrayEnd();
	}
	
	return ValueAsString;
}


FString CustomJsonParser::SerializeSingleUstructToJsonObject(const UStruct* StructDefinition, const void* Struct, const FName InRowName, const TSharedRef<TJsonWriter<TCHAR>>& InJsonWriter, FString& OutFormattedStructAsString)
{
	FString ValueAsString;

	// Before the normal properties can be written to the Json, we need to write the RowName to the json.
	InJsonWriter->WriteValue("Name", InRowName.ToString());
	
	for (TFieldIterator<FProperty> It(StructDefinition); It; ++It) {
		FProperty* Property = *It;

		FString VariableName = Property->GetName();
		const void* Value = Property->ContainerPtrToValuePtr<uint8>(Struct);
		
		ValueAsString = ParseUStructPropertyIntoJsonString(Property, Value, InJsonWriter, true);
	}
	
	return ValueAsString;
}


// Ongoing To-Do: Functions that use templates need to be explicitly instantiated with all supported types,
// in order to prevent the error "LNK2019: unresolved external symbol".
//template LOSTWORLD_API void CustomJsonParser::SerializeTArrayWithRowNames(void* InStructData, const UScriptStruct* InStructDefinition, const TArray<FCard>& InArray, FString& OutJson);
