// Slava Ukraine

#include "Pickups/TPBasePickup.h"
#include "Components/SceneComponent.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
ATPBasePickup::ATPBasePickup()
{
    // Set this actor to call Tick() every frame.  You can turn this off to improve performance if
    // you don't need it.
    PrimaryActorTick.bCanEverTick = false;

    SceneComponent = CreateDefaultSubobject<USceneComponent>("SceneComponent");
    check(SceneComponent);
    SetRootComponent(SceneComponent);

    StandMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>("StandMeshComponent");
    check(StandMeshComponent);
    StandMeshComponent->SetupAttachment(GetRootComponent());

    MainMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>("MainMeshComponent");
    check(MainMeshComponent);
    MainMeshComponent->SetupAttachment(GetRootComponent());

    MakePickupReachable();
}

void ATPBasePickup::MakePickupReachable()
{
    MainMeshComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);
    MainMeshComponent->SetVisibility(true, true);
}

void ATPBasePickup::MakePickupUnreachable()
{
    MainMeshComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
    MainMeshComponent->SetVisibility(false, true);
}

bool ATPBasePickup::IsPickupReachable()
{
    return MainMeshComponent->GetVisibleFlag() &&
           MainMeshComponent->GetCollisionResponseToChannels() == ECollisionResponse::ECR_Overlap;
}
