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

#define LostWorld_Source_LostWorld_Variables_h_143_GENERATED_BODY \
	friend struct Z_Construct_UScriptStruct_FCard_Statics; \
	static class UScriptStruct* StaticStruct();


template<> LOSTWORLD_API UScriptStruct* StaticStruct<struct FCard>();

#define LostWorld_Source_LostWorld_Variables_h_125_GENERATED_BODY \
	friend struct Z_Construct_UScriptStruct_FEntityBaseStats_Statics; \
	static class UScriptStruct* StaticStruct();


template<> LOSTWORLD_API UScriptStruct* StaticStruct<struct FEntityBaseStats>();

#define LostWorld_Source_LostWorld_Variables_h_103_GENERATED_BODY \
	friend struct Z_Construct_UScriptStruct_FLevelDataAsStruct_Statics; \
	static class UScriptStruct* StaticStruct();


template<> LOSTWORLD_API UScriptStruct* StaticStruct<struct FLevelDataAsStruct>();

#define LostWorld_Source_LostWorld_Variables_h_65_GENERATED_BODY \
	friend struct Z_Construct_UScriptStruct_FFloorDataAsStruct_Statics; \
	static class UScriptStruct* StaticStruct();


template<> LOSTWORLD_API UScriptStruct* StaticStruct<struct FFloorDataAsStruct>();

#define LostWorld_Source_LostWorld_Variables_h_36_GENERATED_BODY \
	friend struct Z_Construct_UScriptStruct_FRoomDataAsStruct_Statics; \
	static class UScriptStruct* StaticStruct();


template<> LOSTWORLD_API UScriptStruct* StaticStruct<struct FRoomDataAsStruct>();

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

#define FOREACH_ENUM_EFLOORLAYOUTS(op) \
	op(EFloorLayouts::FourSquares) 

enum class EFloorLayouts : uint8;
template<> LOSTWORLD_API UEnum* StaticEnum<EFloorLayouts>();

PRAGMA_ENABLE_DEPRECATION_WARNINGS
