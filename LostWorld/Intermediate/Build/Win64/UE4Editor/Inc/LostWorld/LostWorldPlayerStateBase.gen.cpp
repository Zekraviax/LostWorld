// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "LostWorld/LostWorldPlayerStateBase.h"
#ifdef _MSC_VER
#pragma warning (push)
#pragma warning (disable : 4883)
#endif
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeLostWorldPlayerStateBase() {}
// Cross Module References
	LOSTWORLD_API UClass* Z_Construct_UClass_ALostWorldPlayerStateBase_NoRegister();
	LOSTWORLD_API UClass* Z_Construct_UClass_ALostWorldPlayerStateBase();
	ENGINE_API UClass* Z_Construct_UClass_APlayerState();
	UPackage* Z_Construct_UPackage__Script_LostWorld();
// End Cross Module References
	void ALostWorldPlayerStateBase::StaticRegisterNativesALostWorldPlayerStateBase()
	{
	}
	UClass* Z_Construct_UClass_ALostWorldPlayerStateBase_NoRegister()
	{
		return ALostWorldPlayerStateBase::StaticClass();
	}
	struct Z_Construct_UClass_ALostWorldPlayerStateBase_Statics
	{
		static UObject* (*const DependentSingletons[])();
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UE4CodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_ALostWorldPlayerStateBase_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_APlayerState,
		(UObject* (*)())Z_Construct_UPackage__Script_LostWorld,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_ALostWorldPlayerStateBase_Statics::Class_MetaDataParams[] = {
		{ "HideCategories", "Input Movement Collision Rendering Utilities|Transformation" },
		{ "IncludePath", "LostWorldPlayerStateBase.h" },
		{ "ModuleRelativePath", "LostWorldPlayerStateBase.h" },
		{ "ShowCategories", "Input|MouseInput Input|TouchInput" },
	};
#endif
	const FCppClassTypeInfoStatic Z_Construct_UClass_ALostWorldPlayerStateBase_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<ALostWorldPlayerStateBase>::IsAbstract,
	};
	const UE4CodeGen_Private::FClassParams Z_Construct_UClass_ALostWorldPlayerStateBase_Statics::ClassParams = {
		&ALostWorldPlayerStateBase::StaticClass,
		"Engine",
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
		METADATA_PARAMS(Z_Construct_UClass_ALostWorldPlayerStateBase_Statics::Class_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UClass_ALostWorldPlayerStateBase_Statics::Class_MetaDataParams))
	};
	UClass* Z_Construct_UClass_ALostWorldPlayerStateBase()
	{
		static UClass* OuterClass = nullptr;
		if (!OuterClass)
		{
			UE4CodeGen_Private::ConstructUClass(OuterClass, Z_Construct_UClass_ALostWorldPlayerStateBase_Statics::ClassParams);
		}
		return OuterClass;
	}
	IMPLEMENT_CLASS(ALostWorldPlayerStateBase, 2629174076);
	template<> LOSTWORLD_API UClass* StaticClass<ALostWorldPlayerStateBase>()
	{
		return ALostWorldPlayerStateBase::StaticClass();
	}
	static FCompiledInDefer Z_CompiledInDefer_UClass_ALostWorldPlayerStateBase(Z_Construct_UClass_ALostWorldPlayerStateBase, &ALostWorldPlayerStateBase::StaticClass, TEXT("/Script/LostWorld"), TEXT("ALostWorldPlayerStateBase"), false, nullptr, nullptr, nullptr);
	DEFINE_VTABLE_PTR_HELPER_CTOR(ALostWorldPlayerStateBase);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
#ifdef _MSC_VER
#pragma warning (pop)
#endif
