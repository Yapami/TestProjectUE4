// Slava Ukraine

#include "Pickups/TPBasePickup.h"

// Sets default values
ATPBasePickup::ATPBasePickup()
{
    // Set this actor to call Tick() every frame.  You can turn this off to improve performance if
    // you don't need it.
    PrimaryActorTick.bCanEverTick = true;
    StandMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>("StandMeshComponent");
    SceneComponent = CreateDefaultSubobject<USceneComponent>("SceneComponent");
    SetRootComponent(SceneComponent);
    StandMeshComponent->SetupAttachment(GetRootComponent());
}

// Called when the game starts or when spawned
void ATPBasePickup::BeginPlay()
{
    Super::BeginPlay();
}

// Called every frame
void ATPBasePickup::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}
