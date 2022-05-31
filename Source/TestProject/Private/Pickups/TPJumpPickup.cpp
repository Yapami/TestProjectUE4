// Slava Ukraine

#include "Pickups/TPJumpPickup.h"
#include "Character/TPCharacter.h"

void ATPJumpPickup::NotifyActorBeginOverlap(AActor* OtherActor)
{
    Super::NotifyActorBeginOverlap(OtherActor);

    ATPCharacter* Player = Cast<ATPCharacter>(OtherActor);
    check(Player);
    Player->LaunchCharacter(Player->GetActorUpVector() * JumpHeight,
                            false, false);
}
