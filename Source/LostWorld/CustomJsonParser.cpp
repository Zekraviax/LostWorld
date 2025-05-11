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


FString CustomJsonParser::ParseUStructPropertyIntoJsonString(const FProperty* Property, const void* ValuePointer, const TSharedRef<TJsonWriter<TCHAR>>& InJsonWriter)
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

	// Floats
	if (Cast<FFloatProperty>(Property)) {
		const float FloatValue = Cast<FFloatProperty>(Property)->GetPropertyValue(ValuePointer);
		return FString::SanitizeFloat(FloatValue);
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
		const UEnum* EnumProperty = Cast<FEnumProperty>(Property)->GetEnum();
		FName EnumAsName = EnumProperty->GetNameByIndex(0);
		FString EnumAsString;
		EnumAsName.ToString().Split(TEXT("::"), nullptr, &EnumAsString, ESearchCase::IgnoreCase);
		//FString ReturnString = Cast<FEnumProperty>(Property).Get
		//return UEnum::GetDisplayValueAsText(EnumProperty).ToString();
		return EnumAsString;
	}

	// To-Do: Array handling
	if (Cast<FArrayProperty>(Property)) {
		const FArrayProperty* ArrayProperty = Cast<FArrayProperty>(Property);

		//ALostWorldGameModeBase::DualLog("Parsing FArrayProperty" + ArrayProperty->GetName(), 2);
		FString OutFormattedArrayJsonString = "";
		TSharedRef <TJsonWriter<TCHAR>> ArrayJsonWriter = TJsonWriterFactory<>::Create(&OutFormattedArrayJsonString);

		// Needs an Array Start and an Array End write.
		ArrayJsonWriter->WriteArrayStart("test_array_identifier");
		
		FScriptArrayHelper ArrayHelper(ArrayProperty, ValuePointer);
		for (int32 ArrayEntryIndex = 0; ArrayEntryIndex < ArrayHelper.Num(); ++ArrayEntryIndex) {
			ArrayJsonWriter->WriteObjectStart();
			
			const uint8* ArrayEntryData = ArrayHelper.GetRawPtr(ArrayEntryIndex);
			FString ValueAsString = ParseUStructPropertyIntoJsonString(ArrayProperty->Inner, ArrayEntryData, InJsonWriter);
			ArrayJsonWriter->WriteValue("test_value_identifier", ValueAsString);

			ArrayJsonWriter->WriteObjectEnd();
		}
		
		ArrayJsonWriter->WriteArrayEnd();
		ArrayJsonWriter->Close();

		return OutFormattedArrayJsonString;
	}
	
	return ""; 
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
		
		ValueAsString = ParseUStructPropertyIntoJsonString(Property, Value, InJsonWriter);
		InJsonWriter->WriteValue(VariableName, ValueAsString);
	}
	
	return ValueAsString;
}


// Ongoing To-Do: Functions that use templates need to be explicitly instantiated with all supported types,
// in order to prevent the error "LNK2019: unresolved external symbol".
template LOSTWORLD_API void CustomJsonParser::SerializeTArrayWithRowNames(void* InStructData, const UScriptStruct* InStructDefinition, const TArray<FCard>& InArray, FString& OutJson);
