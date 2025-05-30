// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "VRMouseClient/Public/VRMouseClientPlugin.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeVRMouseClientPlugin() {}

// Begin Cross Module References
COREUOBJECT_API UClass* Z_Construct_UClass_UObject();
UPackage* Z_Construct_UPackage__Script_VRMouseClient();
VRMOUSECLIENT_API UClass* Z_Construct_UClass_UVRMouseClient();
VRMOUSECLIENT_API UClass* Z_Construct_UClass_UVRMouseClient_NoRegister();
// End Cross Module References

// Begin Class UVRMouseClient Function Connect
struct Z_Construct_UFunction_UVRMouseClient_Connect_Statics
{
	struct VRMouseClient_eventConnect_Parms
	{
		FString Host;
		int32 Port;
		bool ReturnValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "VR Mouse Client" },
		{ "ModuleRelativePath", "Public/VRMouseClientPlugin.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Host_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FStrPropertyParams NewProp_Host;
	static const UECodeGen_Private::FIntPropertyParams NewProp_Port;
	static void NewProp_ReturnValue_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_ReturnValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FStrPropertyParams Z_Construct_UFunction_UVRMouseClient_Connect_Statics::NewProp_Host = { "Host", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(VRMouseClient_eventConnect_Parms, Host), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Host_MetaData), NewProp_Host_MetaData) };
const UECodeGen_Private::FIntPropertyParams Z_Construct_UFunction_UVRMouseClient_Connect_Statics::NewProp_Port = { "Port", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(VRMouseClient_eventConnect_Parms, Port), METADATA_PARAMS(0, nullptr) };
void Z_Construct_UFunction_UVRMouseClient_Connect_Statics::NewProp_ReturnValue_SetBit(void* Obj)
{
	((VRMouseClient_eventConnect_Parms*)Obj)->ReturnValue = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_UVRMouseClient_Connect_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(VRMouseClient_eventConnect_Parms), &Z_Construct_UFunction_UVRMouseClient_Connect_Statics::NewProp_ReturnValue_SetBit, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UVRMouseClient_Connect_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UVRMouseClient_Connect_Statics::NewProp_Host,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UVRMouseClient_Connect_Statics::NewProp_Port,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UVRMouseClient_Connect_Statics::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_UVRMouseClient_Connect_Statics::PropPointers) < 2048);
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UVRMouseClient_Connect_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UVRMouseClient, nullptr, "Connect", nullptr, nullptr, Z_Construct_UFunction_UVRMouseClient_Connect_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UVRMouseClient_Connect_Statics::PropPointers), sizeof(Z_Construct_UFunction_UVRMouseClient_Connect_Statics::VRMouseClient_eventConnect_Parms), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UVRMouseClient_Connect_Statics::Function_MetaDataParams), Z_Construct_UFunction_UVRMouseClient_Connect_Statics::Function_MetaDataParams) };
static_assert(sizeof(Z_Construct_UFunction_UVRMouseClient_Connect_Statics::VRMouseClient_eventConnect_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UVRMouseClient_Connect()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UVRMouseClient_Connect_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UVRMouseClient::execConnect)
{
	P_GET_PROPERTY(FStrProperty,Z_Param_Host);
	P_GET_PROPERTY(FIntProperty,Z_Param_Port);
	P_FINISH;
	P_NATIVE_BEGIN;
	*(bool*)Z_Param__Result=P_THIS->Connect(Z_Param_Host,Z_Param_Port);
	P_NATIVE_END;
}
// End Class UVRMouseClient Function Connect

// Begin Class UVRMouseClient Function Disconnect
struct Z_Construct_UFunction_UVRMouseClient_Disconnect_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "VR Mouse Client" },
		{ "ModuleRelativePath", "Public/VRMouseClientPlugin.h" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UVRMouseClient_Disconnect_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UVRMouseClient, nullptr, "Disconnect", nullptr, nullptr, nullptr, 0, 0, RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UVRMouseClient_Disconnect_Statics::Function_MetaDataParams), Z_Construct_UFunction_UVRMouseClient_Disconnect_Statics::Function_MetaDataParams) };
UFunction* Z_Construct_UFunction_UVRMouseClient_Disconnect()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UVRMouseClient_Disconnect_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UVRMouseClient::execDisconnect)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->Disconnect();
	P_NATIVE_END;
}
// End Class UVRMouseClient Function Disconnect

// Begin Class UVRMouseClient Function IsConnected
struct Z_Construct_UFunction_UVRMouseClient_IsConnected_Statics
{
	struct VRMouseClient_eventIsConnected_Parms
	{
		bool ReturnValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "VR Mouse Client" },
		{ "ModuleRelativePath", "Public/VRMouseClientPlugin.h" },
	};
#endif // WITH_METADATA
	static void NewProp_ReturnValue_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_ReturnValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
void Z_Construct_UFunction_UVRMouseClient_IsConnected_Statics::NewProp_ReturnValue_SetBit(void* Obj)
{
	((VRMouseClient_eventIsConnected_Parms*)Obj)->ReturnValue = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_UVRMouseClient_IsConnected_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(VRMouseClient_eventIsConnected_Parms), &Z_Construct_UFunction_UVRMouseClient_IsConnected_Statics::NewProp_ReturnValue_SetBit, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UVRMouseClient_IsConnected_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UVRMouseClient_IsConnected_Statics::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_UVRMouseClient_IsConnected_Statics::PropPointers) < 2048);
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UVRMouseClient_IsConnected_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UVRMouseClient, nullptr, "IsConnected", nullptr, nullptr, Z_Construct_UFunction_UVRMouseClient_IsConnected_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UVRMouseClient_IsConnected_Statics::PropPointers), sizeof(Z_Construct_UFunction_UVRMouseClient_IsConnected_Statics::VRMouseClient_eventIsConnected_Parms), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x54020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UVRMouseClient_IsConnected_Statics::Function_MetaDataParams), Z_Construct_UFunction_UVRMouseClient_IsConnected_Statics::Function_MetaDataParams) };
static_assert(sizeof(Z_Construct_UFunction_UVRMouseClient_IsConnected_Statics::VRMouseClient_eventIsConnected_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UVRMouseClient_IsConnected()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UVRMouseClient_IsConnected_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UVRMouseClient::execIsConnected)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	*(bool*)Z_Param__Result=P_THIS->IsConnected();
	P_NATIVE_END;
}
// End Class UVRMouseClient Function IsConnected

// Begin Class UVRMouseClient Function SendMouseButtonEvent
struct Z_Construct_UFunction_UVRMouseClient_SendMouseButtonEvent_Statics
{
	struct VRMouseClient_eventSendMouseButtonEvent_Parms
	{
		FString ButtonEvent;
		int32 X;
		int32 Y;
		bool ReturnValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "VR Mouse Client" },
		{ "ModuleRelativePath", "Public/VRMouseClientPlugin.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_ButtonEvent_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FStrPropertyParams NewProp_ButtonEvent;
	static const UECodeGen_Private::FIntPropertyParams NewProp_X;
	static const UECodeGen_Private::FIntPropertyParams NewProp_Y;
	static void NewProp_ReturnValue_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_ReturnValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FStrPropertyParams Z_Construct_UFunction_UVRMouseClient_SendMouseButtonEvent_Statics::NewProp_ButtonEvent = { "ButtonEvent", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(VRMouseClient_eventSendMouseButtonEvent_Parms, ButtonEvent), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_ButtonEvent_MetaData), NewProp_ButtonEvent_MetaData) };
const UECodeGen_Private::FIntPropertyParams Z_Construct_UFunction_UVRMouseClient_SendMouseButtonEvent_Statics::NewProp_X = { "X", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(VRMouseClient_eventSendMouseButtonEvent_Parms, X), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FIntPropertyParams Z_Construct_UFunction_UVRMouseClient_SendMouseButtonEvent_Statics::NewProp_Y = { "Y", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(VRMouseClient_eventSendMouseButtonEvent_Parms, Y), METADATA_PARAMS(0, nullptr) };
void Z_Construct_UFunction_UVRMouseClient_SendMouseButtonEvent_Statics::NewProp_ReturnValue_SetBit(void* Obj)
{
	((VRMouseClient_eventSendMouseButtonEvent_Parms*)Obj)->ReturnValue = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_UVRMouseClient_SendMouseButtonEvent_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(VRMouseClient_eventSendMouseButtonEvent_Parms), &Z_Construct_UFunction_UVRMouseClient_SendMouseButtonEvent_Statics::NewProp_ReturnValue_SetBit, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UVRMouseClient_SendMouseButtonEvent_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UVRMouseClient_SendMouseButtonEvent_Statics::NewProp_ButtonEvent,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UVRMouseClient_SendMouseButtonEvent_Statics::NewProp_X,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UVRMouseClient_SendMouseButtonEvent_Statics::NewProp_Y,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UVRMouseClient_SendMouseButtonEvent_Statics::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_UVRMouseClient_SendMouseButtonEvent_Statics::PropPointers) < 2048);
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UVRMouseClient_SendMouseButtonEvent_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UVRMouseClient, nullptr, "SendMouseButtonEvent", nullptr, nullptr, Z_Construct_UFunction_UVRMouseClient_SendMouseButtonEvent_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UVRMouseClient_SendMouseButtonEvent_Statics::PropPointers), sizeof(Z_Construct_UFunction_UVRMouseClient_SendMouseButtonEvent_Statics::VRMouseClient_eventSendMouseButtonEvent_Parms), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UVRMouseClient_SendMouseButtonEvent_Statics::Function_MetaDataParams), Z_Construct_UFunction_UVRMouseClient_SendMouseButtonEvent_Statics::Function_MetaDataParams) };
static_assert(sizeof(Z_Construct_UFunction_UVRMouseClient_SendMouseButtonEvent_Statics::VRMouseClient_eventSendMouseButtonEvent_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UVRMouseClient_SendMouseButtonEvent()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UVRMouseClient_SendMouseButtonEvent_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UVRMouseClient::execSendMouseButtonEvent)
{
	P_GET_PROPERTY(FStrProperty,Z_Param_ButtonEvent);
	P_GET_PROPERTY(FIntProperty,Z_Param_X);
	P_GET_PROPERTY(FIntProperty,Z_Param_Y);
	P_FINISH;
	P_NATIVE_BEGIN;
	*(bool*)Z_Param__Result=P_THIS->SendMouseButtonEvent(Z_Param_ButtonEvent,Z_Param_X,Z_Param_Y);
	P_NATIVE_END;
}
// End Class UVRMouseClient Function SendMouseButtonEvent

// Begin Class UVRMouseClient Function SendMouseClick
struct Z_Construct_UFunction_UVRMouseClient_SendMouseClick_Statics
{
	struct VRMouseClient_eventSendMouseClick_Parms
	{
		int32 X;
		int32 Y;
		bool ReturnValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "VR Mouse Client" },
		{ "ModuleRelativePath", "Public/VRMouseClientPlugin.h" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FIntPropertyParams NewProp_X;
	static const UECodeGen_Private::FIntPropertyParams NewProp_Y;
	static void NewProp_ReturnValue_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_ReturnValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FIntPropertyParams Z_Construct_UFunction_UVRMouseClient_SendMouseClick_Statics::NewProp_X = { "X", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(VRMouseClient_eventSendMouseClick_Parms, X), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FIntPropertyParams Z_Construct_UFunction_UVRMouseClient_SendMouseClick_Statics::NewProp_Y = { "Y", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(VRMouseClient_eventSendMouseClick_Parms, Y), METADATA_PARAMS(0, nullptr) };
void Z_Construct_UFunction_UVRMouseClient_SendMouseClick_Statics::NewProp_ReturnValue_SetBit(void* Obj)
{
	((VRMouseClient_eventSendMouseClick_Parms*)Obj)->ReturnValue = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_UVRMouseClient_SendMouseClick_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(VRMouseClient_eventSendMouseClick_Parms), &Z_Construct_UFunction_UVRMouseClient_SendMouseClick_Statics::NewProp_ReturnValue_SetBit, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UVRMouseClient_SendMouseClick_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UVRMouseClient_SendMouseClick_Statics::NewProp_X,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UVRMouseClient_SendMouseClick_Statics::NewProp_Y,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UVRMouseClient_SendMouseClick_Statics::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_UVRMouseClient_SendMouseClick_Statics::PropPointers) < 2048);
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UVRMouseClient_SendMouseClick_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UVRMouseClient, nullptr, "SendMouseClick", nullptr, nullptr, Z_Construct_UFunction_UVRMouseClient_SendMouseClick_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UVRMouseClient_SendMouseClick_Statics::PropPointers), sizeof(Z_Construct_UFunction_UVRMouseClient_SendMouseClick_Statics::VRMouseClient_eventSendMouseClick_Parms), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UVRMouseClient_SendMouseClick_Statics::Function_MetaDataParams), Z_Construct_UFunction_UVRMouseClient_SendMouseClick_Statics::Function_MetaDataParams) };
static_assert(sizeof(Z_Construct_UFunction_UVRMouseClient_SendMouseClick_Statics::VRMouseClient_eventSendMouseClick_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UVRMouseClient_SendMouseClick()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UVRMouseClient_SendMouseClick_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UVRMouseClient::execSendMouseClick)
{
	P_GET_PROPERTY(FIntProperty,Z_Param_X);
	P_GET_PROPERTY(FIntProperty,Z_Param_Y);
	P_FINISH;
	P_NATIVE_BEGIN;
	*(bool*)Z_Param__Result=P_THIS->SendMouseClick(Z_Param_X,Z_Param_Y);
	P_NATIVE_END;
}
// End Class UVRMouseClient Function SendMouseClick

// Begin Class UVRMouseClient Function SendMouseMove
struct Z_Construct_UFunction_UVRMouseClient_SendMouseMove_Statics
{
	struct VRMouseClient_eventSendMouseMove_Parms
	{
		int32 X;
		int32 Y;
		bool ReturnValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "VR Mouse Client" },
		{ "ModuleRelativePath", "Public/VRMouseClientPlugin.h" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FIntPropertyParams NewProp_X;
	static const UECodeGen_Private::FIntPropertyParams NewProp_Y;
	static void NewProp_ReturnValue_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_ReturnValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FIntPropertyParams Z_Construct_UFunction_UVRMouseClient_SendMouseMove_Statics::NewProp_X = { "X", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(VRMouseClient_eventSendMouseMove_Parms, X), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FIntPropertyParams Z_Construct_UFunction_UVRMouseClient_SendMouseMove_Statics::NewProp_Y = { "Y", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(VRMouseClient_eventSendMouseMove_Parms, Y), METADATA_PARAMS(0, nullptr) };
void Z_Construct_UFunction_UVRMouseClient_SendMouseMove_Statics::NewProp_ReturnValue_SetBit(void* Obj)
{
	((VRMouseClient_eventSendMouseMove_Parms*)Obj)->ReturnValue = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_UVRMouseClient_SendMouseMove_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(VRMouseClient_eventSendMouseMove_Parms), &Z_Construct_UFunction_UVRMouseClient_SendMouseMove_Statics::NewProp_ReturnValue_SetBit, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UVRMouseClient_SendMouseMove_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UVRMouseClient_SendMouseMove_Statics::NewProp_X,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UVRMouseClient_SendMouseMove_Statics::NewProp_Y,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UVRMouseClient_SendMouseMove_Statics::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_UVRMouseClient_SendMouseMove_Statics::PropPointers) < 2048);
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UVRMouseClient_SendMouseMove_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UVRMouseClient, nullptr, "SendMouseMove", nullptr, nullptr, Z_Construct_UFunction_UVRMouseClient_SendMouseMove_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UVRMouseClient_SendMouseMove_Statics::PropPointers), sizeof(Z_Construct_UFunction_UVRMouseClient_SendMouseMove_Statics::VRMouseClient_eventSendMouseMove_Parms), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UVRMouseClient_SendMouseMove_Statics::Function_MetaDataParams), Z_Construct_UFunction_UVRMouseClient_SendMouseMove_Statics::Function_MetaDataParams) };
static_assert(sizeof(Z_Construct_UFunction_UVRMouseClient_SendMouseMove_Statics::VRMouseClient_eventSendMouseMove_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UVRMouseClient_SendMouseMove()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UVRMouseClient_SendMouseMove_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UVRMouseClient::execSendMouseMove)
{
	P_GET_PROPERTY(FIntProperty,Z_Param_X);
	P_GET_PROPERTY(FIntProperty,Z_Param_Y);
	P_FINISH;
	P_NATIVE_BEGIN;
	*(bool*)Z_Param__Result=P_THIS->SendMouseMove(Z_Param_X,Z_Param_Y);
	P_NATIVE_END;
}
// End Class UVRMouseClient Function SendMouseMove

// Begin Class UVRMouseClient Function SendWorldClickEvent
struct Z_Construct_UFunction_UVRMouseClient_SendWorldClickEvent_Statics
{
	struct VRMouseClient_eventSendWorldClickEvent_Parms
	{
		FString EventType;
		float X;
		float Y;
		float Z;
		bool ReturnValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "VR Mouse Client" },
		{ "ModuleRelativePath", "Public/VRMouseClientPlugin.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_EventType_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FStrPropertyParams NewProp_EventType;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_X;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_Y;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_Z;
	static void NewProp_ReturnValue_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_ReturnValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FStrPropertyParams Z_Construct_UFunction_UVRMouseClient_SendWorldClickEvent_Statics::NewProp_EventType = { "EventType", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(VRMouseClient_eventSendWorldClickEvent_Parms, EventType), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_EventType_MetaData), NewProp_EventType_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UFunction_UVRMouseClient_SendWorldClickEvent_Statics::NewProp_X = { "X", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(VRMouseClient_eventSendWorldClickEvent_Parms, X), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UFunction_UVRMouseClient_SendWorldClickEvent_Statics::NewProp_Y = { "Y", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(VRMouseClient_eventSendWorldClickEvent_Parms, Y), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UFunction_UVRMouseClient_SendWorldClickEvent_Statics::NewProp_Z = { "Z", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(VRMouseClient_eventSendWorldClickEvent_Parms, Z), METADATA_PARAMS(0, nullptr) };
void Z_Construct_UFunction_UVRMouseClient_SendWorldClickEvent_Statics::NewProp_ReturnValue_SetBit(void* Obj)
{
	((VRMouseClient_eventSendWorldClickEvent_Parms*)Obj)->ReturnValue = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_UVRMouseClient_SendWorldClickEvent_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(VRMouseClient_eventSendWorldClickEvent_Parms), &Z_Construct_UFunction_UVRMouseClient_SendWorldClickEvent_Statics::NewProp_ReturnValue_SetBit, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UVRMouseClient_SendWorldClickEvent_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UVRMouseClient_SendWorldClickEvent_Statics::NewProp_EventType,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UVRMouseClient_SendWorldClickEvent_Statics::NewProp_X,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UVRMouseClient_SendWorldClickEvent_Statics::NewProp_Y,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UVRMouseClient_SendWorldClickEvent_Statics::NewProp_Z,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UVRMouseClient_SendWorldClickEvent_Statics::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_UVRMouseClient_SendWorldClickEvent_Statics::PropPointers) < 2048);
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UVRMouseClient_SendWorldClickEvent_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UVRMouseClient, nullptr, "SendWorldClickEvent", nullptr, nullptr, Z_Construct_UFunction_UVRMouseClient_SendWorldClickEvent_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UVRMouseClient_SendWorldClickEvent_Statics::PropPointers), sizeof(Z_Construct_UFunction_UVRMouseClient_SendWorldClickEvent_Statics::VRMouseClient_eventSendWorldClickEvent_Parms), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UVRMouseClient_SendWorldClickEvent_Statics::Function_MetaDataParams), Z_Construct_UFunction_UVRMouseClient_SendWorldClickEvent_Statics::Function_MetaDataParams) };
static_assert(sizeof(Z_Construct_UFunction_UVRMouseClient_SendWorldClickEvent_Statics::VRMouseClient_eventSendWorldClickEvent_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UVRMouseClient_SendWorldClickEvent()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UVRMouseClient_SendWorldClickEvent_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UVRMouseClient::execSendWorldClickEvent)
{
	P_GET_PROPERTY(FStrProperty,Z_Param_EventType);
	P_GET_PROPERTY(FFloatProperty,Z_Param_X);
	P_GET_PROPERTY(FFloatProperty,Z_Param_Y);
	P_GET_PROPERTY(FFloatProperty,Z_Param_Z);
	P_FINISH;
	P_NATIVE_BEGIN;
	*(bool*)Z_Param__Result=P_THIS->SendWorldClickEvent(Z_Param_EventType,Z_Param_X,Z_Param_Y,Z_Param_Z);
	P_NATIVE_END;
}
// End Class UVRMouseClient Function SendWorldClickEvent

// Begin Class UVRMouseClient
void UVRMouseClient::StaticRegisterNativesUVRMouseClient()
{
	UClass* Class = UVRMouseClient::StaticClass();
	static const FNameNativePtrPair Funcs[] = {
		{ "Connect", &UVRMouseClient::execConnect },
		{ "Disconnect", &UVRMouseClient::execDisconnect },
		{ "IsConnected", &UVRMouseClient::execIsConnected },
		{ "SendMouseButtonEvent", &UVRMouseClient::execSendMouseButtonEvent },
		{ "SendMouseClick", &UVRMouseClient::execSendMouseClick },
		{ "SendMouseMove", &UVRMouseClient::execSendMouseMove },
		{ "SendWorldClickEvent", &UVRMouseClient::execSendWorldClickEvent },
	};
	FNativeFunctionRegistrar::RegisterFunctions(Class, Funcs, UE_ARRAY_COUNT(Funcs));
}
IMPLEMENT_CLASS_NO_AUTO_REGISTRATION(UVRMouseClient);
UClass* Z_Construct_UClass_UVRMouseClient_NoRegister()
{
	return UVRMouseClient::StaticClass();
}
struct Z_Construct_UClass_UVRMouseClient_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[] = {
		{ "BlueprintType", "true" },
		{ "IncludePath", "VRMouseClientPlugin.h" },
		{ "IsBlueprintBase", "true" },
		{ "ModuleRelativePath", "Public/VRMouseClientPlugin.h" },
	};
#endif // WITH_METADATA
	static UObject* (*const DependentSingletons[])();
	static constexpr FClassFunctionLinkInfo FuncInfo[] = {
		{ &Z_Construct_UFunction_UVRMouseClient_Connect, "Connect" }, // 819433690
		{ &Z_Construct_UFunction_UVRMouseClient_Disconnect, "Disconnect" }, // 1420720780
		{ &Z_Construct_UFunction_UVRMouseClient_IsConnected, "IsConnected" }, // 1232889255
		{ &Z_Construct_UFunction_UVRMouseClient_SendMouseButtonEvent, "SendMouseButtonEvent" }, // 57742257
		{ &Z_Construct_UFunction_UVRMouseClient_SendMouseClick, "SendMouseClick" }, // 2589058719
		{ &Z_Construct_UFunction_UVRMouseClient_SendMouseMove, "SendMouseMove" }, // 336971753
		{ &Z_Construct_UFunction_UVRMouseClient_SendWorldClickEvent, "SendWorldClickEvent" }, // 2406974243
	};
	static_assert(UE_ARRAY_COUNT(FuncInfo) < 2048);
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UVRMouseClient>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
};
UObject* (*const Z_Construct_UClass_UVRMouseClient_Statics::DependentSingletons[])() = {
	(UObject* (*)())Z_Construct_UClass_UObject,
	(UObject* (*)())Z_Construct_UPackage__Script_VRMouseClient,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_UVRMouseClient_Statics::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams Z_Construct_UClass_UVRMouseClient_Statics::ClassParams = {
	&UVRMouseClient::StaticClass,
	nullptr,
	&StaticCppClassTypeInfo,
	DependentSingletons,
	FuncInfo,
	nullptr,
	nullptr,
	UE_ARRAY_COUNT(DependentSingletons),
	UE_ARRAY_COUNT(FuncInfo),
	0,
	0,
	0x000000A0u,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_UVRMouseClient_Statics::Class_MetaDataParams), Z_Construct_UClass_UVRMouseClient_Statics::Class_MetaDataParams)
};
UClass* Z_Construct_UClass_UVRMouseClient()
{
	if (!Z_Registration_Info_UClass_UVRMouseClient.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_UVRMouseClient.OuterSingleton, Z_Construct_UClass_UVRMouseClient_Statics::ClassParams);
	}
	return Z_Registration_Info_UClass_UVRMouseClient.OuterSingleton;
}
template<> VRMOUSECLIENT_API UClass* StaticClass<UVRMouseClient>()
{
	return UVRMouseClient::StaticClass();
}
DEFINE_VTABLE_PTR_HELPER_CTOR(UVRMouseClient);
UVRMouseClient::~UVRMouseClient() {}
// End Class UVRMouseClient

// Begin Registration
struct Z_CompiledInDeferFile_FID_VRMouseClientProject_Plugins_VRMouseClient_Source_VRMouseClient_Public_VRMouseClientPlugin_h_Statics
{
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_UVRMouseClient, UVRMouseClient::StaticClass, TEXT("UVRMouseClient"), &Z_Registration_Info_UClass_UVRMouseClient, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(UVRMouseClient), 400527208U) },
	};
};
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_VRMouseClientProject_Plugins_VRMouseClient_Source_VRMouseClient_Public_VRMouseClientPlugin_h_883912354(TEXT("/Script/VRMouseClient"),
	Z_CompiledInDeferFile_FID_VRMouseClientProject_Plugins_VRMouseClient_Source_VRMouseClient_Public_VRMouseClientPlugin_h_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_VRMouseClientProject_Plugins_VRMouseClient_Source_VRMouseClient_Public_VRMouseClientPlugin_h_Statics::ClassInfo),
	nullptr, 0,
	nullptr, 0);
// End Registration
PRAGMA_ENABLE_DEPRECATION_WARNINGS
