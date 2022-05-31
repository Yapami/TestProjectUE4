// Slava Ukraine

#include "Components/TPHealthComponent.h"
#include "TPGameModeBase.h"
#include "STUCoreTypes.h"

// Sets default values
UTPHealthComponent::UTPHealthComponent()
{
    PrimaryComponentTick.bCanEverTick = false;
    check(MaxHealth > 0);
    Health = MaxHealth;
}

float UTPHealthComponent::GetHealth() const
{
    return Health;
}

float UTPHealthComponent::GeteHealthPercent() const
{
    return Health / MaxHealth;
}

void UTPHealthComponent::OnTakeAnyDamage(AActor* DamagedActor, float Damage,
                                                 const UDamageType* DamageType,
                                                 AController* InstigatedBy, AActor* DamageCauser)
{
    SetHealth(Health - Damage);
}

void UTPHealthComponent::SetHealth(float NewHealth)
{
    Health = FMath::Clamp(NewHealth, 0.0f, MaxHealth);
    if (IsPlayerDead())
    {
        OnPlayerDead();
    }
}

void UTPHealthComponent::OnPlayerDead()
{
    ATPGameModeBase* GameMode = CastChecked<ATPGameModeBase>( GetWorld()->GetAuthGameMode());
    GameMode->OnChangeGameState.Broadcast(EGameState::PlayerIsDead);
    PlayerDead.Broadcast(); //TO DO
}

bool UTPHealthComponent::IsPlayerDead()
{
    return Health <= 0;
}