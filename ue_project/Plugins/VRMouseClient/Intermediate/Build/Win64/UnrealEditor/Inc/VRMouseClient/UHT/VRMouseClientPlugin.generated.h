// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

// IWYU pragma: private, include "VRMouseClientPlugin.h"
#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
#ifdef VRMOUSECLIENT_VRMouseClientPlugin_generated_h
#error "VRMouseClientPlugin.generated.h already included, missing '#pragma once' in VRMouseClientPlugin.h"
#endif
#define VRMOUSECLIENT_VRMouseClientPlugin_generated_h

#define FID_VRMouseClientProject_Plugins_VRMouseClient_Source_VRMouseClient_Public_VRMouseClientPlugin_h_20_RPC_WRAPPERS_NO_PURE_DECLS \
	DECLARE_FUNCTION(execSendWorldClickEvent); \
	DECLARE_FUNCTION(execIsConnected); \
	DECLARE_FUNCTION(execDisconnect); \
	DECLARE_FUNCTION(execSendMouseMove); \
	DECLARE_FUNCTION(execSendMouseClick); \
	DECLARE_FUNCTION(execConnect); \
	DECLARE_FUNCTION(execSendMouseButtonEvent);


#define FID_VRMouseClientProject_Plugins_VRMouseClient_Source_VRMouseClient_Public_VRMouseClientPlugin_h_20_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesUVRMouseClient(); \
	friend struct Z_Construct_UClass_UVRMouseClient_Statics; \
public: \
	DECLARE_CLASS(UVRMouseClient, UObject, COMPILED_IN_FLAGS(0), CASTCLASS_None, TEXT("/Script/VRMouseClient"), NO_API) \
	DECLARE_SERIALIZER(UVRMouseClient)


#define FID_VRMouseClientProject_Plugins_VRMouseClient_Source_VRMouseClient_Public_VRMouseClientPlugin_h_20_ENHANCED_CONSTRUCTORS \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	UVRMouseClient(UVRMouseClient&&); \
	UVRMouseClient(const UVRMouseClient&); \
public: \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, UVRMouseClient); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(UVRMouseClient); \
	DEFINE_DEFAULT_CONSTRUCTOR_CALL(UVRMouseClient) \
	NO_API virtual ~UVRMouseClient();


#define FID_VRMouseClientProject_Plugins_VRMouseClient_Source_VRMouseClient_Public_VRMouseClientPlugin_h_17_PROLOG
#define FID_VRMouseClientProject_Plugins_VRMouseClient_Source_VRMouseClient_Public_VRMouseClientPlugin_h_20_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	FID_VRMouseClientProject_Plugins_VRMouseClient_Source_VRMouseClient_Public_VRMouseClientPlugin_h_20_RPC_WRAPPERS_NO_PURE_DECLS \
	FID_VRMouseClientProject_Plugins_VRMouseClient_Source_VRMouseClient_Public_VRMouseClientPlugin_h_20_INCLASS_NO_PURE_DECLS \
	FID_VRMouseClientProject_Plugins_VRMouseClient_Source_VRMouseClient_Public_VRMouseClientPlugin_h_20_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


template<> VRMOUSECLIENT_API UClass* StaticClass<class UVRMouseClient>();

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID FID_VRMouseClientProject_Plugins_VRMouseClient_Source_VRMouseClient_Public_VRMouseClientPlugin_h


PRAGMA_ENABLE_DEPRECATION_WARNINGS
