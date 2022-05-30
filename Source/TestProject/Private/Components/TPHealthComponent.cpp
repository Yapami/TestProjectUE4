// Slava Ukraine

#include "Components/TPHealthComponent.h"
#include "TPGameModeBase.h"
#include "STUCoreTypes.h"

// Sets default values
UTPHealthComponent::UTPHealthComponent()
{
    // Set this actor to call Tick() every frame.  You can turn this off to improve performance if
    // you don't need it.
    check(MaxHealth > 0);
    Health = MaxHealth;
}

// Called when the game starts
void UTPHealthComponent::BeginPlay()
{
    Super::BeginPlay();
}

float UTPHealthComponent::GetHealth()
{
    return Health;
}

float UTPHealthComponent::GeteHealthPercent() const
{
    return Health / MaxHealth;
}

void UTPHealthComponent::OnTakeAnyDamageFunction(AActor* DamagedActor, float Damage,
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
    PlayerDead.Broadcast();
}

bool UTPHealthComponent::IsPlayerDead()
{
    return Health <= 0;
}

// Called every frame
void UTPHealthComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                       FActorComponentTickFunction* ThisTickFunction)
{
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

    // ...
}
