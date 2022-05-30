// Slava Ukraine

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PainCausingVolume.h"
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
    ATPPainCausingVolume();

protected:
    virtual void BeginPlay() override;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PainVolume")
    USceneComponent* SceneComponent;

    UBoxComponent* CollisionComponent;

    FTimerHandle IncreaseDamage;
    FTimerHandle TimeSinceGameStart;

    float DamagePerSec = 1.0f;

public:
    UFUNCTION()
    void FinishTimers();

private:
    void ApplyPainVolume();
};
