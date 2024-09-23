// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
#ifdef LOSTWORLD_Variables_generated_h
#error "Variables.generated.h already included, missing '#pragma once' in Variables.h"
#endif
#define LOSTWORLD_Variables_generated_h

#define LostWorld_Source_LostWorld_Variables_h_105_GENERATED_BODY \
	friend struct Z_Construct_UScriptStruct_FCard_Statics; \
	static class UScriptStruct* StaticStruct();


template<> LOSTWORLD_API UScriptStruct* StaticStruct<struct FCard>();

#define LostWorld_Source_LostWorld_Variables_h_87_GENERATED_BODY \
	friend struct Z_Construct_UScriptStruct_FEntityBaseStats_Statics; \
	static class UScriptStruct* StaticStruct();


template<> LOSTWORLD_API UScriptStruct* StaticStruct<struct FEntityBaseStats>();

#define LostWorld_Source_LostWorld_Variables_h_79_GENERATED_BODY \
	friend struct Z_Construct_UScriptStruct_FRoomDataAsStruct_Statics; \
	static class UScriptStruct* StaticStruct();


template<> LOSTWORLD_API UScriptStruct* StaticStruct<struct FRoomDataAsStruct>();

#define LostWorld_Source_LostWorld_Variables_h_48_GENERATED_BODY \
	friend struct Z_Construct_UScriptStruct_FFloorDataAsStruct_Statics; \
	static class UScriptStruct* StaticStruct();


template<> LOSTWORLD_API UScriptStruct* StaticStruct<struct FFloorDataAsStruct>();

#define LostWorld_Source_LostWorld_Variables_h_30_GENERATED_BODY \
	friend struct Z_Construct_UScriptStruct_FLevelDataAsStruct_Statics; \
	static class UScriptStruct* StaticStruct();


template<> LOSTWORLD_API UScriptStruct* StaticStruct<struct FLevelDataAsStruct>();

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID LostWorld_Source_LostWorld_Variables_h


#define FOREACH_ENUM_ECARDTYPES(op) \
	op(ECardTypes::Spell) \
	op(ECardTypes::Summon) \
	op(ECardTypes::Technique) \
	op(ECardTypes::Command) \
	op(ECardTypes::Shout) 

enum class ECardTypes : uint8;
template<> LOSTWORLD_API UEnum* StaticEnum<ECardTypes>();

PRAGMA_ENABLE_DEPRECATION_WARNINGS
