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
    ATPJumpPickup();

protected:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "JumppadPickup")
    UStaticMeshComponent* JumppadPickup;

public:
    virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;
};
