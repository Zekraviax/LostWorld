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
// End Cross Module References
	void ALostWorldGameModeBattle::StaticRegisterNativesALostWorldGameModeBattle()
	{
	}
	UClass* Z_Construct_UClass_ALostWorldGameModeBattle_NoRegister()
	{
		return ALostWorldGameModeBattle::StaticClass();
	}
	struct Z_Construct_UClass_ALostWorldGameModeBattle_Statics
	{
		static UObject* (*const DependentSingletons[])();
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UE4CodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_ALostWorldGameModeBattle_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_ALostWorldGameModeBase,
		(UObject* (*)())Z_Construct_UPackage__Script_LostWorld,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_ALostWorldGameModeBattle_Statics::Class_MetaDataParams[] = {
		{ "HideCategories", "Info Rendering MovementReplication Replication Actor Input Movement Collision Rendering Utilities|Transformation" },
		{ "IncludePath", "LostWorldGameModeBattle.h" },
		{ "ModuleRelativePath", "LostWorldGameModeBattle.h" },
		{ "ShowCategories", "Input|MouseInput Input|TouchInput" },
	};
#endif
	const FCppClassTypeInfoStatic Z_Construct_UClass_ALostWorldGameModeBattle_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<ALostWorldGameModeBattle>::IsAbstract,
	};
	const UE4CodeGen_Private::FClassParams Z_Construct_UClass_ALostWorldGameModeBattle_Statics::ClassParams = {
		&ALostWorldGameModeBattle::StaticClass,
		"Game",
		&StaticCppClassTypeInfo,
		DependentSingletons,
		nullptr,
		nullptr,
		nullptr,
		UE_ARRAY_COUNT(DependentSingletons),
		0,
		0,
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
	IMPLEMENT_CLASS(ALostWorldGameModeBattle, 4159436506);
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
