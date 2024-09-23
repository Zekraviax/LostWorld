// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "LostWorld/LostWorldGameStateBase.h"
#ifdef _MSC_VER
#pragma warning (push)
#pragma warning (disable : 4883)
#endif
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeLostWorldGameStateBase() {}
// Cross Module References
	LOSTWORLD_API UClass* Z_Construct_UClass_ALostWorldGameStateBase_NoRegister();
	LOSTWORLD_API UClass* Z_Construct_UClass_ALostWorldGameStateBase();
	ENGINE_API UClass* Z_Construct_UClass_AGameStateBase();
	UPackage* Z_Construct_UPackage__Script_LostWorld();
// End Cross Module References
	void ALostWorldGameStateBase::StaticRegisterNativesALostWorldGameStateBase()
	{
	}
	UClass* Z_Construct_UClass_ALostWorldGameStateBase_NoRegister()
	{
		return ALostWorldGameStateBase::StaticClass();
	}
	struct Z_Construct_UClass_ALostWorldGameStateBase_Statics
	{
		static UObject* (*const DependentSingletons[])();
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UE4CodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_ALostWorldGameStateBase_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_AGameStateBase,
		(UObject* (*)())Z_Construct_UPackage__Script_LostWorld,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_ALostWorldGameStateBase_Statics::Class_MetaDataParams[] = {
		{ "HideCategories", "Input Movement Collision Rendering Utilities|Transformation" },
		{ "IncludePath", "LostWorldGameStateBase.h" },
		{ "ModuleRelativePath", "LostWorldGameStateBase.h" },
		{ "ShowCategories", "Input|MouseInput Input|TouchInput" },
	};
#endif
	const FCppClassTypeInfoStatic Z_Construct_UClass_ALostWorldGameStateBase_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<ALostWorldGameStateBase>::IsAbstract,
	};
	const UE4CodeGen_Private::FClassParams Z_Construct_UClass_ALostWorldGameStateBase_Statics::ClassParams = {
		&ALostWorldGameStateBase::StaticClass,
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
		0x009002A4u,
		METADATA_PARAMS(Z_Construct_UClass_ALostWorldGameStateBase_Statics::Class_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UClass_ALostWorldGameStateBase_Statics::Class_MetaDataParams))
	};
	UClass* Z_Construct_UClass_ALostWorldGameStateBase()
	{
		static UClass* OuterClass = nullptr;
		if (!OuterClass)
		{
			UE4CodeGen_Private::ConstructUClass(OuterClass, Z_Construct_UClass_ALostWorldGameStateBase_Statics::ClassParams);
		}
		return OuterClass;
	}
	IMPLEMENT_CLASS(ALostWorldGameStateBase, 2184530050);
	template<> LOSTWORLD_API UClass* StaticClass<ALostWorldGameStateBase>()
	{
		return ALostWorldGameStateBase::StaticClass();
	}
	static FCompiledInDefer Z_CompiledInDefer_UClass_ALostWorldGameStateBase(Z_Construct_UClass_ALostWorldGameStateBase, &ALostWorldGameStateBase::StaticClass, TEXT("/Script/LostWorld"), TEXT("ALostWorldGameStateBase"), false, nullptr, nullptr, nullptr);
	DEFINE_VTABLE_PTR_HELPER_CTOR(ALostWorldGameStateBase);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
#ifdef _MSC_VER
#pragma warning (pop)
#endif
