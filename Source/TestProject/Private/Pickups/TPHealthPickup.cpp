// Slava Ukraine

#include "Pickups/TPHealthPickup.h"
#include "Character/TPCharacter.h"
#include "Components/TPHealthComponent.h"
#include "Kismet/GameplayStatics.h"
#include "TPGameModeBase.h"

ATPHealthPickup::ATPHealthPickup()
{
    MakePickupUnreachable();
}

void ATPHealthPickup::NotifyActorBeginOverlap(AActor* OtherActor)
{
    Super::NotifyActorBeginOverlap(OtherActor);

    HealingPlayer(OtherActor);

    MakePickupUnreachable();

    MakeReachableRandomHealthPickup();
}

void ATPHealthPickup::MakeReachableRandomHealthPickup()
{
    ATPGameModeBase* GameMode = Cast<ATPGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));
    if (!GameMode)
    {
        return;
    }

    GameMode->HealthPickupsRespawn();
}

void ATPHealthPickup::HealingPlayer(AActor* Actor)
{
    ATPCharacter* Player = Cast<ATPCharacter>(Actor);
    if (!Player)
    {
        return;
    }
    UTPHealthComponent* HealthComponent =
        Cast<UTPHealthComponent>(Player->GetComponentByClass(UTPHealthComponent::StaticClass()));
    if (!HealthComponent)
    {
        return;
    }

    HealthComponent->SetHealth(HealthComponent->GetHealth() + HealingAmount);
}
