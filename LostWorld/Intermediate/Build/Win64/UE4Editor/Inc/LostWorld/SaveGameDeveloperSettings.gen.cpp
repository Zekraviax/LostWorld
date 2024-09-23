// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "LostWorld/SaveGameDeveloperSettings.h"
#ifdef _MSC_VER
#pragma warning (push)
#pragma warning (disable : 4883)
#endif
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeSaveGameDeveloperSettings() {}
// Cross Module References
	LOSTWORLD_API UScriptStruct* Z_Construct_UScriptStruct_FDeveloperSettingsAsStruct();
	UPackage* Z_Construct_UPackage__Script_LostWorld();
	LOSTWORLD_API UClass* Z_Construct_UClass_USaveGameDeveloperSettings_NoRegister();
	LOSTWORLD_API UClass* Z_Construct_UClass_USaveGameDeveloperSettings();
	ENGINE_API UClass* Z_Construct_UClass_USaveGame();
// End Cross Module References
class UScriptStruct* FDeveloperSettingsAsStruct::StaticStruct()
{
	static class UScriptStruct* Singleton = NULL;
	if (!Singleton)
	{
		extern LOSTWORLD_API uint32 Get_Z_Construct_UScriptStruct_FDeveloperSettingsAsStruct_Hash();
		Singleton = GetStaticStruct(Z_Construct_UScriptStruct_FDeveloperSettingsAsStruct, Z_Construct_UPackage__Script_LostWorld(), TEXT("DeveloperSettingsAsStruct"), sizeof(FDeveloperSettingsAsStruct), Get_Z_Construct_UScriptStruct_FDeveloperSettingsAsStruct_Hash());
	}
	return Singleton;
}
template<> LOSTWORLD_API UScriptStruct* StaticStruct<FDeveloperSettingsAsStruct>()
{
	return FDeveloperSettingsAsStruct::StaticStruct();
}
static FCompiledInDeferStruct Z_CompiledInDeferStruct_UScriptStruct_FDeveloperSettingsAsStruct(FDeveloperSettingsAsStruct::StaticStruct, TEXT("/Script/LostWorld"), TEXT("DeveloperSettingsAsStruct"), false, nullptr, nullptr);
static struct FScriptStruct_LostWorld_StaticRegisterNativesFDeveloperSettingsAsStruct
{
	FScriptStruct_LostWorld_StaticRegisterNativesFDeveloperSettingsAsStruct()
	{
		UScriptStruct::DeferCppStructOps(FName(TEXT("DeveloperSettingsAsStruct")),new UScriptStruct::TCppStructOps<FDeveloperSettingsAsStruct>);
	}
} ScriptStruct_LostWorld_StaticRegisterNativesFDeveloperSettingsAsStruct;
	struct Z_Construct_UScriptStruct_FDeveloperSettingsAsStruct_Statics
	{
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Struct_MetaDataParams[];
#endif
		static void* NewStructOps();
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_GiveAllEntitiesTestDecks_MetaData[];
#endif
		static void NewProp_GiveAllEntitiesTestDecks_SetBit(void* Obj);
		static const UE4CodeGen_Private::FBoolPropertyParams NewProp_GiveAllEntitiesTestDecks;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_PrintMessageOnGameStart_MetaData[];
#endif
		static const UE4CodeGen_Private::FStrPropertyParams NewProp_PrintMessageOnGameStart;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_EnableDeveloperSettingsOverride_MetaData[];
#endif
		static void NewProp_EnableDeveloperSettingsOverride_SetBit(void* Obj);
		static const UE4CodeGen_Private::FBoolPropertyParams NewProp_EnableDeveloperSettingsOverride;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
		static const UE4CodeGen_Private::FStructParams ReturnStructParams;
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FDeveloperSettingsAsStruct_Statics::Struct_MetaDataParams[] = {
		{ "BlueprintType", "true" },
		{ "ModuleRelativePath", "SaveGameDeveloperSettings.h" },
	};
#endif
	void* Z_Construct_UScriptStruct_FDeveloperSettingsAsStruct_Statics::NewStructOps()
	{
		return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FDeveloperSettingsAsStruct>();
	}
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FDeveloperSettingsAsStruct_Statics::NewProp_GiveAllEntitiesTestDecks_MetaData[] = {
		{ "Category", "DeveloperSettingsAsStruct" },
		{ "ModuleRelativePath", "SaveGameDeveloperSettings.h" },
	};
#endif
	void Z_Construct_UScriptStruct_FDeveloperSettingsAsStruct_Statics::NewProp_GiveAllEntitiesTestDecks_SetBit(void* Obj)
	{
		((FDeveloperSettingsAsStruct*)Obj)->GiveAllEntitiesTestDecks = 1;
	}
	const UE4CodeGen_Private::FBoolPropertyParams Z_Construct_UScriptStruct_FDeveloperSettingsAsStruct_Statics::NewProp_GiveAllEntitiesTestDecks = { "GiveAllEntitiesTestDecks", nullptr, (EPropertyFlags)0x0010000000000005, UE4CodeGen_Private::EPropertyGenFlags::Bool | UE4CodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, 1, sizeof(bool), sizeof(FDeveloperSettingsAsStruct), &Z_Construct_UScriptStruct_FDeveloperSettingsAsStruct_Statics::NewProp_GiveAllEntitiesTestDecks_SetBit, METADATA_PARAMS(Z_Construct_UScriptStruct_FDeveloperSettingsAsStruct_Statics::NewProp_GiveAllEntitiesTestDecks_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FDeveloperSettingsAsStruct_Statics::NewProp_GiveAllEntitiesTestDecks_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FDeveloperSettingsAsStruct_Statics::NewProp_PrintMessageOnGameStart_MetaData[] = {
		{ "Category", "DeveloperSettingsAsStruct" },
		{ "ModuleRelativePath", "SaveGameDeveloperSettings.h" },
	};
#endif
	const UE4CodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FDeveloperSettingsAsStruct_Statics::NewProp_PrintMessageOnGameStart = { "PrintMessageOnGameStart", nullptr, (EPropertyFlags)0x0010000000000005, UE4CodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FDeveloperSettingsAsStruct, PrintMessageOnGameStart), METADATA_PARAMS(Z_Construct_UScriptStruct_FDeveloperSettingsAsStruct_Statics::NewProp_PrintMessageOnGameStart_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FDeveloperSettingsAsStruct_Statics::NewProp_PrintMessageOnGameStart_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FDeveloperSettingsAsStruct_Statics::NewProp_EnableDeveloperSettingsOverride_MetaData[] = {
		{ "Category", "DeveloperSettingsAsStruct" },
		{ "ModuleRelativePath", "SaveGameDeveloperSettings.h" },
	};
#endif
	void Z_Construct_UScriptStruct_FDeveloperSettingsAsStruct_Statics::NewProp_EnableDeveloperSettingsOverride_SetBit(void* Obj)
	{
		((FDeveloperSettingsAsStruct*)Obj)->EnableDeveloperSettingsOverride = 1;
	}
	const UE4CodeGen_Private::FBoolPropertyParams Z_Construct_UScriptStruct_FDeveloperSettingsAsStruct_Statics::NewProp_EnableDeveloperSettingsOverride = { "EnableDeveloperSettingsOverride", nullptr, (EPropertyFlags)0x0010000000000005, UE4CodeGen_Private::EPropertyGenFlags::Bool | UE4CodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, 1, sizeof(bool), sizeof(FDeveloperSettingsAsStruct), &Z_Construct_UScriptStruct_FDeveloperSettingsAsStruct_Statics::NewProp_EnableDeveloperSettingsOverride_SetBit, METADATA_PARAMS(Z_Construct_UScriptStruct_FDeveloperSettingsAsStruct_Statics::NewProp_EnableDeveloperSettingsOverride_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FDeveloperSettingsAsStruct_Statics::NewProp_EnableDeveloperSettingsOverride_MetaData)) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UScriptStruct_FDeveloperSettingsAsStruct_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FDeveloperSettingsAsStruct_Statics::NewProp_GiveAllEntitiesTestDecks,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FDeveloperSettingsAsStruct_Statics::NewProp_PrintMessageOnGameStart,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FDeveloperSettingsAsStruct_Statics::NewProp_EnableDeveloperSettingsOverride,
	};
	const UE4CodeGen_Private::FStructParams Z_Construct_UScriptStruct_FDeveloperSettingsAsStruct_Statics::ReturnStructParams = {
		(UObject* (*)())Z_Construct_UPackage__Script_LostWorld,
		nullptr,
		&NewStructOps,
		"DeveloperSettingsAsStruct",
		sizeof(FDeveloperSettingsAsStruct),
		alignof(FDeveloperSettingsAsStruct),
		Z_Construct_UScriptStruct_FDeveloperSettingsAsStruct_Statics::PropPointers,
		UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FDeveloperSettingsAsStruct_Statics::PropPointers),
		RF_Public|RF_Transient|RF_MarkAsNative,
		EStructFlags(0x00000201),
		METADATA_PARAMS(Z_Construct_UScriptStruct_FDeveloperSettingsAsStruct_Statics::Struct_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FDeveloperSettingsAsStruct_Statics::Struct_MetaDataParams))
	};
	UScriptStruct* Z_Construct_UScriptStruct_FDeveloperSettingsAsStruct()
	{
#if WITH_HOT_RELOAD
		extern uint32 Get_Z_Construct_UScriptStruct_FDeveloperSettingsAsStruct_Hash();
		UPackage* Outer = Z_Construct_UPackage__Script_LostWorld();
		static UScriptStruct* ReturnStruct = FindExistingStructIfHotReloadOrDynamic(Outer, TEXT("DeveloperSettingsAsStruct"), sizeof(FDeveloperSettingsAsStruct), Get_Z_Construct_UScriptStruct_FDeveloperSettingsAsStruct_Hash(), false);
#else
		static UScriptStruct* ReturnStruct = nullptr;
#endif
		if (!ReturnStruct)
		{
			UE4CodeGen_Private::ConstructUScriptStruct(ReturnStruct, Z_Construct_UScriptStruct_FDeveloperSettingsAsStruct_Statics::ReturnStructParams);
		}
		return ReturnStruct;
	}
	uint32 Get_Z_Construct_UScriptStruct_FDeveloperSettingsAsStruct_Hash() { return 2719999924U; }
	DEFINE_FUNCTION(USaveGameDeveloperSettings::execLoadDeveloperSettingsFromJson)
	{
		P_FINISH;
		P_NATIVE_BEGIN;
		P_THIS->LoadDeveloperSettingsFromJson();
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(USaveGameDeveloperSettings::execSaveDeveloperSettingsToJson)
	{
		P_FINISH;
		P_NATIVE_BEGIN;
		P_THIS->SaveDeveloperSettingsToJson();
		P_NATIVE_END;
	}
	void USaveGameDeveloperSettings::StaticRegisterNativesUSaveGameDeveloperSettings()
	{
		UClass* Class = USaveGameDeveloperSettings::StaticClass();
		static const FNameNativePtrPair Funcs[] = {
			{ "LoadDeveloperSettingsFromJson", &USaveGameDeveloperSettings::execLoadDeveloperSettingsFromJson },
			{ "SaveDeveloperSettingsToJson", &USaveGameDeveloperSettings::execSaveDeveloperSettingsToJson },
		};
		FNativeFunctionRegistrar::RegisterFunctions(Class, Funcs, UE_ARRAY_COUNT(Funcs));
	}
	struct Z_Construct_UFunction_USaveGameDeveloperSettings_LoadDeveloperSettingsFromJson_Statics
	{
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_USaveGameDeveloperSettings_LoadDeveloperSettingsFromJson_Statics::Function_MetaDataParams[] = {
		{ "ModuleRelativePath", "SaveGameDeveloperSettings.h" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_USaveGameDeveloperSettings_LoadDeveloperSettingsFromJson_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_USaveGameDeveloperSettings, nullptr, "LoadDeveloperSettingsFromJson", nullptr, nullptr, 0, nullptr, 0, RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_USaveGameDeveloperSettings_LoadDeveloperSettingsFromJson_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_USaveGameDeveloperSettings_LoadDeveloperSettingsFromJson_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_USaveGameDeveloperSettings_LoadDeveloperSettingsFromJson()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_USaveGameDeveloperSettings_LoadDeveloperSettingsFromJson_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_USaveGameDeveloperSettings_SaveDeveloperSettingsToJson_Statics
	{
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_USaveGameDeveloperSettings_SaveDeveloperSettingsToJson_Statics::Function_MetaDataParams[] = {
		{ "Comment", "// ---------------------------------------- Functions ---------------------------------------- //\n" },
		{ "ModuleRelativePath", "SaveGameDeveloperSettings.h" },
		{ "ToolTip", "---------------------------------------- Functions ----------------------------------------" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_USaveGameDeveloperSettings_SaveDeveloperSettingsToJson_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_USaveGameDeveloperSettings, nullptr, "SaveDeveloperSettingsToJson", nullptr, nullptr, 0, nullptr, 0, RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_USaveGameDeveloperSettings_SaveDeveloperSettingsToJson_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_USaveGameDeveloperSettings_SaveDeveloperSettingsToJson_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_USaveGameDeveloperSettings_SaveDeveloperSettingsToJson()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_USaveGameDeveloperSettings_SaveDeveloperSettingsToJson_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	UClass* Z_Construct_UClass_USaveGameDeveloperSettings_NoRegister()
	{
		return USaveGameDeveloperSettings::StaticClass();
	}
	struct Z_Construct_UClass_USaveGameDeveloperSettings_Statics
	{
		static UObject* (*const DependentSingletons[])();
		static const FClassFunctionLinkInfo FuncInfo[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_DeveloperSettingsAsStruct_MetaData[];
#endif
		static const UE4CodeGen_Private::FStructPropertyParams NewProp_DeveloperSettingsAsStruct;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UE4CodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_USaveGameDeveloperSettings_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_USaveGame,
		(UObject* (*)())Z_Construct_UPackage__Script_LostWorld,
	};
	const FClassFunctionLinkInfo Z_Construct_UClass_USaveGameDeveloperSettings_Statics::FuncInfo[] = {
		{ &Z_Construct_UFunction_USaveGameDeveloperSettings_LoadDeveloperSettingsFromJson, "LoadDeveloperSettingsFromJson" }, // 1744153989
		{ &Z_Construct_UFunction_USaveGameDeveloperSettings_SaveDeveloperSettingsToJson, "SaveDeveloperSettingsToJson" }, // 1961949690
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_USaveGameDeveloperSettings_Statics::Class_MetaDataParams[] = {
		{ "IncludePath", "SaveGameDeveloperSettings.h" },
		{ "ModuleRelativePath", "SaveGameDeveloperSettings.h" },
	};
#endif
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_USaveGameDeveloperSettings_Statics::NewProp_DeveloperSettingsAsStruct_MetaData[] = {
		{ "Category", "SaveGameDeveloperSettings" },
		{ "Comment", "// ---------------------------------------- Variables ---------------------------------------- //\n" },
		{ "ModuleRelativePath", "SaveGameDeveloperSettings.h" },
		{ "ToolTip", "---------------------------------------- Variables ----------------------------------------" },
	};
#endif
	const UE4CodeGen_Private::FStructPropertyParams Z_Construct_UClass_USaveGameDeveloperSettings_Statics::NewProp_DeveloperSettingsAsStruct = { "DeveloperSettingsAsStruct", nullptr, (EPropertyFlags)0x0010000000020015, UE4CodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(USaveGameDeveloperSettings, DeveloperSettingsAsStruct), Z_Construct_UScriptStruct_FDeveloperSettingsAsStruct, METADATA_PARAMS(Z_Construct_UClass_USaveGameDeveloperSettings_Statics::NewProp_DeveloperSettingsAsStruct_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_USaveGameDeveloperSettings_Statics::NewProp_DeveloperSettingsAsStruct_MetaData)) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_USaveGameDeveloperSettings_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_USaveGameDeveloperSettings_Statics::NewProp_DeveloperSettingsAsStruct,
	};
	const FCppClassTypeInfoStatic Z_Construct_UClass_USaveGameDeveloperSettings_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<USaveGameDeveloperSettings>::IsAbstract,
	};
	const UE4CodeGen_Private::FClassParams Z_Construct_UClass_USaveGameDeveloperSettings_Statics::ClassParams = {
		&USaveGameDeveloperSettings::StaticClass,
		nullptr,
		&StaticCppClassTypeInfo,
		DependentSingletons,
		FuncInfo,
		Z_Construct_UClass_USaveGameDeveloperSettings_Statics::PropPointers,
		nullptr,
		UE_ARRAY_COUNT(DependentSingletons),
		UE_ARRAY_COUNT(FuncInfo),
		UE_ARRAY_COUNT(Z_Construct_UClass_USaveGameDeveloperSettings_Statics::PropPointers),
		0,
		0x001000A0u,
		METADATA_PARAMS(Z_Construct_UClass_USaveGameDeveloperSettings_Statics::Class_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UClass_USaveGameDeveloperSettings_Statics::Class_MetaDataParams))
	};
	UClass* Z_Construct_UClass_USaveGameDeveloperSettings()
	{
		static UClass* OuterClass = nullptr;
		if (!OuterClass)
		{
			UE4CodeGen_Private::ConstructUClass(OuterClass, Z_Construct_UClass_USaveGameDeveloperSettings_Statics::ClassParams);
		}
		return OuterClass;
	}
	IMPLEMENT_CLASS(USaveGameDeveloperSettings, 3260949052);
	template<> LOSTWORLD_API UClass* StaticClass<USaveGameDeveloperSettings>()
	{
		return USaveGameDeveloperSettings::StaticClass();
	}
	static FCompiledInDefer Z_CompiledInDefer_UClass_USaveGameDeveloperSettings(Z_Construct_UClass_USaveGameDeveloperSettings, &USaveGameDeveloperSettings::StaticClass, TEXT("/Script/LostWorld"), TEXT("USaveGameDeveloperSettings"), false, nullptr, nullptr, nullptr);
	DEFINE_VTABLE_PTR_HELPER_CTOR(USaveGameDeveloperSettings);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
#ifdef _MSC_VER
#pragma warning (pop)
#endif
