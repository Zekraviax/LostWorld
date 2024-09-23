// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "LostWorld/ActorGridTile.h"
#ifdef _MSC_VER
#pragma warning (push)
#pragma warning (disable : 4883)
#endif
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeActorGridTile() {}
// Cross Module References
	LOSTWORLD_API UClass* Z_Construct_UClass_AActorGridTile_NoRegister();
	LOSTWORLD_API UClass* Z_Construct_UClass_AActorGridTile();
	ENGINE_API UClass* Z_Construct_UClass_AActor();
	UPackage* Z_Construct_UPackage__Script_LostWorld();
// End Cross Module References
	void AActorGridTile::StaticRegisterNativesAActorGridTile()
	{
	}
	UClass* Z_Construct_UClass_AActorGridTile_NoRegister()
	{
		return AActorGridTile::StaticClass();
	}
	struct Z_Construct_UClass_AActorGridTile_Statics
	{
		static UObject* (*const DependentSingletons[])();
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UE4CodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_AActorGridTile_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_AActor,
		(UObject* (*)())Z_Construct_UPackage__Script_LostWorld,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AActorGridTile_Statics::Class_MetaDataParams[] = {
		{ "IncludePath", "ActorGridTile.h" },
		{ "ModuleRelativePath", "ActorGridTile.h" },
	};
#endif
	const FCppClassTypeInfoStatic Z_Construct_UClass_AActorGridTile_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<AActorGridTile>::IsAbstract,
	};
	const UE4CodeGen_Private::FClassParams Z_Construct_UClass_AActorGridTile_Statics::ClassParams = {
		&AActorGridTile::StaticClass,
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
		0x009000A4u,
		METADATA_PARAMS(Z_Construct_UClass_AActorGridTile_Statics::Class_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UClass_AActorGridTile_Statics::Class_MetaDataParams))
	};
	UClass* Z_Construct_UClass_AActorGridTile()
	{
		static UClass* OuterClass = nullptr;
		if (!OuterClass)
		{
			UE4CodeGen_Private::ConstructUClass(OuterClass, Z_Construct_UClass_AActorGridTile_Statics::ClassParams);
		}
		return OuterClass;
	}
	IMPLEMENT_CLASS(AActorGridTile, 371416068);
	template<> LOSTWORLD_API UClass* StaticClass<AActorGridTile>()
	{
		return AActorGridTile::StaticClass();
	}
	static FCompiledInDefer Z_CompiledInDefer_UClass_AActorGridTile(Z_Construct_UClass_AActorGridTile, &AActorGridTile::StaticClass, TEXT("/Script/LostWorld"), TEXT("AActorGridTile"), false, nullptr, nullptr, nullptr);
	DEFINE_VTABLE_PTR_HELPER_CTOR(AActorGridTile);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
#ifdef _MSC_VER
#pragma warning (pop)
#endif
