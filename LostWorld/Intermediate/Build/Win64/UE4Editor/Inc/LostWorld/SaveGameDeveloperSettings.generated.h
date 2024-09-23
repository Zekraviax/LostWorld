// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
#ifdef LOSTWORLD_SaveGameDeveloperSettings_generated_h
#error "SaveGameDeveloperSettings.generated.h already included, missing '#pragma once' in SaveGameDeveloperSettings.h"
#endif
#define LOSTWORLD_SaveGameDeveloperSettings_generated_h

#define LostWorld_Source_LostWorld_SaveGameDeveloperSettings_h_12_GENERATED_BODY \
	friend struct Z_Construct_UScriptStruct_FDeveloperSettingsAsStruct_Statics; \
	static class UScriptStruct* StaticStruct();


template<> LOSTWORLD_API UScriptStruct* StaticStruct<struct FDeveloperSettingsAsStruct>();

#define LostWorld_Source_LostWorld_SaveGameDeveloperSettings_h_35_SPARSE_DATA
#define LostWorld_Source_LostWorld_SaveGameDeveloperSettings_h_35_RPC_WRAPPERS \
 \
	DECLARE_FUNCTION(execLoadDeveloperSettingsFromJson); \
	DECLARE_FUNCTION(execSaveDeveloperSettingsToJson);


#define LostWorld_Source_LostWorld_SaveGameDeveloperSettings_h_35_RPC_WRAPPERS_NO_PURE_DECLS \
 \
	DECLARE_FUNCTION(execLoadDeveloperSettingsFromJson); \
	DECLARE_FUNCTION(execSaveDeveloperSettingsToJson);


#define LostWorld_Source_LostWorld_SaveGameDeveloperSettings_h_35_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesUSaveGameDeveloperSettings(); \
	friend struct Z_Construct_UClass_USaveGameDeveloperSettings_Statics; \
public: \
	DECLARE_CLASS(USaveGameDeveloperSettings, USaveGame, COMPILED_IN_FLAGS(0), CASTCLASS_None, TEXT("/Script/LostWorld"), NO_API) \
	DECLARE_SERIALIZER(USaveGameDeveloperSettings)


#define LostWorld_Source_LostWorld_SaveGameDeveloperSettings_h_35_INCLASS \
private: \
	static void StaticRegisterNativesUSaveGameDeveloperSettings(); \
	friend struct Z_Construct_UClass_USaveGameDeveloperSettings_Statics; \
public: \
	DECLARE_CLASS(USaveGameDeveloperSettings, USaveGame, COMPILED_IN_FLAGS(0), CASTCLASS_None, TEXT("/Script/LostWorld"), NO_API) \
	DECLARE_SERIALIZER(USaveGameDeveloperSettings)


#define LostWorld_Source_LostWorld_SaveGameDeveloperSettings_h_35_STANDARD_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API USaveGameDeveloperSettings(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get()); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(USaveGameDeveloperSettings) \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, USaveGameDeveloperSettings); \
DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(USaveGameDeveloperSettings); \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API USaveGameDeveloperSettings(USaveGameDeveloperSettings&&); \
	NO_API USaveGameDeveloperSettings(const USaveGameDeveloperSettings&); \
public:


#define LostWorld_Source_LostWorld_SaveGameDeveloperSettings_h_35_ENHANCED_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API USaveGameDeveloperSettings(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get()) : Super(ObjectInitializer) { }; \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API USaveGameDeveloperSettings(USaveGameDeveloperSettings&&); \
	NO_API USaveGameDeveloperSettings(const USaveGameDeveloperSettings&); \
public: \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, USaveGameDeveloperSettings); \
DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(USaveGameDeveloperSettings); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(USaveGameDeveloperSettings)


#define LostWorld_Source_LostWorld_SaveGameDeveloperSettings_h_35_PRIVATE_PROPERTY_OFFSET
#define LostWorld_Source_LostWorld_SaveGameDeveloperSettings_h_32_PROLOG
#define LostWorld_Source_LostWorld_SaveGameDeveloperSettings_h_35_GENERATED_BODY_LEGACY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	LostWorld_Source_LostWorld_SaveGameDeveloperSettings_h_35_PRIVATE_PROPERTY_OFFSET \
	LostWorld_Source_LostWorld_SaveGameDeveloperSettings_h_35_SPARSE_DATA \
	LostWorld_Source_LostWorld_SaveGameDeveloperSettings_h_35_RPC_WRAPPERS \
	LostWorld_Source_LostWorld_SaveGameDeveloperSettings_h_35_INCLASS \
	LostWorld_Source_LostWorld_SaveGameDeveloperSettings_h_35_STANDARD_CONSTRUCTORS \
public: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


#define LostWorld_Source_LostWorld_SaveGameDeveloperSettings_h_35_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	LostWorld_Source_LostWorld_SaveGameDeveloperSettings_h_35_PRIVATE_PROPERTY_OFFSET \
	LostWorld_Source_LostWorld_SaveGameDeveloperSettings_h_35_SPARSE_DATA \
	LostWorld_Source_LostWorld_SaveGameDeveloperSettings_h_35_RPC_WRAPPERS_NO_PURE_DECLS \
	LostWorld_Source_LostWorld_SaveGameDeveloperSettings_h_35_INCLASS_NO_PURE_DECLS \
	LostWorld_Source_LostWorld_SaveGameDeveloperSettings_h_35_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


template<> LOSTWORLD_API UClass* StaticClass<class USaveGameDeveloperSettings>();

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID LostWorld_Source_LostWorld_SaveGameDeveloperSettings_h


PRAGMA_ENABLE_DEPRECATION_WARNINGS
