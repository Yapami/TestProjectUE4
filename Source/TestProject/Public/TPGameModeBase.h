// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Pickups/TPHealthPickup.h"
#include "STUCoreTypes.h"
#include "TPGameModeBase.generated.h"

class UTPSaveGame;

/**
 *
 */
UCLASS()
class TESTPROJECT_API ATPGameModeBase : public AGameModeBase
{
    GENERATED_BODY()

public:
    ATPGameModeBase();

    FTimerHandle PlayerLifeTimer;

    FGameStateSignature OnChangeGameState;

    void HealthPickupsRespawn();

    void SetupGameStatePlayerAlive();

    void DestroyPlayerLifeTimer();

protected:
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
    float TimerRate = 1.0f;

    FUpdateGameTimeSignature UpdateGameTimeDelegate;

    TArray<AActor*> HealthPickups;

    virtual void BeginPlay() override;

    bool IsAnyHealthPickupReachable();

    void UpdateGameTime();

private:
    float TimerRemaining = 0;

    UFUNCTION()
    void ChangeGameState(EGameState State);

    void SaveResult();
};
