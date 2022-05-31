// Slava Ukraine

#include "UI/TPPlayerHUDWidget.h"
#include "Components/TPHealthComponent.h"
#include "TPGameModeBase.h"
#include "TPUtils.h"

float UTPPlayerHUDWidget::GetHealthPercent() const
{
    const auto Player = GetOwningPlayerPawn();
    if (!Player)
    {
        return 0.f;
    }

    return Cast<UTPHealthComponent>(Player->GetComponentByClass(UTPHealthComponent::StaticClass()))
        ->GeteHealthPercent();
}

FString UTPPlayerHUDWidget::GetTimeSinceStartGame() const
{
    return TPUtils::IntToTime(TimeSinceGameStart);
}

void UTPPlayerHUDWidget::SetTimeSinceGameStart(float Time)
{
    TimeSinceGameStart = static_cast<int32>(Time);
}
