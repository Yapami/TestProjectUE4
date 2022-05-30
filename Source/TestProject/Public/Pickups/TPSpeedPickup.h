// Slava Ukraine

#pragma once

#include "Components/SphereComponent.h"
#include "CoreMinimal.h"
#include "Pickups/TPBasePickup.h"
#include "TPSpeedPickup.generated.h"

class UTextRenderComponent;

/**
 *
 */
UCLASS()
class TESTPROJECT_API ATPSpeedPickup : public ATPBasePickup
{
    GENERATED_BODY()
    ATPSpeedPickup();

protected:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SpeedPickup")
    UStaticMeshComponent* SpeedPickup;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SpeedPickup")
    UTextRenderComponent* TextComponent;

    FTimerHandle RespawnTimer;

    FTimerHandle RespawnTimeTimer;

    void ShowTimeToRespawn();

    int32 TimeLeftToRespawn = 0;

    virtual void Tick(float DeltaTime) override;

public:
    virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;
};
