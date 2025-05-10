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
	//FString OutputJsonString;
	//TSharedRef<TJsonWriter<TCHAR>> JsonWriter = TJsonWriterFactory<>::Create(&OutputJsonString);
	
	static FString ParseUStructPropertyIntoJsonString(const FProperty* Property, const void* ValuePointer);




	/*template<typename T>
	UFUNCTION(BlueprintCallable, CustomThunk, meta = (CustomStructureParam = "AnyStruct"))
	static void InputAnyStruct(UStruct* AnyStruct);
	
	DECLARE_FUNCTION(execInputAnyStruct)
	{
		// Step into the stack; walking to the next property within the stack.
		Stack.Step(Stack.Object, NULL);

		// Grab the last Property we found when we walked into the stack.
		// This doesn't contain the Property's value; only it's type info.
		FProperty* StructProperty = CastField<FProperty>(Stack.MostRecentProperty);
		//FArrayProperty* ArrayProperty = CastField<FArrayProperty>(Stack.MostRecentProperty);

		// Grab the base address where the structs' data is actually stored.
		// This does contain the Property's value.
		void* StructPointer = Stack.MostRecentPropertyAddress;
		//void* ArrayAddr = Stack.MostRecentPropertyAddress;

		// Wrap up our use of the stack.
		P_FINISH

		// We can pass the values we found into a function that iterates through the struct Properties.
		//GenericInputAnyStruct(ArrayAddr, ArrayProperty);
		//IterateThroughStructProperties(StructProperty, StructPointer);
	}*/

	//static void GenericInputAnyStruct(void* TargetArray, const FArrayProperty* ArrayProp);
	
	//static void IterateThroughStructProperties(FProperty* Property, void* StructPointer);
	
	


	

	// We need to use a CustomThunk to get the Ustruct data addresses.
	template<typename T>
	void SerializeTArrayWithRowNames(void* InStructData, const UScriptStruct* InStructDefinition, const TArray<T>& InArray, FString& OutJson);

	//template<typename T>
	//void FunctionWithGenericArray(const TArray<T>& TargetArray);

	/* Example function for parsing a single property
	* @param Property    the property reflection data
	* @param ValuePtr    the pointer to the property value
	*/
	/*void ParseProperty(UProperty* Property, void* ValuePtr)
	{        
	        
	    float FloatValue;
	    int32 IntValue;
	    bool BoolValue;
	    FString StringValue;
	    FName NameValue;
	    FText TextValue;
	 
	 
	    // Here's how to read integer and float properties
	    if (UNumericProperty *NumericProperty = Cast<UNumericProperty>(Property))
	    {
	        if (NumericProperty->IsFloatingPoint())
	        {
	            FloatValue = NumericProperty->GetFloatingPointPropertyValue(ValuePtr);
	        }
	        else if (NumericProperty->IsInteger())
	        {
	            IntValue = NumericProperty->GetSignedIntPropertyValue(ValuePtr);
	        }
	    }
	 
	    // How to read booleans
	    if (UBoolProperty* BoolProperty = Cast<UBoolProperty>(Property))
	    {
	        BoolValue = BoolProperty->GetPropertyValue(ValuePtr);
	    }
	 
	    // Reading names
	    if (UNameProperty* NameProperty = Cast<UNameProperty>(Property))
	    {
	        NameValue = NameProperty->GetPropertyValue(ValuePtr);
	    }
	 
	    // Reading strings
	    if (UStrProperty* StringProperty = Cast<UStrProperty>(Property))
	    {
	        StringValue = StringProperty->GetPropertyValue(ValuePtr);
	    }
	 
	    // Reading texts
	    if (UTextProperty* TextProperty = Cast<UTextProperty>(Property))
	    {
	        TextValue = TextProperty->GetPropertyValue(ValuePtr);
	    }
	 
	    // Reading an array
	    if (UArrayProperty* ArrayProperty = Cast<UArrayProperty>(Property))
	    {
	        // We need the helper to get to the items of the array            
	        FScriptArrayHelper Helper(ArrayProperty, ValuePtr);
	        for (int32 i = 0, n = Helper.Num(); i<n; ++i)
	        {    
	            ParseProperty(ArrayProperty->Inner, Helper.GetRawPtr(i));
	        }
	    }
	 
	    // Reading a nested struct
	    if (UStructProperty* StructProperty = Cast<UStructProperty>(Property))
	    {
	        IterateThroughStructProperty(StructProperty, ValuePtr);
	    }
	}*/
	
	/* Example function for iterating through all properties of a struct
	* @param StructProperty    The struct property reflection data
	* @param StructPtr        The pointer to the struct value*/
	/*void IterateThroughStructProperty(UStructProperty* StructProperty, void* StructPtr)
	{
		// Walk the structs' properties
		UScriptStruct* Struct = StructProperty->Struct;
		for (TFieldIterator<UProperty> It(Struct); It; ++It)
		{
			UProperty* Property = *It;
 
			// This is the variable name if you need it
			FString VariableName = Property->GetName();
 
			// Never assume ArrayDim is always 1
			for (int32 ArrayIndex = 0; ArrayIndex < Property->ArrayDim; ArrayIndex++)
			{
				// This grabs the pointer to where the property value is stored
				void* ValuePtr = Property->ContainerPtrToValuePtr<void>(StructPtr, ArrayIndex);
 
				// Parse this property
				ParseProperty(Property, ValuePtr);
			}
		}
	}*/
};
