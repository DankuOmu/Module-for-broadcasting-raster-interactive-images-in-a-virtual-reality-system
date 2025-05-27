// VRMouseClientPlugin.cpp
#include "VRMouseClientPlugin.h"
#include "VRMouseClient.h"

#include <thread>

IMPLEMENT_MODULE(FVRMouseClientPluginModule, VRMouseClientPlugin)

float UVRMouseClient::LastUpdate = 0;


void FVRMouseClientPluginModule::StartupModule()
{
    // Èíèöèàëèçàöèÿ ìîäóëÿ
}

void FVRMouseClientPluginModule::ShutdownModule()
{
    // Î÷èñòêà ìîäóëÿ
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


void update(VRMouseClient* NativeClient, float DeltaTime) {
    return;
}

void UVRMouseClient::Tick(float DeltaTime)
{
    if (NativeClient->Translator and UVRMouseClient::LastUpdate >= 0.01f) {
        NativeClient->Translator->UpdateTexture(NativeClient->RecieveData());
        UVRMouseClient::LastUpdate = 0;
        return;
    }
    UVRMouseClient::LastUpdate += DeltaTime;
}

TStatId UVRMouseClient::GetStatId() const
{
    return TStatId();
}

