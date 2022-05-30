// Slava Ukraine

#include "Pickups/TPHealthPickup.h"
#include "Character/TPCharacter.h"
#include "Components/TPHealthComponent.h"
#include "Kismet/GameplayStatics.h"
#include "TPGameModeBase.h"

ATPHealthPickup::ATPHealthPickup()
{
    HealthCrossPickup = CreateDefaultSubobject<UStaticMeshComponent>("HealthCross");
    HealthCrossPickup->SetupAttachment(GetRootComponent());

    HealthCrossPickup->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
    HealthCrossPickup->SetVisibility(false, true);
}

void ATPHealthPickup::NotifyActorBeginOverlap(AActor* OtherActor)
{
    Super::NotifyActorBeginOverlap(OtherActor);

    ATPCharacter* Player = Cast<ATPCharacter>(OtherActor);
    if (!Player)
    {
        return;
    }
    UTPHealthComponent* HealthComponent =
        Cast<UTPHealthComponent>(Player->GetComponentByClass(UTPHealthComponent::StaticClass()));
    if (HealthComponent)
    {
        HealthComponent->SetHealth(HealthComponent->GetHealth() + 30);
    }

    HealthCrossPickup->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
    HealthCrossPickup->SetVisibility(false, true);

    ATPGameModeBase* GameMode = Cast<ATPGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));
    if (GameMode)
    {
        GameMode->HealthPickupsRespawn();
    }
}

bool ATPHealthPickup::IsPickupReachable()
{
    return HealthCrossPickup->GetVisibleFlag() &&
           HealthCrossPickup->GetCollisionResponseToChannels() == ECollisionResponse::ECR_Overlap;
}

void ATPHealthPickup::PickupRespawn()
{
    HealthCrossPickup->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);
    HealthCrossPickup->SetVisibility(true, true);
}
