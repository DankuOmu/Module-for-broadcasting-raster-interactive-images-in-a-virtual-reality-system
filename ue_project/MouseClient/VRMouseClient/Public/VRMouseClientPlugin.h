#pragma once
// VRMouseClientPlugin.h
#pragma once

#include "CoreMinimal.h"
#include "Modules/ModuleManager.h"
#include <iostream>
#include "VRMouseClientPlugin.generated.h"

class FVRMouseClientPluginModule : public IModuleInterface
{
public:
    virtual void StartupModule() override;
    virtual void ShutdownModule() override;
};

UCLASS(Blueprintable)
class UVRMouseClient : public UObject
{
    GENERATED_BODY()

public:
    UVRMouseClient();

    UFUNCTION(BlueprintCallable, Category = "VR Mouse Client")
    bool SendMouseButtonEvent(const FString& ButtonEvent, int32 X, int32 Y);

    UFUNCTION(BlueprintCallable, Category = "VR Mouse Client")
    bool Connect(const FString& Host, int32 Port);

    UFUNCTION(BlueprintCallable, Category = "VR Mouse Client")
    bool SendMouseClick(int32 X, int32 Y);

    UFUNCTION(BlueprintCallable, Category = "VR Mouse Client")
    bool SendMouseMove(int32 X, int32 Y);

    UFUNCTION(BlueprintCallable, Category = "VR Mouse Client")
    void Disconnect();

    UFUNCTION(BlueprintCallable, Category = "VR Mouse Client")
    bool IsConnected() const;

private:
    class VRMouseClient* NativeClient;
};