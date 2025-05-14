#include "MouseForwardingWidget.h"
#include "Components/TextBlock.h"


void UMouseForwardingWidget::NativeConstruct()
{
    Super::NativeConstruct();

    if (VRMouseClientRef)
    {
        VRMouseClientRef->Connect(TEXT("127.0.0.1"), 12345); // Порт и адрес сервера
    }
}


FReply UMouseForwardingWidget::NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
    if (VRMouseClientRef && VRMouseClientRef->IsConnected())
    {
        FVector2D Pos = InMouseEvent.GetScreenSpacePosition();
        FString Type = InMouseEvent.GetEffectingButton() == EKeys::LeftMouseButton ? "left_down" : "right_down";
        VRMouseClientRef->SendMouseButtonEvent(Type, Pos.X, Pos.Y);
    }
    return Super::NativeOnMouseButtonDown(InGeometry, InMouseEvent);
}

FReply UMouseForwardingWidget::NativeOnMouseButtonUp(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
    if (VRMouseClientRef && VRMouseClientRef->IsConnected())
    {
        FVector2D Pos = InMouseEvent.GetScreenSpacePosition();
        FString Type = InMouseEvent.GetEffectingButton() == EKeys::LeftMouseButton ? "left_up" : "right_up";
        VRMouseClientRef->SendMouseButtonEvent(Type, Pos.X, Pos.Y);
    }
    return Super::NativeOnMouseButtonUp(InGeometry, InMouseEvent);
}