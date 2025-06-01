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

        FDateTime Now = FDateTime::UtcNow();
        int64 TimestampMs = Now.ToUnixTimestamp() * 1000 + Now.GetMillisecond();
        UE_LOG(LogTemp, Log, TEXT("Mouse down [%s] at (%f, %f) — %lld ms"), *Type, Pos.X, Pos.Y, TimestampMs);

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