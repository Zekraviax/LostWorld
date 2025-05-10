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


/*void CustomJsonParser::IterateThroughStructProperties(FProperty* Property, void* StructPointer)
{
	FStructProperty* StructProperty = CastField<FStructProperty>(Property);

	if (StructProperty) {
		for (TFieldIterator<FProperty> PropertyIterator(StructProperty->Struct); PropertyIterator; ++PropertyIterator) {
			// Get the variable name
			FString VariableName = *PropertyIterator->GetAuthoredName();

			for (int32 ArrayIndex = 0; ArrayIndex < PropertyIterator->ArrayDim; ArrayIndex++) {
				// Grab the pointer that points to where the property value is stored.
				void* ValuePointer = PropertyIterator->ContainerPtrToValuePtr<void>(StructPointer, ArrayIndex);

				// Parse the property here.
				FString PropertyAsString = ParseUStructPropertyIntoJsonString(Property, ValuePointer);
			}
		}
	}
}*/



//void CustomJsonParser::GenericInputAnyStruct(void* TargetArray, const FArrayProperty* ArrayProp)
//{
//	ALostWorldGameModeBase::DualLog("", 2);
//}


template <typename T>
void CustomJsonParser::SerializeTArrayWithRowNames(void* InStructData, const UScriptStruct* InStructDefinition, const TArray<T>& InArray, FString& OutJson)
{
	//auto ArrayVariable = CastField<FArrayProperty>(InStructData);

	//if (Cast<FArrayProperty>(InStructData)) {
	//	ALostWorldGameModeBase::DualLog("", 2);
	//} else {
	//	ALostWorldGameModeBase::DualLog("", 2);
	//}

	
	//if (InRowNames.Num() != InArrayItems.Num()) {
		//ALostWorldGameModeBase::DualLog("Error! Number of RowNames and ArrayItems does not match.", 1);
	//if (!TargetArray){
	//	ALostWorldGameModeBase::DualLog("Error! InArray is not valid.", 1);
	//} else {

	/*FString JsonString;
	TArray<TSharedPtr<FJsonValue>> JsonArray;

	for (int Index = 0; Index < InRowNames.Num(); Index++) {
		TSharedPtr<FJsonObject> JsonObjectWithRowName = MakeShareable(new FJsonObject);
		TSharedPtr<FJsonObject> ArrayItemJsonObject = MakeShareable(new FJsonObject);
		TMap<FString, TSharedPtr<FJsonValue>> OutJsonAttributes;*/
			
			//if (FJsonObjectConverter::UStructToJsonObject(InStruct, InArrayItems[Index], ArrayItemJsonObject, 0, 0)) {
		
			//if (FJsonObjectConverter::UStructToJsonAttributes(InArray::StaticClass(), InArrayItems[Index], OutJsonAttributes, 0, 0, 0, nullptr, true)) {
				//JsonObjectWithRowName->SetStringField("Name", InRowNames[Index].ToString());
				//JsonObjectWithRowName->SetObjectField("ObjectTest", ArrayItemJsonObject);

				//JsonArray.Add(MakeShareable(JsonObjectWithRowName));
			//} else {}
		//}

		//TSharedRef<TJsonWriter<>> Writer = TJsonWriterFactory<>::Create(&JsonString);
		//FJsonSerializer::Serialize(JsonArray, Writer);
	//}

	//for (TFieldIterator<const FProperty> It(InStruct); It; ++It) {}

	
	// Clear the Json string, then append the start of an array in string format.
	//FullJsonString = "[\n{\n";
	//JsonWriter->WriteObjectStart();




	
	// test
	FString JsonString;
	TSharedRef <TJsonWriter<TCHAR>> JsonWriter = TJsonWriterFactory<>::Create(&JsonString);
	// Write data
	JsonWriter->WriteArrayStart();
	JsonWriter->WriteObjectStart();
	//JsonWriter->WriteObjectStart();
	//JsonWriter->WriteObjectStart("TestData");
	//JsonWriter->WriteValue("Name", TEXT("Bob"));
	//JsonWriter->WriteValue("Age", 32);
	//JsonWriter->WriteObjectEnd();
	//JsonWriter->WriteObjectEnd();
	//JsonWriter->Close();

	

	
	
	//JsonWriter->WriteObjectStart();
	//sonWriter->WriteObjectStart("TestData");


	//for (auto& StructItem : InStructArray) {}
	//for (TFieldIterator<void*> Iterator(InStructData); Iterator; ++Iterator) {}

	//int32 NewIndex = INDEX_NONE;
	//if (InStructData) {
		//FScriptArrayHelper ArrayHelper(InStruct, InStructData);
		//FProperty* InnerProp = ArrayProp->Inner;

		//NewIndex = ArrayHelper.AddValue();
		//InnerProp->CopySingleValueToScriptVM(ArrayHelper.GetRawPtr(NewIndex), NewItem);

		//TArray<void>& Array = *InStructData;
	//}

	//for (auto& Element : InArray) {
	//	ALostWorldGameModeBase::DualLog("", 2);
	//}
	

	// Iterate through every array element.
	//for (auto& Element : InArray) {
		// Iterate through all of the UStructs' properties.
		for (TFieldIterator<FProperty> Iterator(InStructDefinition); Iterator; ++Iterator) {
			const FProperty* Property = *Iterator;

			// Get variable name.
			//UObject* Value = *Property->ContainerPtrToValuePtr<UObject*>(InStructData);
			FString VariableName = Property->GetName();

			for (int32 ArrayIndex = 0; ArrayIndex < Property->ArrayDim; ArrayIndex++) {
				// Get the pointer to where the data is stored.
				void* ValuePointer = Property->ContainerPtrToValuePtr<void>(InStructData, ArrayIndex);
				//void* ValuePointer = Property->ContainerPtrToValuePtr<void>((void* )Element, ArrayIndex);

				//Element->GetClass()->FindPropertyByName();

				// To-Do: Get the corresponding property from the UStruct.

				// Parse the variable into two different strings: the name and the value.
				FString ParsedVariable = ParseUStructPropertyIntoJsonString(Property, ValuePointer);
				//+ ",\n";

				// The first variable is the Row name.
				//if (ArrayIndex == 0) {

				//JsonWriter->WriteObjectStart(ParsedVariable);
				//JsonWriter->WriteValue("test name", "test value");
				//JsonWriter->WriteObjectEnd();

				//JsonWriter->WriteObjectStart("VariableTest");
				//JsonWriter->WriteObjectStart();
				JsonWriter->WriteValue(VariableName, ParsedVariable);
				//JsonWriter->WriteObjectEnd();

				//}
			}

			//ALostWorldGameModeBase::DualLog("", 2);
		}

		//OutputFullJsonString += "\r}\r]";
		//JsonWriter->WriteObjectEnd();
		JsonWriter->WriteObjectEnd();
		JsonWriter->WriteArrayEnd();
		JsonWriter->Close();

		OutJson = JsonString;
		ALostWorldGameModeBase::DualLog("", 2);
	//}
}


// Ongoing To-Do: Functions that use templates need to be explicitly instantiated with all supported types,
// in order to prevent the error "LNK2019: unresolved external symbol".
//template LOSTWORLD_API void CustomJsonParser::InputAnyStruct(FCard* AnyStruct);
template LOSTWORLD_API void CustomJsonParser::SerializeTArrayWithRowNames(void* InStructData, const UScriptStruct* InStructDefinition, const TArray<FCard>& InArray, FString& OutJson);


/*template <typename T>
void CustomJsonParser::FunctionWithGenericArray(const TArray<T>& TargetArray)
{
	for (auto& Element : TargetArray) {
		
	}
}*/
