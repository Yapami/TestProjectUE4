// Slava Ukraine

#include "UI/TPPlayerHUDWidget.h"
#include "Components/TPHealthComponent.h"
#include "TPGameModeBase.h"

float UTPPlayerHUDWidget::GetHealthPercent() const
{
    const auto Player = GetOwningPlayerPawn();
    if (!Player)
        return 0.f;
    const auto a = Player->GetComponentByClass(UTPHealthComponent::StaticClass());
    return Cast<UTPHealthComponent>(a)->GeteHealthPercent();
}

FString UTPPlayerHUDWidget::GetTimeSinceStartGame() const
{
    return "0" + FString::FromInt(TimeSinceGameStart / 60) + ":" +
           ((TimeSinceGameStart % 60) < 10 ? "0" : "") + FString::FromInt(TimeSinceGameStart % 60);
}

void UTPPlayerHUDWidget::SetTimeSinceGameStart(float Time)
{
    TimeSinceGameStart = static_cast<int32>(Time);
}

