// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

// IWYU pragma: private, include "MouseForwardingWidget.h"
#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
#ifdef VRMOUSECLIENT_MouseForwardingWidget_generated_h
#error "MouseForwardingWidget.generated.h already included, missing '#pragma once' in MouseForwardingWidget.h"
#endif
#define VRMOUSECLIENT_MouseForwardingWidget_generated_h

#define FID_VRMouseClientProject_Plugins_VRMouseClient_Source_VRMouseClient_Public_MouseForwardingWidget_h_11_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesUMouseForwardingWidget(); \
	friend struct Z_Construct_UClass_UMouseForwardingWidget_Statics; \
public: \
	DECLARE_CLASS(UMouseForwardingWidget, UUserWidget, COMPILED_IN_FLAGS(0), CASTCLASS_None, TEXT("/Script/VRMouseClient"), NO_API) \
	DECLARE_SERIALIZER(UMouseForwardingWidget)


#define FID_VRMouseClientProject_Plugins_VRMouseClient_Source_VRMouseClient_Public_MouseForwardingWidget_h_11_ENHANCED_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API UMouseForwardingWidget(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get()); \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	UMouseForwardingWidget(UMouseForwardingWidget&&); \
	UMouseForwardingWidget(const UMouseForwardingWidget&); \
public: \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, UMouseForwardingWidget); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(UMouseForwardingWidget); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(UMouseForwardingWidget) \
	NO_API virtual ~UMouseForwardingWidget();


#define FID_VRMouseClientProject_Plugins_VRMouseClient_Source_VRMouseClient_Public_MouseForwardingWidget_h_8_PROLOG
#define FID_VRMouseClientProject_Plugins_VRMouseClient_Source_VRMouseClient_Public_MouseForwardingWidget_h_11_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	FID_VRMouseClientProject_Plugins_VRMouseClient_Source_VRMouseClient_Public_MouseForwardingWidget_h_11_INCLASS_NO_PURE_DECLS \
	FID_VRMouseClientProject_Plugins_VRMouseClient_Source_VRMouseClient_Public_MouseForwardingWidget_h_11_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


template<> VRMOUSECLIENT_API UClass* StaticClass<class UMouseForwardingWidget>();

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID FID_VRMouseClientProject_Plugins_VRMouseClient_Source_VRMouseClient_Public_MouseForwardingWidget_h


PRAGMA_ENABLE_DEPRECATION_WARNINGS
