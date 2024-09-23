// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "LostWorld/LostWorldGameInstanceBase.h"
#ifdef _MSC_VER
#pragma warning (push)
#pragma warning (disable : 4883)
#endif
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeLostWorldGameInstanceBase() {}
// Cross Module References
	LOSTWORLD_API UClass* Z_Construct_UClass_ULostWorldGameInstanceBase_NoRegister();
	LOSTWORLD_API UClass* Z_Construct_UClass_ULostWorldGameInstanceBase();
	ENGINE_API UClass* Z_Construct_UClass_UGameInstance();
	UPackage* Z_Construct_UPackage__Script_LostWorld();
	LOSTWORLD_API UClass* Z_Construct_UClass_USaveGameDeveloperSettings_NoRegister();
// End Cross Module References
	void ULostWorldGameInstanceBase::StaticRegisterNativesULostWorldGameInstanceBase()
	{
	}
	UClass* Z_Construct_UClass_ULostWorldGameInstanceBase_NoRegister()
	{
		return ULostWorldGameInstanceBase::StaticClass();
	}
	struct Z_Construct_UClass_ULostWorldGameInstanceBase_Statics
	{
		static UObject* (*const DependentSingletons[])();
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_DeveloperSettingsSaveGame_MetaData[];
#endif
		static const UE4CodeGen_Private::FObjectPropertyParams NewProp_DeveloperSettingsSaveGame;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UE4CodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_ULostWorldGameInstanceBase_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_UGameInstance,
		(UObject* (*)())Z_Construct_UPackage__Script_LostWorld,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_ULostWorldGameInstanceBase_Statics::Class_MetaDataParams[] = {
		{ "IncludePath", "LostWorldGameInstanceBase.h" },
		{ "ModuleRelativePath", "LostWorldGameInstanceBase.h" },
	};
#endif
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_ULostWorldGameInstanceBase_Statics::NewProp_DeveloperSettingsSaveGame_MetaData[] = {
		{ "Category", "LostWorldGameInstanceBase" },
		{ "Comment", "// ---------------------------------------- Variables ---------------------------------------- //\n" },
		{ "ModuleRelativePath", "LostWorldGameInstanceBase.h" },
		{ "ToolTip", "---------------------------------------- Variables ----------------------------------------" },
	};
#endif
	const UE4CodeGen_Private::FObjectPropertyParams Z_Construct_UClass_ULostWorldGameInstanceBase_Statics::NewProp_DeveloperSettingsSaveGame = { "DeveloperSettingsSaveGame", nullptr, (EPropertyFlags)0x0010000000020015, UE4CodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(ULostWorldGameInstanceBase, DeveloperSettingsSaveGame), Z_Construct_UClass_USaveGameDeveloperSettings_NoRegister, METADATA_PARAMS(Z_Construct_UClass_ULostWorldGameInstanceBase_Statics::NewProp_DeveloperSettingsSaveGame_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_ULostWorldGameInstanceBase_Statics::NewProp_DeveloperSettingsSaveGame_MetaData)) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_ULostWorldGameInstanceBase_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ULostWorldGameInstanceBase_Statics::NewProp_DeveloperSettingsSaveGame,
	};
	const FCppClassTypeInfoStatic Z_Construct_UClass_ULostWorldGameInstanceBase_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<ULostWorldGameInstanceBase>::IsAbstract,
	};
	const UE4CodeGen_Private::FClassParams Z_Construct_UClass_ULostWorldGameInstanceBase_Statics::ClassParams = {
		&ULostWorldGameInstanceBase::StaticClass,
		nullptr,
		&StaticCppClassTypeInfo,
		DependentSingletons,
		nullptr,
		Z_Construct_UClass_ULostWorldGameInstanceBase_Statics::PropPointers,
		nullptr,
		UE_ARRAY_COUNT(DependentSingletons),
		0,
		UE_ARRAY_COUNT(Z_Construct_UClass_ULostWorldGameInstanceBase_Statics::PropPointers),
		0,
		0x001000A8u,
		METADATA_PARAMS(Z_Construct_UClass_ULostWorldGameInstanceBase_Statics::Class_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UClass_ULostWorldGameInstanceBase_Statics::Class_MetaDataParams))
	};
	UClass* Z_Construct_UClass_ULostWorldGameInstanceBase()
	{
		static UClass* OuterClass = nullptr;
		if (!OuterClass)
		{
			UE4CodeGen_Private::ConstructUClass(OuterClass, Z_Construct_UClass_ULostWorldGameInstanceBase_Statics::ClassParams);
		}
		return OuterClass;
	}
	IMPLEMENT_CLASS(ULostWorldGameInstanceBase, 1444326802);
	template<> LOSTWORLD_API UClass* StaticClass<ULostWorldGameInstanceBase>()
	{
		return ULostWorldGameInstanceBase::StaticClass();
	}
	static FCompiledInDefer Z_CompiledInDefer_UClass_ULostWorldGameInstanceBase(Z_Construct_UClass_ULostWorldGameInstanceBase, &ULostWorldGameInstanceBase::StaticClass, TEXT("/Script/LostWorld"), TEXT("ULostWorldGameInstanceBase"), false, nullptr, nullptr, nullptr);
	DEFINE_VTABLE_PTR_HELPER_CTOR(ULostWorldGameInstanceBase);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
#ifdef _MSC_VER
#pragma warning (pop)
#endif
