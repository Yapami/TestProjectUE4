// Slava Ukraine

#pragma once

#include "CoreMinimal.h"
#include "STUCoreTypes.h"
#include "TPPainCausingVolume.generated.h"

class USceneComponent;
class UBoxComponent;

/**
 *
 */
UCLASS()
class TESTPROJECT_API ATPPainCausingVolume : public AActor
{
    GENERATED_BODY()

public:
    ATPPainCausingVolume();

    UFUNCTION()
    void ApplyDamageSwitcher(EGameState GameState);

protected:
    virtual void BeginPlay() override;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "PainVolume")
    float DamageTimerFrequancy = 1.0f;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "PainVolume")
    float DamagePerSec = 1.0f;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "PainVolume")
    float TimerTicksPerSecond = 10.0f;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "PainVolume")
    float DamageMultiplier = 1.1f;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "PainVolume")
    float IncreaseDamageFrequancy = 5.0;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PainVolume")
    USceneComponent* SceneComponent;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PainVolume")
    UBoxComponent* CollisionComponent;

    FTimerHandle ApplyDamageEverySecondTimer;

private:
    void ApplyPainVolume();
};
