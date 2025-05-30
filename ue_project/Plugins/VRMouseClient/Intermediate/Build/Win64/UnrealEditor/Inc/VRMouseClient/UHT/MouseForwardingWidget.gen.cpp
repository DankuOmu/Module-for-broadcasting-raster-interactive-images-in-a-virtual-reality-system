// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "VRMouseClient/Public/MouseForwardingWidget.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeMouseForwardingWidget() {}

// Begin Cross Module References
UMG_API UClass* Z_Construct_UClass_UUserWidget();
UPackage* Z_Construct_UPackage__Script_VRMouseClient();
VRMOUSECLIENT_API UClass* Z_Construct_UClass_UMouseForwardingWidget();
VRMOUSECLIENT_API UClass* Z_Construct_UClass_UMouseForwardingWidget_NoRegister();
VRMOUSECLIENT_API UClass* Z_Construct_UClass_UVRMouseClient_NoRegister();
// End Cross Module References

// Begin Class UMouseForwardingWidget
void UMouseForwardingWidget::StaticRegisterNativesUMouseForwardingWidget()
{
}
IMPLEMENT_CLASS_NO_AUTO_REGISTRATION(UMouseForwardingWidget);
UClass* Z_Construct_UClass_UMouseForwardingWidget_NoRegister()
{
	return UMouseForwardingWidget::StaticClass();
}
struct Z_Construct_UClass_UMouseForwardingWidget_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[] = {
		{ "IncludePath", "MouseForwardingWidget.h" },
		{ "ModuleRelativePath", "Public/MouseForwardingWidget.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_VRMouseClientRef_MetaData[] = {
		{ "Category", "VR Mouse" },
		{ "ModuleRelativePath", "Public/MouseForwardingWidget.h" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FObjectPropertyParams NewProp_VRMouseClientRef;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static UObject* (*const DependentSingletons[])();
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UMouseForwardingWidget>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
};
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_UMouseForwardingWidget_Statics::NewProp_VRMouseClientRef = { "VRMouseClientRef", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UMouseForwardingWidget, VRMouseClientRef), Z_Construct_UClass_UVRMouseClient_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_VRMouseClientRef_MetaData), NewProp_VRMouseClientRef_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_UMouseForwardingWidget_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UMouseForwardingWidget_Statics::NewProp_VRMouseClientRef,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_UMouseForwardingWidget_Statics::PropPointers) < 2048);
UObject* (*const Z_Construct_UClass_UMouseForwardingWidget_Statics::DependentSingletons[])() = {
	(UObject* (*)())Z_Construct_UClass_UUserWidget,
	(UObject* (*)())Z_Construct_UPackage__Script_VRMouseClient,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_UMouseForwardingWidget_Statics::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams Z_Construct_UClass_UMouseForwardingWidget_Statics::ClassParams = {
	&UMouseForwardingWidget::StaticClass,
	nullptr,
	&StaticCppClassTypeInfo,
	DependentSingletons,
	nullptr,
	Z_Construct_UClass_UMouseForwardingWidget_Statics::PropPointers,
	nullptr,
	UE_ARRAY_COUNT(DependentSingletons),
	0,
	UE_ARRAY_COUNT(Z_Construct_UClass_UMouseForwardingWidget_Statics::PropPointers),
	0,
	0x00B010A0u,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_UMouseForwardingWidget_Statics::Class_MetaDataParams), Z_Construct_UClass_UMouseForwardingWidget_Statics::Class_MetaDataParams)
};
UClass* Z_Construct_UClass_UMouseForwardingWidget()
{
	if (!Z_Registration_Info_UClass_UMouseForwardingWidget.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_UMouseForwardingWidget.OuterSingleton, Z_Construct_UClass_UMouseForwardingWidget_Statics::ClassParams);
	}
	return Z_Registration_Info_UClass_UMouseForwardingWidget.OuterSingleton;
}
template<> VRMOUSECLIENT_API UClass* StaticClass<UMouseForwardingWidget>()
{
	return UMouseForwardingWidget::StaticClass();
}
UMouseForwardingWidget::UMouseForwardingWidget(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {}
DEFINE_VTABLE_PTR_HELPER_CTOR(UMouseForwardingWidget);
UMouseForwardingWidget::~UMouseForwardingWidget() {}
// End Class UMouseForwardingWidget

// Begin Registration
struct Z_CompiledInDeferFile_FID_VRMouseClientProject_Plugins_VRMouseClient_Source_VRMouseClient_Public_MouseForwardingWidget_h_Statics
{
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_UMouseForwardingWidget, UMouseForwardingWidget::StaticClass, TEXT("UMouseForwardingWidget"), &Z_Registration_Info_UClass_UMouseForwardingWidget, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(UMouseForwardingWidget), 115473755U) },
	};
};
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_VRMouseClientProject_Plugins_VRMouseClient_Source_VRMouseClient_Public_MouseForwardingWidget_h_2049583360(TEXT("/Script/VRMouseClient"),
	Z_CompiledInDeferFile_FID_VRMouseClientProject_Plugins_VRMouseClient_Source_VRMouseClient_Public_MouseForwardingWidget_h_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_VRMouseClientProject_Plugins_VRMouseClient_Source_VRMouseClient_Public_MouseForwardingWidget_h_Statics::ClassInfo),
	nullptr, 0,
	nullptr, 0);
// End Registration
PRAGMA_ENABLE_DEPRECATION_WARNINGS
