// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
#ifdef LOSTWORLD_SaveGameLevelData_generated_h
#error "SaveGameLevelData.generated.h already included, missing '#pragma once' in SaveGameLevelData.h"
#endif
#define LOSTWORLD_SaveGameLevelData_generated_h

#define LostWorld_Source_LostWorld_SaveGameLevelData_h_12_SPARSE_DATA
#define LostWorld_Source_LostWorld_SaveGameLevelData_h_12_RPC_WRAPPERS \
 \
	DECLARE_FUNCTION(execSaveLevelDataToJson);


#define LostWorld_Source_LostWorld_SaveGameLevelData_h_12_RPC_WRAPPERS_NO_PURE_DECLS \
 \
	DECLARE_FUNCTION(execSaveLevelDataToJson);


#define LostWorld_Source_LostWorld_SaveGameLevelData_h_12_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesUSaveGameLevelData(); \
	friend struct Z_Construct_UClass_USaveGameLevelData_Statics; \
public: \
	DECLARE_CLASS(USaveGameLevelData, USaveGame, COMPILED_IN_FLAGS(0), CASTCLASS_None, TEXT("/Script/LostWorld"), NO_API) \
	DECLARE_SERIALIZER(USaveGameLevelData)


#define LostWorld_Source_LostWorld_SaveGameLevelData_h_12_INCLASS \
private: \
	static void StaticRegisterNativesUSaveGameLevelData(); \
	friend struct Z_Construct_UClass_USaveGameLevelData_Statics; \
public: \
	DECLARE_CLASS(USaveGameLevelData, USaveGame, COMPILED_IN_FLAGS(0), CASTCLASS_None, TEXT("/Script/LostWorld"), NO_API) \
	DECLARE_SERIALIZER(USaveGameLevelData)


#define LostWorld_Source_LostWorld_SaveGameLevelData_h_12_STANDARD_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API USaveGameLevelData(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get()); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(USaveGameLevelData) \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, USaveGameLevelData); \
DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(USaveGameLevelData); \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API USaveGameLevelData(USaveGameLevelData&&); \
	NO_API USaveGameLevelData(const USaveGameLevelData&); \
public:


#define LostWorld_Source_LostWorld_SaveGameLevelData_h_12_ENHANCED_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API USaveGameLevelData(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get()) : Super(ObjectInitializer) { }; \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API USaveGameLevelData(USaveGameLevelData&&); \
	NO_API USaveGameLevelData(const USaveGameLevelData&); \
public: \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, USaveGameLevelData); \
DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(USaveGameLevelData); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(USaveGameLevelData)


#define LostWorld_Source_LostWorld_SaveGameLevelData_h_12_PRIVATE_PROPERTY_OFFSET
#define LostWorld_Source_LostWorld_SaveGameLevelData_h_9_PROLOG
#define LostWorld_Source_LostWorld_SaveGameLevelData_h_12_GENERATED_BODY_LEGACY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	LostWorld_Source_LostWorld_SaveGameLevelData_h_12_PRIVATE_PROPERTY_OFFSET \
	LostWorld_Source_LostWorld_SaveGameLevelData_h_12_SPARSE_DATA \
	LostWorld_Source_LostWorld_SaveGameLevelData_h_12_RPC_WRAPPERS \
	LostWorld_Source_LostWorld_SaveGameLevelData_h_12_INCLASS \
	LostWorld_Source_LostWorld_SaveGameLevelData_h_12_STANDARD_CONSTRUCTORS \
public: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


#define LostWorld_Source_LostWorld_SaveGameLevelData_h_12_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	LostWorld_Source_LostWorld_SaveGameLevelData_h_12_PRIVATE_PROPERTY_OFFSET \
	LostWorld_Source_LostWorld_SaveGameLevelData_h_12_SPARSE_DATA \
	LostWorld_Source_LostWorld_SaveGameLevelData_h_12_RPC_WRAPPERS_NO_PURE_DECLS \
	LostWorld_Source_LostWorld_SaveGameLevelData_h_12_INCLASS_NO_PURE_DECLS \
	LostWorld_Source_LostWorld_SaveGameLevelData_h_12_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


template<> LOSTWORLD_API UClass* StaticClass<class USaveGameLevelData>();

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID LostWorld_Source_LostWorld_SaveGameLevelData_h


PRAGMA_ENABLE_DEPRECATION_WARNINGS
