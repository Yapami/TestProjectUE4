// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Pickups/TPHealthPickup.h"
#include "STUCoreTypes.h"
#include "TPGameModeBase.generated.h"

class UTPSaveGame;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FUpdateGameTimeSignature, float, Time);

/**
 *
 */
UCLASS()
class TESTPROJECT_API ATPGameModeBase : public AGameModeBase
{
    GENERATED_BODY()

    ATPGameModeBase();

public:
    void HealthPickupsRespawn();

    void SetupPlayerLifeTimer();

    void DestroyPlayerLifeTimer();

    FTimerHandle PlayerLifeTimer;

    FGameStateSignature OnChangeGameState;

protected:
    virtual void BeginPlay() override;

    TArray<AActor*> HealthPickups;

    bool IsAnyHealthPickupReachable();

    FUpdateGameTimeSignature UpdateGameTimeDelegate;

    void UpdateGameTime();

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
    float TimerRate = 1.0f;

private:
    float TimerRemaining = 0;

    UFUNCTION()
    void FinishGame();
};
