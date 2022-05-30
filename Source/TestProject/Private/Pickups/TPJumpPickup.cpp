// Slava Ukraine

#include "Pickups/TPJumpPickup.h"
#include "Character/TPCharacter.h"

ATPJumpPickup::ATPJumpPickup()
{
    JumppadPickup = CreateDefaultSubobject<UStaticMeshComponent>("JumppadPickup");
    JumppadPickup->SetupAttachment(GetRootComponent());
}

void ATPJumpPickup::NotifyActorBeginOverlap(AActor* OtherActor)
{
    Super::NotifyActorBeginOverlap(OtherActor);
    ATPCharacter* Player = Cast<ATPCharacter>(OtherActor);
    if (!Player)
    {
        return;
    }
    Player->LaunchCharacter(Player->GetActorUpVector() * 1025,
                            false, false);
}
