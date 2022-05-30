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
    ATPHealthPickup();

public:
    UFUNCTION(BlueprintCallable)
    void PickupRespawn();
    bool IsPickupReachable();

protected:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "HealthCrossPickup")
    UStaticMeshComponent* HealthCrossPickup;
    virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;
};
