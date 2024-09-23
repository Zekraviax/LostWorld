// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "LostWorld/LostWorldGameModeBase.h"
#ifdef _MSC_VER
#pragma warning (push)
#pragma warning (disable : 4883)
#endif
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeLostWorldGameModeBase() {}
// Cross Module References
	LOSTWORLD_API UClass* Z_Construct_UClass_ALostWorldGameModeBase_NoRegister();
	LOSTWORLD_API UClass* Z_Construct_UClass_ALostWorldGameModeBase();
	ENGINE_API UClass* Z_Construct_UClass_AGameModeBase();
	UPackage* Z_Construct_UPackage__Script_LostWorld();
// End Cross Module References
	void ALostWorldGameModeBase::StaticRegisterNativesALostWorldGameModeBase()
	{
	}
	UClass* Z_Construct_UClass_ALostWorldGameModeBase_NoRegister()
	{
		return ALostWorldGameModeBase::StaticClass();
	}
	struct Z_Construct_UClass_ALostWorldGameModeBase_Statics
	{
		static UObject* (*const DependentSingletons[])();
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UE4CodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_ALostWorldGameModeBase_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_AGameModeBase,
		(UObject* (*)())Z_Construct_UPackage__Script_LostWorld,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_ALostWorldGameModeBase_Statics::Class_MetaDataParams[] = {
		{ "HideCategories", "Info Rendering MovementReplication Replication Actor Input Movement Collision Rendering Utilities|Transformation" },
		{ "IncludePath", "LostWorldGameModeBase.h" },
		{ "ModuleRelativePath", "LostWorldGameModeBase.h" },
		{ "ShowCategories", "Input|MouseInput Input|TouchInput" },
	};
#endif
	const FCppClassTypeInfoStatic Z_Construct_UClass_ALostWorldGameModeBase_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<ALostWorldGameModeBase>::IsAbstract,
	};
	const UE4CodeGen_Private::FClassParams Z_Construct_UClass_ALostWorldGameModeBase_Statics::ClassParams = {
		&ALostWorldGameModeBase::StaticClass,
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
		METADATA_PARAMS(Z_Construct_UClass_ALostWorldGameModeBase_Statics::Class_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UClass_ALostWorldGameModeBase_Statics::Class_MetaDataParams))
	};
	UClass* Z_Construct_UClass_ALostWorldGameModeBase()
	{
		static UClass* OuterClass = nullptr;
		if (!OuterClass)
		{
			UE4CodeGen_Private::ConstructUClass(OuterClass, Z_Construct_UClass_ALostWorldGameModeBase_Statics::ClassParams);
		}
		return OuterClass;
	}
	IMPLEMENT_CLASS(ALostWorldGameModeBase, 4165569558);
	template<> LOSTWORLD_API UClass* StaticClass<ALostWorldGameModeBase>()
	{
		return ALostWorldGameModeBase::StaticClass();
	}
	static FCompiledInDefer Z_CompiledInDefer_UClass_ALostWorldGameModeBase(Z_Construct_UClass_ALostWorldGameModeBase, &ALostWorldGameModeBase::StaticClass, TEXT("/Script/LostWorld"), TEXT("ALostWorldGameModeBase"), false, nullptr, nullptr, nullptr);
	DEFINE_VTABLE_PTR_HELPER_CTOR(ALostWorldGameModeBase);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
#ifdef _MSC_VER
#pragma warning (pop)
#endif
