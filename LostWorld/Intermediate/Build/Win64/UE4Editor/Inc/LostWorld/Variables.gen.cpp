// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "LostWorld/Variables.h"
#ifdef _MSC_VER
#pragma warning (push)
#pragma warning (disable : 4883)
#endif
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeVariables() {}
// Cross Module References
	LOSTWORLD_API UEnum* Z_Construct_UEnum_LostWorld_ECardTypes();
	UPackage* Z_Construct_UPackage__Script_LostWorld();
	LOSTWORLD_API UScriptStruct* Z_Construct_UScriptStruct_FCard();
	LOSTWORLD_API UScriptStruct* Z_Construct_UScriptStruct_FEntityBaseStats();
	LOSTWORLD_API UScriptStruct* Z_Construct_UScriptStruct_FRoomDataAsStruct();
	LOSTWORLD_API UScriptStruct* Z_Construct_UScriptStruct_FFloorDataAsStruct();
	LOSTWORLD_API UScriptStruct* Z_Construct_UScriptStruct_FLevelDataAsStruct();
// End Cross Module References
	static UEnum* ECardTypes_StaticEnum()
	{
		static UEnum* Singleton = nullptr;
		if (!Singleton)
		{
			Singleton = GetStaticEnum(Z_Construct_UEnum_LostWorld_ECardTypes, Z_Construct_UPackage__Script_LostWorld(), TEXT("ECardTypes"));
		}
		return Singleton;
	}
	template<> LOSTWORLD_API UEnum* StaticEnum<ECardTypes>()
	{
		return ECardTypes_StaticEnum();
	}
	static FCompiledInDeferEnum Z_CompiledInDeferEnum_UEnum_ECardTypes(ECardTypes_StaticEnum, TEXT("/Script/LostWorld"), TEXT("ECardTypes"), false, nullptr, nullptr);
	uint32 Get_Z_Construct_UEnum_LostWorld_ECardTypes_Hash() { return 316237134U; }
	UEnum* Z_Construct_UEnum_LostWorld_ECardTypes()
	{
#if WITH_HOT_RELOAD
		UPackage* Outer = Z_Construct_UPackage__Script_LostWorld();
		static UEnum* ReturnEnum = FindExistingEnumIfHotReloadOrDynamic(Outer, TEXT("ECardTypes"), 0, Get_Z_Construct_UEnum_LostWorld_ECardTypes_Hash(), false);
#else
		static UEnum* ReturnEnum = nullptr;
#endif // WITH_HOT_RELOAD
		if (!ReturnEnum)
		{
			static const UE4CodeGen_Private::FEnumeratorParam Enumerators[] = {
				{ "ECardTypes::Spell", (int64)ECardTypes::Spell },
				{ "ECardTypes::Summon", (int64)ECardTypes::Summon },
				{ "ECardTypes::Technique", (int64)ECardTypes::Technique },
				{ "ECardTypes::Command", (int64)ECardTypes::Command },
				{ "ECardTypes::Shout", (int64)ECardTypes::Shout },
			};
#if WITH_METADATA
			const UE4CodeGen_Private::FMetaDataPairParam Enum_MetaDataParams[] = {
				{ "BlueprintType", "true" },
				{ "Command.Name", "ECardTypes::Command" },
				{ "Comment", "// -------------------------------- Cards\n" },
				{ "ModuleRelativePath", "Variables.h" },
				{ "Shout.Name", "ECardTypes::Shout" },
				{ "Spell.Name", "ECardTypes::Spell" },
				{ "Summon.Name", "ECardTypes::Summon" },
				{ "Technique.Name", "ECardTypes::Technique" },
				{ "ToolTip", "-------------------------------- Cards" },
			};
#endif
			static const UE4CodeGen_Private::FEnumParams EnumParams = {
				(UObject*(*)())Z_Construct_UPackage__Script_LostWorld,
				nullptr,
				"ECardTypes",
				"ECardTypes",
				Enumerators,
				UE_ARRAY_COUNT(Enumerators),
				RF_Public|RF_Transient|RF_MarkAsNative,
				UE4CodeGen_Private::EDynamicType::NotDynamic,
				(uint8)UEnum::ECppForm::EnumClass,
				METADATA_PARAMS(Enum_MetaDataParams, UE_ARRAY_COUNT(Enum_MetaDataParams))
			};
			UE4CodeGen_Private::ConstructUEnum(ReturnEnum, EnumParams);
		}
		return ReturnEnum;
	}
class UScriptStruct* FCard::StaticStruct()
{
	static class UScriptStruct* Singleton = NULL;
	if (!Singleton)
	{
		extern LOSTWORLD_API uint32 Get_Z_Construct_UScriptStruct_FCard_Hash();
		Singleton = GetStaticStruct(Z_Construct_UScriptStruct_FCard, Z_Construct_UPackage__Script_LostWorld(), TEXT("Card"), sizeof(FCard), Get_Z_Construct_UScriptStruct_FCard_Hash());
	}
	return Singleton;
}
template<> LOSTWORLD_API UScriptStruct* StaticStruct<FCard>()
{
	return FCard::StaticStruct();
}
static FCompiledInDeferStruct Z_CompiledInDeferStruct_UScriptStruct_FCard(FCard::StaticStruct, TEXT("/Script/LostWorld"), TEXT("Card"), false, nullptr, nullptr);
static struct FScriptStruct_LostWorld_StaticRegisterNativesFCard
{
	FScriptStruct_LostWorld_StaticRegisterNativesFCard()
	{
		UScriptStruct::DeferCppStructOps(FName(TEXT("Card")),new UScriptStruct::TCppStructOps<FCard>);
	}
} ScriptStruct_LostWorld_StaticRegisterNativesFCard;
	struct Z_Construct_UScriptStruct_FCard_Statics
	{
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Struct_MetaDataParams[];
#endif
		static void* NewStructOps();
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_CalculatedCost_MetaData[];
#endif
		static const UE4CodeGen_Private::FUnsizedIntPropertyParams NewProp_CalculatedCost;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_CardTypes_MetaData[];
#endif
		static const UE4CodeGen_Private::FArrayPropertyParams NewProp_CardTypes;
		static const UE4CodeGen_Private::FEnumPropertyParams NewProp_CardTypes_Inner;
		static const UE4CodeGen_Private::FBytePropertyParams NewProp_CardTypes_Inner_Underlying;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_BaseCost_MetaData[];
#endif
		static const UE4CodeGen_Private::FUnsizedIntPropertyParams NewProp_BaseCost;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_DisplayName_MetaData[];
#endif
		static const UE4CodeGen_Private::FStrPropertyParams NewProp_DisplayName;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
		static const UE4CodeGen_Private::FStructParams ReturnStructParams;
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FCard_Statics::Struct_MetaDataParams[] = {
		{ "BlueprintType", "true" },
		{ "Comment", "// -------------------------------- Cards\n" },
		{ "ModuleRelativePath", "Variables.h" },
		{ "ToolTip", "-------------------------------- Cards" },
	};
#endif
	void* Z_Construct_UScriptStruct_FCard_Statics::NewStructOps()
	{
		return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FCard>();
	}
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FCard_Statics::NewProp_CalculatedCost_MetaData[] = {
		{ "Category", "Calculated" },
		{ "Comment", "// Should be added to the array in the order that they're written on the card.\n" },
		{ "ModuleRelativePath", "Variables.h" },
		{ "ToolTip", "Should be added to the array in the order that they're written on the card." },
	};
#endif
	const UE4CodeGen_Private::FUnsizedIntPropertyParams Z_Construct_UScriptStruct_FCard_Statics::NewProp_CalculatedCost = { "CalculatedCost", nullptr, (EPropertyFlags)0x0010000000000005, UE4CodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FCard, CalculatedCost), METADATA_PARAMS(Z_Construct_UScriptStruct_FCard_Statics::NewProp_CalculatedCost_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FCard_Statics::NewProp_CalculatedCost_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FCard_Statics::NewProp_CardTypes_MetaData[] = {
		{ "Category", "Base" },
		{ "Comment", "// Use a different variable for the total cost (after any changes to the base cost)\n" },
		{ "ModuleRelativePath", "Variables.h" },
		{ "ToolTip", "Use a different variable for the total cost (after any changes to the base cost)" },
	};
#endif
	const UE4CodeGen_Private::FArrayPropertyParams Z_Construct_UScriptStruct_FCard_Statics::NewProp_CardTypes = { "CardTypes", nullptr, (EPropertyFlags)0x0010000000000005, UE4CodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FCard, CardTypes), EArrayPropertyFlags::None, METADATA_PARAMS(Z_Construct_UScriptStruct_FCard_Statics::NewProp_CardTypes_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FCard_Statics::NewProp_CardTypes_MetaData)) };
	const UE4CodeGen_Private::FEnumPropertyParams Z_Construct_UScriptStruct_FCard_Statics::NewProp_CardTypes_Inner = { "CardTypes", nullptr, (EPropertyFlags)0x0000000000000000, UE4CodeGen_Private::EPropertyGenFlags::Enum, RF_Public|RF_Transient|RF_MarkAsNative, 1, 0, Z_Construct_UEnum_LostWorld_ECardTypes, METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FBytePropertyParams Z_Construct_UScriptStruct_FCard_Statics::NewProp_CardTypes_Inner_Underlying = { "UnderlyingType", nullptr, (EPropertyFlags)0x0000000000000000, UE4CodeGen_Private::EPropertyGenFlags::Byte, RF_Public|RF_Transient|RF_MarkAsNative, 1, 0, nullptr, METADATA_PARAMS(nullptr, 0) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FCard_Statics::NewProp_BaseCost_MetaData[] = {
		{ "Category", "Base" },
		{ "ModuleRelativePath", "Variables.h" },
	};
#endif
	const UE4CodeGen_Private::FUnsizedIntPropertyParams Z_Construct_UScriptStruct_FCard_Statics::NewProp_BaseCost = { "BaseCost", nullptr, (EPropertyFlags)0x0010000000000005, UE4CodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FCard, BaseCost), METADATA_PARAMS(Z_Construct_UScriptStruct_FCard_Statics::NewProp_BaseCost_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FCard_Statics::NewProp_BaseCost_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FCard_Statics::NewProp_DisplayName_MetaData[] = {
		{ "Category", "Base" },
		{ "ModuleRelativePath", "Variables.h" },
	};
#endif
	const UE4CodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FCard_Statics::NewProp_DisplayName = { "DisplayName", nullptr, (EPropertyFlags)0x0010000000000005, UE4CodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FCard, DisplayName), METADATA_PARAMS(Z_Construct_UScriptStruct_FCard_Statics::NewProp_DisplayName_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FCard_Statics::NewProp_DisplayName_MetaData)) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UScriptStruct_FCard_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FCard_Statics::NewProp_CalculatedCost,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FCard_Statics::NewProp_CardTypes,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FCard_Statics::NewProp_CardTypes_Inner,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FCard_Statics::NewProp_CardTypes_Inner_Underlying,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FCard_Statics::NewProp_BaseCost,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FCard_Statics::NewProp_DisplayName,
	};
	const UE4CodeGen_Private::FStructParams Z_Construct_UScriptStruct_FCard_Statics::ReturnStructParams = {
		(UObject* (*)())Z_Construct_UPackage__Script_LostWorld,
		nullptr,
		&NewStructOps,
		"Card",
		sizeof(FCard),
		alignof(FCard),
		Z_Construct_UScriptStruct_FCard_Statics::PropPointers,
		UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FCard_Statics::PropPointers),
		RF_Public|RF_Transient|RF_MarkAsNative,
		EStructFlags(0x00000201),
		METADATA_PARAMS(Z_Construct_UScriptStruct_FCard_Statics::Struct_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FCard_Statics::Struct_MetaDataParams))
	};
	UScriptStruct* Z_Construct_UScriptStruct_FCard()
	{
#if WITH_HOT_RELOAD
		extern uint32 Get_Z_Construct_UScriptStruct_FCard_Hash();
		UPackage* Outer = Z_Construct_UPackage__Script_LostWorld();
		static UScriptStruct* ReturnStruct = FindExistingStructIfHotReloadOrDynamic(Outer, TEXT("Card"), sizeof(FCard), Get_Z_Construct_UScriptStruct_FCard_Hash(), false);
#else
		static UScriptStruct* ReturnStruct = nullptr;
#endif
		if (!ReturnStruct)
		{
			UE4CodeGen_Private::ConstructUScriptStruct(ReturnStruct, Z_Construct_UScriptStruct_FCard_Statics::ReturnStructParams);
		}
		return ReturnStruct;
	}
	uint32 Get_Z_Construct_UScriptStruct_FCard_Hash() { return 1228877526U; }
class UScriptStruct* FEntityBaseStats::StaticStruct()
{
	static class UScriptStruct* Singleton = NULL;
	if (!Singleton)
	{
		extern LOSTWORLD_API uint32 Get_Z_Construct_UScriptStruct_FEntityBaseStats_Hash();
		Singleton = GetStaticStruct(Z_Construct_UScriptStruct_FEntityBaseStats, Z_Construct_UPackage__Script_LostWorld(), TEXT("EntityBaseStats"), sizeof(FEntityBaseStats), Get_Z_Construct_UScriptStruct_FEntityBaseStats_Hash());
	}
	return Singleton;
}
template<> LOSTWORLD_API UScriptStruct* StaticStruct<FEntityBaseStats>()
{
	return FEntityBaseStats::StaticStruct();
}
static FCompiledInDeferStruct Z_CompiledInDeferStruct_UScriptStruct_FEntityBaseStats(FEntityBaseStats::StaticStruct, TEXT("/Script/LostWorld"), TEXT("EntityBaseStats"), false, nullptr, nullptr);
static struct FScriptStruct_LostWorld_StaticRegisterNativesFEntityBaseStats
{
	FScriptStruct_LostWorld_StaticRegisterNativesFEntityBaseStats()
	{
		UScriptStruct::DeferCppStructOps(FName(TEXT("EntityBaseStats")),new UScriptStruct::TCppStructOps<FEntityBaseStats>);
	}
} ScriptStruct_LostWorld_StaticRegisterNativesFEntityBaseStats;
	struct Z_Construct_UScriptStruct_FEntityBaseStats_Statics
	{
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Struct_MetaDataParams[];
#endif
		static void* NewStructOps();
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_Strength_MetaData[];
#endif
		static const UE4CodeGen_Private::FUnsizedIntPropertyParams NewProp_Strength;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
		static const UE4CodeGen_Private::FStructParams ReturnStructParams;
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FEntityBaseStats_Statics::Struct_MetaDataParams[] = {
		{ "BlueprintType", "true" },
		{ "Comment", "// -------------------------------- Entities\n" },
		{ "ModuleRelativePath", "Variables.h" },
		{ "ToolTip", "-------------------------------- Entities" },
	};
#endif
	void* Z_Construct_UScriptStruct_FEntityBaseStats_Statics::NewStructOps()
	{
		return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FEntityBaseStats>();
	}
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FEntityBaseStats_Statics::NewProp_Strength_MetaData[] = {
		{ "Category", "EntityBaseStats" },
		{ "Comment", "// Increases damage dealt by physical attacks.\n" },
		{ "ModuleRelativePath", "Variables.h" },
		{ "ToolTip", "Increases damage dealt by physical attacks." },
	};
#endif
	const UE4CodeGen_Private::FUnsizedIntPropertyParams Z_Construct_UScriptStruct_FEntityBaseStats_Statics::NewProp_Strength = { "Strength", nullptr, (EPropertyFlags)0x0010000000000005, UE4CodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FEntityBaseStats, Strength), METADATA_PARAMS(Z_Construct_UScriptStruct_FEntityBaseStats_Statics::NewProp_Strength_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FEntityBaseStats_Statics::NewProp_Strength_MetaData)) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UScriptStruct_FEntityBaseStats_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FEntityBaseStats_Statics::NewProp_Strength,
	};
	const UE4CodeGen_Private::FStructParams Z_Construct_UScriptStruct_FEntityBaseStats_Statics::ReturnStructParams = {
		(UObject* (*)())Z_Construct_UPackage__Script_LostWorld,
		nullptr,
		&NewStructOps,
		"EntityBaseStats",
		sizeof(FEntityBaseStats),
		alignof(FEntityBaseStats),
		Z_Construct_UScriptStruct_FEntityBaseStats_Statics::PropPointers,
		UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FEntityBaseStats_Statics::PropPointers),
		RF_Public|RF_Transient|RF_MarkAsNative,
		EStructFlags(0x00000201),
		METADATA_PARAMS(Z_Construct_UScriptStruct_FEntityBaseStats_Statics::Struct_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FEntityBaseStats_Statics::Struct_MetaDataParams))
	};
	UScriptStruct* Z_Construct_UScriptStruct_FEntityBaseStats()
	{
#if WITH_HOT_RELOAD
		extern uint32 Get_Z_Construct_UScriptStruct_FEntityBaseStats_Hash();
		UPackage* Outer = Z_Construct_UPackage__Script_LostWorld();
		static UScriptStruct* ReturnStruct = FindExistingStructIfHotReloadOrDynamic(Outer, TEXT("EntityBaseStats"), sizeof(FEntityBaseStats), Get_Z_Construct_UScriptStruct_FEntityBaseStats_Hash(), false);
#else
		static UScriptStruct* ReturnStruct = nullptr;
#endif
		if (!ReturnStruct)
		{
			UE4CodeGen_Private::ConstructUScriptStruct(ReturnStruct, Z_Construct_UScriptStruct_FEntityBaseStats_Statics::ReturnStructParams);
		}
		return ReturnStruct;
	}
	uint32 Get_Z_Construct_UScriptStruct_FEntityBaseStats_Hash() { return 3585053802U; }
class UScriptStruct* FRoomDataAsStruct::StaticStruct()
{
	static class UScriptStruct* Singleton = NULL;
	if (!Singleton)
	{
		extern LOSTWORLD_API uint32 Get_Z_Construct_UScriptStruct_FRoomDataAsStruct_Hash();
		Singleton = GetStaticStruct(Z_Construct_UScriptStruct_FRoomDataAsStruct, Z_Construct_UPackage__Script_LostWorld(), TEXT("RoomDataAsStruct"), sizeof(FRoomDataAsStruct), Get_Z_Construct_UScriptStruct_FRoomDataAsStruct_Hash());
	}
	return Singleton;
}
template<> LOSTWORLD_API UScriptStruct* StaticStruct<FRoomDataAsStruct>()
{
	return FRoomDataAsStruct::StaticStruct();
}
static FCompiledInDeferStruct Z_CompiledInDeferStruct_UScriptStruct_FRoomDataAsStruct(FRoomDataAsStruct::StaticStruct, TEXT("/Script/LostWorld"), TEXT("RoomDataAsStruct"), false, nullptr, nullptr);
static struct FScriptStruct_LostWorld_StaticRegisterNativesFRoomDataAsStruct
{
	FScriptStruct_LostWorld_StaticRegisterNativesFRoomDataAsStruct()
	{
		UScriptStruct::DeferCppStructOps(FName(TEXT("RoomDataAsStruct")),new UScriptStruct::TCppStructOps<FRoomDataAsStruct>);
	}
} ScriptStruct_LostWorld_StaticRegisterNativesFRoomDataAsStruct;
	struct Z_Construct_UScriptStruct_FRoomDataAsStruct_Statics
	{
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Struct_MetaDataParams[];
#endif
		static void* NewStructOps();
		static const UE4CodeGen_Private::FStructParams ReturnStructParams;
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FRoomDataAsStruct_Statics::Struct_MetaDataParams[] = {
		{ "BlueprintType", "true" },
		{ "ModuleRelativePath", "Variables.h" },
	};
#endif
	void* Z_Construct_UScriptStruct_FRoomDataAsStruct_Statics::NewStructOps()
	{
		return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FRoomDataAsStruct>();
	}
	const UE4CodeGen_Private::FStructParams Z_Construct_UScriptStruct_FRoomDataAsStruct_Statics::ReturnStructParams = {
		(UObject* (*)())Z_Construct_UPackage__Script_LostWorld,
		nullptr,
		&NewStructOps,
		"RoomDataAsStruct",
		sizeof(FRoomDataAsStruct),
		alignof(FRoomDataAsStruct),
		nullptr,
		0,
		RF_Public|RF_Transient|RF_MarkAsNative,
		EStructFlags(0x00000201),
		METADATA_PARAMS(Z_Construct_UScriptStruct_FRoomDataAsStruct_Statics::Struct_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FRoomDataAsStruct_Statics::Struct_MetaDataParams))
	};
	UScriptStruct* Z_Construct_UScriptStruct_FRoomDataAsStruct()
	{
#if WITH_HOT_RELOAD
		extern uint32 Get_Z_Construct_UScriptStruct_FRoomDataAsStruct_Hash();
		UPackage* Outer = Z_Construct_UPackage__Script_LostWorld();
		static UScriptStruct* ReturnStruct = FindExistingStructIfHotReloadOrDynamic(Outer, TEXT("RoomDataAsStruct"), sizeof(FRoomDataAsStruct), Get_Z_Construct_UScriptStruct_FRoomDataAsStruct_Hash(), false);
#else
		static UScriptStruct* ReturnStruct = nullptr;
#endif
		if (!ReturnStruct)
		{
			UE4CodeGen_Private::ConstructUScriptStruct(ReturnStruct, Z_Construct_UScriptStruct_FRoomDataAsStruct_Statics::ReturnStructParams);
		}
		return ReturnStruct;
	}
	uint32 Get_Z_Construct_UScriptStruct_FRoomDataAsStruct_Hash() { return 2613336404U; }
class UScriptStruct* FFloorDataAsStruct::StaticStruct()
{
	static class UScriptStruct* Singleton = NULL;
	if (!Singleton)
	{
		extern LOSTWORLD_API uint32 Get_Z_Construct_UScriptStruct_FFloorDataAsStruct_Hash();
		Singleton = GetStaticStruct(Z_Construct_UScriptStruct_FFloorDataAsStruct, Z_Construct_UPackage__Script_LostWorld(), TEXT("FloorDataAsStruct"), sizeof(FFloorDataAsStruct), Get_Z_Construct_UScriptStruct_FFloorDataAsStruct_Hash());
	}
	return Singleton;
}
template<> LOSTWORLD_API UScriptStruct* StaticStruct<FFloorDataAsStruct>()
{
	return FFloorDataAsStruct::StaticStruct();
}
static FCompiledInDeferStruct Z_CompiledInDeferStruct_UScriptStruct_FFloorDataAsStruct(FFloorDataAsStruct::StaticStruct, TEXT("/Script/LostWorld"), TEXT("FloorDataAsStruct"), false, nullptr, nullptr);
static struct FScriptStruct_LostWorld_StaticRegisterNativesFFloorDataAsStruct
{
	FScriptStruct_LostWorld_StaticRegisterNativesFFloorDataAsStruct()
	{
		UScriptStruct::DeferCppStructOps(FName(TEXT("FloorDataAsStruct")),new UScriptStruct::TCppStructOps<FFloorDataAsStruct>);
	}
} ScriptStruct_LostWorld_StaticRegisterNativesFFloorDataAsStruct;
	struct Z_Construct_UScriptStruct_FFloorDataAsStruct_Statics
	{
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Struct_MetaDataParams[];
#endif
		static void* NewStructOps();
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_MaximumWidth_MetaData[];
#endif
		static const UE4CodeGen_Private::FUnsizedIntPropertyParams NewProp_MaximumWidth;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_MaximumLength_MetaData[];
#endif
		static const UE4CodeGen_Private::FUnsizedIntPropertyParams NewProp_MaximumLength;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_MinimumWidth_MetaData[];
#endif
		static const UE4CodeGen_Private::FUnsizedIntPropertyParams NewProp_MinimumWidth;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_MinimumLength_MetaData[];
#endif
		static const UE4CodeGen_Private::FUnsizedIntPropertyParams NewProp_MinimumLength;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
		static const UE4CodeGen_Private::FStructParams ReturnStructParams;
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FFloorDataAsStruct_Statics::Struct_MetaDataParams[] = {
		{ "BlueprintType", "true" },
		{ "ModuleRelativePath", "Variables.h" },
	};
#endif
	void* Z_Construct_UScriptStruct_FFloorDataAsStruct_Statics::NewStructOps()
	{
		return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FFloorDataAsStruct>();
	}
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FFloorDataAsStruct_Statics::NewProp_MaximumWidth_MetaData[] = {
		{ "Category", "FloorDataAsStruct" },
		{ "ModuleRelativePath", "Variables.h" },
	};
#endif
	const UE4CodeGen_Private::FUnsizedIntPropertyParams Z_Construct_UScriptStruct_FFloorDataAsStruct_Statics::NewProp_MaximumWidth = { "MaximumWidth", nullptr, (EPropertyFlags)0x0010000000000005, UE4CodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FFloorDataAsStruct, MaximumWidth), METADATA_PARAMS(Z_Construct_UScriptStruct_FFloorDataAsStruct_Statics::NewProp_MaximumWidth_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FFloorDataAsStruct_Statics::NewProp_MaximumWidth_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FFloorDataAsStruct_Statics::NewProp_MaximumLength_MetaData[] = {
		{ "Category", "FloorDataAsStruct" },
		{ "Comment", "// This is the maximum size of the map in tiles\n" },
		{ "ModuleRelativePath", "Variables.h" },
		{ "ToolTip", "This is the maximum size of the map in tiles" },
	};
#endif
	const UE4CodeGen_Private::FUnsizedIntPropertyParams Z_Construct_UScriptStruct_FFloorDataAsStruct_Statics::NewProp_MaximumLength = { "MaximumLength", nullptr, (EPropertyFlags)0x0010000000000005, UE4CodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FFloorDataAsStruct, MaximumLength), METADATA_PARAMS(Z_Construct_UScriptStruct_FFloorDataAsStruct_Statics::NewProp_MaximumLength_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FFloorDataAsStruct_Statics::NewProp_MaximumLength_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FFloorDataAsStruct_Statics::NewProp_MinimumWidth_MetaData[] = {
		{ "Category", "FloorDataAsStruct" },
		{ "Comment", "// The east-west dimension will be called 'Width' and 'Y'.\n" },
		{ "ModuleRelativePath", "Variables.h" },
		{ "ToolTip", "The east-west dimension will be called 'Width' and 'Y'." },
	};
#endif
	const UE4CodeGen_Private::FUnsizedIntPropertyParams Z_Construct_UScriptStruct_FFloorDataAsStruct_Statics::NewProp_MinimumWidth = { "MinimumWidth", nullptr, (EPropertyFlags)0x0010000000000005, UE4CodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FFloorDataAsStruct, MinimumWidth), METADATA_PARAMS(Z_Construct_UScriptStruct_FFloorDataAsStruct_Statics::NewProp_MinimumWidth_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FFloorDataAsStruct_Statics::NewProp_MinimumWidth_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FFloorDataAsStruct_Statics::NewProp_MinimumLength_MetaData[] = {
		{ "Category", "FloorDataAsStruct" },
		{ "Comment", "// The north-south dimension will be called 'Length' and 'X'.\n// This is the minimum size of the map in tiles\n" },
		{ "ModuleRelativePath", "Variables.h" },
		{ "ToolTip", "The north-south dimension will be called 'Length' and 'X'.\nThis is the minimum size of the map in tiles" },
	};
#endif
	const UE4CodeGen_Private::FUnsizedIntPropertyParams Z_Construct_UScriptStruct_FFloorDataAsStruct_Statics::NewProp_MinimumLength = { "MinimumLength", nullptr, (EPropertyFlags)0x0010000000000005, UE4CodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FFloorDataAsStruct, MinimumLength), METADATA_PARAMS(Z_Construct_UScriptStruct_FFloorDataAsStruct_Statics::NewProp_MinimumLength_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FFloorDataAsStruct_Statics::NewProp_MinimumLength_MetaData)) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UScriptStruct_FFloorDataAsStruct_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FFloorDataAsStruct_Statics::NewProp_MaximumWidth,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FFloorDataAsStruct_Statics::NewProp_MaximumLength,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FFloorDataAsStruct_Statics::NewProp_MinimumWidth,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FFloorDataAsStruct_Statics::NewProp_MinimumLength,
	};
	const UE4CodeGen_Private::FStructParams Z_Construct_UScriptStruct_FFloorDataAsStruct_Statics::ReturnStructParams = {
		(UObject* (*)())Z_Construct_UPackage__Script_LostWorld,
		nullptr,
		&NewStructOps,
		"FloorDataAsStruct",
		sizeof(FFloorDataAsStruct),
		alignof(FFloorDataAsStruct),
		Z_Construct_UScriptStruct_FFloorDataAsStruct_Statics::PropPointers,
		UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FFloorDataAsStruct_Statics::PropPointers),
		RF_Public|RF_Transient|RF_MarkAsNative,
		EStructFlags(0x00000201),
		METADATA_PARAMS(Z_Construct_UScriptStruct_FFloorDataAsStruct_Statics::Struct_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FFloorDataAsStruct_Statics::Struct_MetaDataParams))
	};
	UScriptStruct* Z_Construct_UScriptStruct_FFloorDataAsStruct()
	{
#if WITH_HOT_RELOAD
		extern uint32 Get_Z_Construct_UScriptStruct_FFloorDataAsStruct_Hash();
		UPackage* Outer = Z_Construct_UPackage__Script_LostWorld();
		static UScriptStruct* ReturnStruct = FindExistingStructIfHotReloadOrDynamic(Outer, TEXT("FloorDataAsStruct"), sizeof(FFloorDataAsStruct), Get_Z_Construct_UScriptStruct_FFloorDataAsStruct_Hash(), false);
#else
		static UScriptStruct* ReturnStruct = nullptr;
#endif
		if (!ReturnStruct)
		{
			UE4CodeGen_Private::ConstructUScriptStruct(ReturnStruct, Z_Construct_UScriptStruct_FFloorDataAsStruct_Statics::ReturnStructParams);
		}
		return ReturnStruct;
	}
	uint32 Get_Z_Construct_UScriptStruct_FFloorDataAsStruct_Hash() { return 1029477844U; }
class UScriptStruct* FLevelDataAsStruct::StaticStruct()
{
	static class UScriptStruct* Singleton = NULL;
	if (!Singleton)
	{
		extern LOSTWORLD_API uint32 Get_Z_Construct_UScriptStruct_FLevelDataAsStruct_Hash();
		Singleton = GetStaticStruct(Z_Construct_UScriptStruct_FLevelDataAsStruct, Z_Construct_UPackage__Script_LostWorld(), TEXT("LevelDataAsStruct"), sizeof(FLevelDataAsStruct), Get_Z_Construct_UScriptStruct_FLevelDataAsStruct_Hash());
	}
	return Singleton;
}
template<> LOSTWORLD_API UScriptStruct* StaticStruct<FLevelDataAsStruct>()
{
	return FLevelDataAsStruct::StaticStruct();
}
static FCompiledInDeferStruct Z_CompiledInDeferStruct_UScriptStruct_FLevelDataAsStruct(FLevelDataAsStruct::StaticStruct, TEXT("/Script/LostWorld"), TEXT("LevelDataAsStruct"), false, nullptr, nullptr);
static struct FScriptStruct_LostWorld_StaticRegisterNativesFLevelDataAsStruct
{
	FScriptStruct_LostWorld_StaticRegisterNativesFLevelDataAsStruct()
	{
		UScriptStruct::DeferCppStructOps(FName(TEXT("LevelDataAsStruct")),new UScriptStruct::TCppStructOps<FLevelDataAsStruct>);
	}
} ScriptStruct_LostWorld_StaticRegisterNativesFLevelDataAsStruct;
	struct Z_Construct_UScriptStruct_FLevelDataAsStruct_Statics
	{
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Struct_MetaDataParams[];
#endif
		static void* NewStructOps();
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_StairsGoUp_MetaData[];
#endif
		static void NewProp_StairsGoUp_SetBit(void* Obj);
		static const UE4CodeGen_Private::FBoolPropertyParams NewProp_StairsGoUp;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
		static const UE4CodeGen_Private::FStructParams ReturnStructParams;
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FLevelDataAsStruct_Statics::Struct_MetaDataParams[] = {
		{ "BlueprintType", "true" },
		{ "Comment", "// -------------------------------- Levels\n" },
		{ "ModuleRelativePath", "Variables.h" },
		{ "ToolTip", "-------------------------------- Levels" },
	};
#endif
	void* Z_Construct_UScriptStruct_FLevelDataAsStruct_Statics::NewStructOps()
	{
		return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FLevelDataAsStruct>();
	}
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FLevelDataAsStruct_Statics::NewProp_StairsGoUp_MetaData[] = {
		{ "Category", "LevelDataAsStruct" },
		{ "Comment", "// If true, the floor count will increment by +1 and\n// the stairs will appear to climb upward.\n// If false, then the reverse will be the case\n" },
		{ "ModuleRelativePath", "Variables.h" },
		{ "ToolTip", "If true, the floor count will increment by +1 and\nthe stairs will appear to climb upward.\nIf false, then the reverse will be the case" },
	};
#endif
	void Z_Construct_UScriptStruct_FLevelDataAsStruct_Statics::NewProp_StairsGoUp_SetBit(void* Obj)
	{
		((FLevelDataAsStruct*)Obj)->StairsGoUp = 1;
	}
	const UE4CodeGen_Private::FBoolPropertyParams Z_Construct_UScriptStruct_FLevelDataAsStruct_Statics::NewProp_StairsGoUp = { "StairsGoUp", nullptr, (EPropertyFlags)0x0010000000000005, UE4CodeGen_Private::EPropertyGenFlags::Bool | UE4CodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, 1, sizeof(bool), sizeof(FLevelDataAsStruct), &Z_Construct_UScriptStruct_FLevelDataAsStruct_Statics::NewProp_StairsGoUp_SetBit, METADATA_PARAMS(Z_Construct_UScriptStruct_FLevelDataAsStruct_Statics::NewProp_StairsGoUp_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FLevelDataAsStruct_Statics::NewProp_StairsGoUp_MetaData)) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UScriptStruct_FLevelDataAsStruct_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FLevelDataAsStruct_Statics::NewProp_StairsGoUp,
	};
	const UE4CodeGen_Private::FStructParams Z_Construct_UScriptStruct_FLevelDataAsStruct_Statics::ReturnStructParams = {
		(UObject* (*)())Z_Construct_UPackage__Script_LostWorld,
		nullptr,
		&NewStructOps,
		"LevelDataAsStruct",
		sizeof(FLevelDataAsStruct),
		alignof(FLevelDataAsStruct),
		Z_Construct_UScriptStruct_FLevelDataAsStruct_Statics::PropPointers,
		UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FLevelDataAsStruct_Statics::PropPointers),
		RF_Public|RF_Transient|RF_MarkAsNative,
		EStructFlags(0x00000201),
		METADATA_PARAMS(Z_Construct_UScriptStruct_FLevelDataAsStruct_Statics::Struct_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FLevelDataAsStruct_Statics::Struct_MetaDataParams))
	};
	UScriptStruct* Z_Construct_UScriptStruct_FLevelDataAsStruct()
	{
#if WITH_HOT_RELOAD
		extern uint32 Get_Z_Construct_UScriptStruct_FLevelDataAsStruct_Hash();
		UPackage* Outer = Z_Construct_UPackage__Script_LostWorld();
		static UScriptStruct* ReturnStruct = FindExistingStructIfHotReloadOrDynamic(Outer, TEXT("LevelDataAsStruct"), sizeof(FLevelDataAsStruct), Get_Z_Construct_UScriptStruct_FLevelDataAsStruct_Hash(), false);
#else
		static UScriptStruct* ReturnStruct = nullptr;
#endif
		if (!ReturnStruct)
		{
			UE4CodeGen_Private::ConstructUScriptStruct(ReturnStruct, Z_Construct_UScriptStruct_FLevelDataAsStruct_Statics::ReturnStructParams);
		}
		return ReturnStruct;
	}
	uint32 Get_Z_Construct_UScriptStruct_FLevelDataAsStruct_Hash() { return 1950019508U; }
PRAGMA_ENABLE_DEPRECATION_WARNINGS
#ifdef _MSC_VER
#pragma warning (pop)
#endif
