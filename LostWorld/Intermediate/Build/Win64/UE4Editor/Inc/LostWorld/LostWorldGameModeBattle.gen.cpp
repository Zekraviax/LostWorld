// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "LostWorld/LostWorldGameModeBattle.h"
#ifdef _MSC_VER
#pragma warning (push)
#pragma warning (disable : 4883)
#endif
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeLostWorldGameModeBattle() {}
// Cross Module References
	LOSTWORLD_API UClass* Z_Construct_UClass_ALostWorldGameModeBattle_NoRegister();
	LOSTWORLD_API UClass* Z_Construct_UClass_ALostWorldGameModeBattle();
	LOSTWORLD_API UClass* Z_Construct_UClass_ALostWorldGameModeBase();
	UPackage* Z_Construct_UPackage__Script_LostWorld();
	LOSTWORLD_API UClass* Z_Construct_UClass_USaveGameLevelData_NoRegister();
// End Cross Module References
	DEFINE_FUNCTION(ALostWorldGameModeBattle::execLoadLevelData)
	{
		P_FINISH;
		P_NATIVE_BEGIN;
		P_THIS->LoadLevelData();
		P_NATIVE_END;
	}
	void ALostWorldGameModeBattle::StaticRegisterNativesALostWorldGameModeBattle()
	{
		UClass* Class = ALostWorldGameModeBattle::StaticClass();
		static const FNameNativePtrPair Funcs[] = {
			{ "LoadLevelData", &ALostWorldGameModeBattle::execLoadLevelData },
		};
		FNativeFunctionRegistrar::RegisterFunctions(Class, Funcs, UE_ARRAY_COUNT(Funcs));
	}
	struct Z_Construct_UFunction_ALostWorldGameModeBattle_LoadLevelData_Statics
	{
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_ALostWorldGameModeBattle_LoadLevelData_Statics::Function_MetaDataParams[] = {
		{ "Comment", "// Level Generation:\n// First, the game mode needs to know the dimensions of a level in Tiles.\n// The north-south dimension will be called 'Length' and 'X'.\n// The east-west dimension will be called 'Width' and 'Y'.\n" },
		{ "ModuleRelativePath", "LostWorldGameModeBattle.h" },
		{ "ToolTip", "Level Generation:\nFirst, the game mode needs to know the dimensions of a level in Tiles.\nThe north-south dimension will be called 'Length' and 'X'.\nThe east-west dimension will be called 'Width' and 'Y'." },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_ALostWorldGameModeBattle_LoadLevelData_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_ALostWorldGameModeBattle, nullptr, "LoadLevelData", nullptr, nullptr, 0, nullptr, 0, RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_ALostWorldGameModeBattle_LoadLevelData_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_ALostWorldGameModeBattle_LoadLevelData_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_ALostWorldGameModeBattle_LoadLevelData()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_ALostWorldGameModeBattle_LoadLevelData_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	UClass* Z_Construct_UClass_ALostWorldGameModeBattle_NoRegister()
	{
		return ALostWorldGameModeBattle::StaticClass();
	}
	struct Z_Construct_UClass_ALostWorldGameModeBattle_Statics
	{
		static UObject* (*const DependentSingletons[])();
		static const FClassFunctionLinkInfo FuncInfo[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_LevelDataSaveGameReference_MetaData[];
#endif
		static const UE4CodeGen_Private::FObjectPropertyParams NewProp_LevelDataSaveGameReference;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UE4CodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_ALostWorldGameModeBattle_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_ALostWorldGameModeBase,
		(UObject* (*)())Z_Construct_UPackage__Script_LostWorld,
	};
	const FClassFunctionLinkInfo Z_Construct_UClass_ALostWorldGameModeBattle_Statics::FuncInfo[] = {
		{ &Z_Construct_UFunction_ALostWorldGameModeBattle_LoadLevelData, "LoadLevelData" }, // 1983712915
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_ALostWorldGameModeBattle_Statics::Class_MetaDataParams[] = {
		{ "HideCategories", "Info Rendering MovementReplication Replication Actor Input Movement Collision Rendering Utilities|Transformation" },
		{ "IncludePath", "LostWorldGameModeBattle.h" },
		{ "ModuleRelativePath", "LostWorldGameModeBattle.h" },
		{ "ShowCategories", "Input|MouseInput Input|TouchInput" },
	};
#endif
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_ALostWorldGameModeBattle_Statics::NewProp_LevelDataSaveGameReference_MetaData[] = {
		{ "Category", "LostWorldGameModeBattle" },
		{ "Comment", "// ---------------------------------------- Variables ---------------------------------------- //\n" },
		{ "ModuleRelativePath", "LostWorldGameModeBattle.h" },
		{ "ToolTip", "---------------------------------------- Variables ----------------------------------------" },
	};
#endif
	const UE4CodeGen_Private::FObjectPropertyParams Z_Construct_UClass_ALostWorldGameModeBattle_Statics::NewProp_LevelDataSaveGameReference = { "LevelDataSaveGameReference", nullptr, (EPropertyFlags)0x0010000000020015, UE4CodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(ALostWorldGameModeBattle, LevelDataSaveGameReference), Z_Construct_UClass_USaveGameLevelData_NoRegister, METADATA_PARAMS(Z_Construct_UClass_ALostWorldGameModeBattle_Statics::NewProp_LevelDataSaveGameReference_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_ALostWorldGameModeBattle_Statics::NewProp_LevelDataSaveGameReference_MetaData)) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_ALostWorldGameModeBattle_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ALostWorldGameModeBattle_Statics::NewProp_LevelDataSaveGameReference,
	};
	const FCppClassTypeInfoStatic Z_Construct_UClass_ALostWorldGameModeBattle_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<ALostWorldGameModeBattle>::IsAbstract,
	};
	const UE4CodeGen_Private::FClassParams Z_Construct_UClass_ALostWorldGameModeBattle_Statics::ClassParams = {
		&ALostWorldGameModeBattle::StaticClass,
		"Game",
		&StaticCppClassTypeInfo,
		DependentSingletons,
		FuncInfo,
		Z_Construct_UClass_ALostWorldGameModeBattle_Statics::PropPointers,
		nullptr,
		UE_ARRAY_COUNT(DependentSingletons),
		UE_ARRAY_COUNT(FuncInfo),
		UE_ARRAY_COUNT(Z_Construct_UClass_ALostWorldGameModeBattle_Statics::PropPointers),
		0,
		0x009002ACu,
		METADATA_PARAMS(Z_Construct_UClass_ALostWorldGameModeBattle_Statics::Class_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UClass_ALostWorldGameModeBattle_Statics::Class_MetaDataParams))
	};
	UClass* Z_Construct_UClass_ALostWorldGameModeBattle()
	{
		static UClass* OuterClass = nullptr;
		if (!OuterClass)
		{
			UE4CodeGen_Private::ConstructUClass(OuterClass, Z_Construct_UClass_ALostWorldGameModeBattle_Statics::ClassParams);
		}
		return OuterClass;
	}
	IMPLEMENT_CLASS(ALostWorldGameModeBattle, 1059373796);
	template<> LOSTWORLD_API UClass* StaticClass<ALostWorldGameModeBattle>()
	{
		return ALostWorldGameModeBattle::StaticClass();
	}
	static FCompiledInDefer Z_CompiledInDefer_UClass_ALostWorldGameModeBattle(Z_Construct_UClass_ALostWorldGameModeBattle, &ALostWorldGameModeBattle::StaticClass, TEXT("/Script/LostWorld"), TEXT("ALostWorldGameModeBattle"), false, nullptr, nullptr, nullptr);
	DEFINE_VTABLE_PTR_HELPER_CTOR(ALostWorldGameModeBattle);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
#ifdef _MSC_VER
#pragma warning (pop)
#endif
