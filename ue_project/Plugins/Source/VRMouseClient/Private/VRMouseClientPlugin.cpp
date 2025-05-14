// VRMouseClientPlugin.cpp
#include "VRMouseClientPlugin.h"
#include "VRMouseClient.h"

IMPLEMENT_MODULE(FVRMouseClientPluginModule, VRMouseClientPlugin)

void FVRMouseClientPluginModule::StartupModule()
{
    // Инициализация модуля
}

void FVRMouseClientPluginModule::ShutdownModule()
{
    // Очистка модуля
}

UVRMouseClient::UVRMouseClient()
{
    NativeClient = new VRMouseClient(this);
}

bool UVRMouseClient::Connect(const FString& Host, int32 Port)
{
    return NativeClient->Connect(TCHAR_TO_UTF8(*Host), Port);
}

bool UVRMouseClient::SendMouseClick(int32 X, int32 Y)
{
    return NativeClient->SendMouseEvent("click", X, Y);
}

bool UVRMouseClient::SendMouseMove(int32 X, int32 Y)
{
    return NativeClient->SendMouseEvent("move", X, Y);
}

void UVRMouseClient::Disconnect()
{
    NativeClient->Disconnect();
}

bool UVRMouseClient::IsConnected() const
{
    return NativeClient->IsConnected();
}

bool UVRMouseClient::SendMouseButtonEvent(const FString& ButtonEvent, int32 X, int32 Y)
{
    return NativeClient->SendMouseEvent(TCHAR_TO_UTF8(*ButtonEvent), X, Y);
}