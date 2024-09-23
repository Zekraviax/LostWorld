// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "LostWorld/ActorEntity.h"
#ifdef _MSC_VER
#pragma warning (push)
#pragma warning (disable : 4883)
#endif
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeActorEntity() {}
// Cross Module References
	LOSTWORLD_API UClass* Z_Construct_UClass_AActorEntity_NoRegister();
	LOSTWORLD_API UClass* Z_Construct_UClass_AActorEntity();
	ENGINE_API UClass* Z_Construct_UClass_AActor();
	UPackage* Z_Construct_UPackage__Script_LostWorld();
	LOSTWORLD_API UScriptStruct* Z_Construct_UScriptStruct_FCard();
// End Cross Module References
	void AActorEntity::StaticRegisterNativesAActorEntity()
	{
	}
	UClass* Z_Construct_UClass_AActorEntity_NoRegister()
	{
		return AActorEntity::StaticClass();
	}
	struct Z_Construct_UClass_AActorEntity_Statics
	{
		static UObject* (*const DependentSingletons[])();
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_Deck_MetaData[];
#endif
		static const UE4CodeGen_Private::FArrayPropertyParams NewProp_Deck;
		static const UE4CodeGen_Private::FStructPropertyParams NewProp_Deck_Inner;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UE4CodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_AActorEntity_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_AActor,
		(UObject* (*)())Z_Construct_UPackage__Script_LostWorld,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AActorEntity_Statics::Class_MetaDataParams[] = {
		{ "IncludePath", "ActorEntity.h" },
		{ "ModuleRelativePath", "ActorEntity.h" },
	};
#endif
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AActorEntity_Statics::NewProp_Deck_MetaData[] = {
		{ "Comment", "// -------------------------------- Cards & Deck\n" },
		{ "ModuleRelativePath", "ActorEntity.h" },
		{ "ToolTip", "-------------------------------- Cards & Deck" },
	};
#endif
	const UE4CodeGen_Private::FArrayPropertyParams Z_Construct_UClass_AActorEntity_Statics::NewProp_Deck = { "Deck", nullptr, (EPropertyFlags)0x0010000000000000, UE4CodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(AActorEntity, Deck), EArrayPropertyFlags::None, METADATA_PARAMS(Z_Construct_UClass_AActorEntity_Statics::NewProp_Deck_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_AActorEntity_Statics::NewProp_Deck_MetaData)) };
	const UE4CodeGen_Private::FStructPropertyParams Z_Construct_UClass_AActorEntity_Statics::NewProp_Deck_Inner = { "Deck", nullptr, (EPropertyFlags)0x0000000000000000, UE4CodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, 0, Z_Construct_UScriptStruct_FCard, METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_AActorEntity_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AActorEntity_Statics::NewProp_Deck,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AActorEntity_Statics::NewProp_Deck_Inner,
	};
	const FCppClassTypeInfoStatic Z_Construct_UClass_AActorEntity_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<AActorEntity>::IsAbstract,
	};
	const UE4CodeGen_Private::FClassParams Z_Construct_UClass_AActorEntity_Statics::ClassParams = {
		&AActorEntity::StaticClass,
		"Engine",
		&StaticCppClassTypeInfo,
		DependentSingletons,
		nullptr,
		Z_Construct_UClass_AActorEntity_Statics::PropPointers,
		nullptr,
		UE_ARRAY_COUNT(DependentSingletons),
		0,
		UE_ARRAY_COUNT(Z_Construct_UClass_AActorEntity_Statics::PropPointers),
		0,
		0x009000A4u,
		METADATA_PARAMS(Z_Construct_UClass_AActorEntity_Statics::Class_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UClass_AActorEntity_Statics::Class_MetaDataParams))
	};
	UClass* Z_Construct_UClass_AActorEntity()
	{
		static UClass* OuterClass = nullptr;
		if (!OuterClass)
		{
			UE4CodeGen_Private::ConstructUClass(OuterClass, Z_Construct_UClass_AActorEntity_Statics::ClassParams);
		}
		return OuterClass;
	}
	IMPLEMENT_CLASS(AActorEntity, 501581739);
	template<> LOSTWORLD_API UClass* StaticClass<AActorEntity>()
	{
		return AActorEntity::StaticClass();
	}
	static FCompiledInDefer Z_CompiledInDefer_UClass_AActorEntity(Z_Construct_UClass_AActorEntity, &AActorEntity::StaticClass, TEXT("/Script/LostWorld"), TEXT("AActorEntity"), false, nullptr, nullptr, nullptr);
	DEFINE_VTABLE_PTR_HELPER_CTOR(AActorEntity);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
#ifdef _MSC_VER
#pragma warning (pop)
#endif
