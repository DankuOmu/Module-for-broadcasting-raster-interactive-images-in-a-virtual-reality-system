#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "VRMouseClient.h"
#include "VRMouseClientPlugin.h"
#include "MouseForwardingWidget.generated.h"


UCLASS()
class VRMOUSECLIENT_API UMouseForwardingWidget : public UUserWidget
{
    GENERATED_BODY()

public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "VR Mouse")
    UVRMouseClient* VRMouseClientRef;

protected:
    virtual FReply NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;
    virtual FReply NativeOnMouseButtonUp(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;
    virtual void NativeConstruct() override;
};