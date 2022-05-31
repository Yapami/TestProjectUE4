// Slava Ukraine

#pragma once

#include "CoreMinimal.h"
#include "Pickups/TPBasePickup.h"
#include "STUCoreTypes.h"
#include "TPSpeedPickup.generated.h"

class UTextRenderComponent;

UCLASS()
class TESTPROJECT_API ATPSpeedPickup : public ATPBasePickup
{
    GENERATED_BODY()

public:
    ATPSpeedPickup();

    virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;

    UFUNCTION()
    void ChangeGameState(EGameState GameState);

protected:
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "SpeedPickup")
    UStaticMeshComponent* SpeedPickup;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "SpeedPickup")
    UTextRenderComponent* TextComponent;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "SpeedPickup")
    float SpeedMultiplier = 1.5f;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "SpeedPickup")
    float HighSpeedDuration = 5.0f;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "SpeedPickup")
    float TimeToSpeedPickupRespawn = 15.0f;

    virtual void BeginPlay() override;

    FTimerHandle RespawnTimer;

    FTimerHandle RespawnTimeTimer;

    FTimerHandle SetNormalSpeedTimer;

    void ShowTimeToRespawn();

    virtual void Tick(float DeltaTime) override;

private:
    int32 TimeLeftToRespawn = 0;

    void PickupRespawnTimerStart();

    void FinishAllTimers();

    void ChangePlayerSpeed(AActor* Actor);
};
