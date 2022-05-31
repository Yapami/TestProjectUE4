// Slava Ukraine

#pragma once

#include "CoreMinimal.h"
#include "Pickups/TPBasePickup.h"
#include "TPHealthPickup.generated.h"

/**
 *
 */
UCLASS()
class TESTPROJECT_API ATPHealthPickup : public ATPBasePickup
{
    GENERATED_BODY()
public:
    ATPHealthPickup();

protected:
    virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "HealthPickup")
    float HealingAmount = 30.0f;

private:

    void MakeReachableRandomHealthPickup();

    void HealingPlayer(AActor* Actor);
};
