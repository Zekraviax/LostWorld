// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "LostWorld/SaveGameLevelData.h"
#ifdef _MSC_VER
#pragma warning (push)
#pragma warning (disable : 4883)
#endif
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeSaveGameLevelData() {}
// Cross Module References
	LOSTWORLD_API UClass* Z_Construct_UClass_USaveGameLevelData_NoRegister();
	LOSTWORLD_API UClass* Z_Construct_UClass_USaveGameLevelData();
	ENGINE_API UClass* Z_Construct_UClass_USaveGame();
	UPackage* Z_Construct_UPackage__Script_LostWorld();
// End Cross Module References
	DEFINE_FUNCTION(USaveGameLevelData::execSaveLevelDataToJson)
	{
		P_FINISH;
		P_NATIVE_BEGIN;
		P_THIS->SaveLevelDataToJson();
		P_NATIVE_END;
	}
	void USaveGameLevelData::StaticRegisterNativesUSaveGameLevelData()
	{
		UClass* Class = USaveGameLevelData::StaticClass();
		static const FNameNativePtrPair Funcs[] = {
			{ "SaveLevelDataToJson", &USaveGameLevelData::execSaveLevelDataToJson },
		};
		FNativeFunctionRegistrar::RegisterFunctions(Class, Funcs, UE_ARRAY_COUNT(Funcs));
	}
	struct Z_Construct_UFunction_USaveGameLevelData_SaveLevelDataToJson_Statics
	{
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_USaveGameLevelData_SaveLevelDataToJson_Statics::Function_MetaDataParams[] = {
		{ "Comment", "// ---------------------------------------- Functions ---------------------------------------- //\n// Fallback function.\n// Should only be used if the level data JSON cannot be found.\n" },
		{ "ModuleRelativePath", "SaveGameLevelData.h" },
		{ "ToolTip", "---------------------------------------- Functions ----------------------------------------\nFallback function.\nShould only be used if the level data JSON cannot be found." },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_USaveGameLevelData_SaveLevelDataToJson_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_USaveGameLevelData, nullptr, "SaveLevelDataToJson", nullptr, nullptr, 0, nullptr, 0, RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_USaveGameLevelData_SaveLevelDataToJson_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_USaveGameLevelData_SaveLevelDataToJson_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_USaveGameLevelData_SaveLevelDataToJson()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_USaveGameLevelData_SaveLevelDataToJson_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	UClass* Z_Construct_UClass_USaveGameLevelData_NoRegister()
	{
		return USaveGameLevelData::StaticClass();
	}
	struct Z_Construct_UClass_USaveGameLevelData_Statics
	{
		static UObject* (*const DependentSingletons[])();
		static const FClassFunctionLinkInfo FuncInfo[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UE4CodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_USaveGameLevelData_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_USaveGame,
		(UObject* (*)())Z_Construct_UPackage__Script_LostWorld,
	};
	const FClassFunctionLinkInfo Z_Construct_UClass_USaveGameLevelData_Statics::FuncInfo[] = {
		{ &Z_Construct_UFunction_USaveGameLevelData_SaveLevelDataToJson, "SaveLevelDataToJson" }, // 1592598411
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_USaveGameLevelData_Statics::Class_MetaDataParams[] = {
		{ "IncludePath", "SaveGameLevelData.h" },
		{ "ModuleRelativePath", "SaveGameLevelData.h" },
	};
#endif
	const FCppClassTypeInfoStatic Z_Construct_UClass_USaveGameLevelData_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<USaveGameLevelData>::IsAbstract,
	};
	const UE4CodeGen_Private::FClassParams Z_Construct_UClass_USaveGameLevelData_Statics::ClassParams = {
		&USaveGameLevelData::StaticClass,
		nullptr,
		&StaticCppClassTypeInfo,
		DependentSingletons,
		FuncInfo,
		nullptr,
		nullptr,
		UE_ARRAY_COUNT(DependentSingletons),
		UE_ARRAY_COUNT(FuncInfo),
		0,
		0,
		0x001000A0u,
		METADATA_PARAMS(Z_Construct_UClass_USaveGameLevelData_Statics::Class_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UClass_USaveGameLevelData_Statics::Class_MetaDataParams))
	};
	UClass* Z_Construct_UClass_USaveGameLevelData()
	{
		static UClass* OuterClass = nullptr;
		if (!OuterClass)
		{
			UE4CodeGen_Private::ConstructUClass(OuterClass, Z_Construct_UClass_USaveGameLevelData_Statics::ClassParams);
		}
		return OuterClass;
	}
	IMPLEMENT_CLASS(USaveGameLevelData, 1704427283);
	template<> LOSTWORLD_API UClass* StaticClass<USaveGameLevelData>()
	{
		return USaveGameLevelData::StaticClass();
	}
	static FCompiledInDefer Z_CompiledInDefer_UClass_USaveGameLevelData(Z_Construct_UClass_USaveGameLevelData, &USaveGameLevelData::StaticClass, TEXT("/Script/LostWorld"), TEXT("USaveGameLevelData"), false, nullptr, nullptr, nullptr);
	DEFINE_VTABLE_PTR_HELPER_CTOR(USaveGameLevelData);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
#ifdef _MSC_VER
#pragma warning (pop)
#endif
