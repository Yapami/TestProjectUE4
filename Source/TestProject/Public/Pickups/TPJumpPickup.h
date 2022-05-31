// Slava Ukraine

#pragma once

#include "CoreMinimal.h"
#include "Pickups/TPBasePickup.h"
#include "TPJumpPickup.generated.h"
/**
 *
 */
UCLASS()
class TESTPROJECT_API ATPJumpPickup : public ATPBasePickup
{
    GENERATED_BODY()

public:
    virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;

protected:
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "JumpPad")
    int32 JumpHeight = 1035;
};
