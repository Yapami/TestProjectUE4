// Fill out your copyright notice in the Description page of Project Settings.

#include "TPGameModeBase.h"
#include "Character/TPCharacter.h"
#include "Character/TPPlayerController.h"
#include "Components/TPHealthComponent.h"
#include "Kismet/GameplayStatics.h"
#include "SaveSystem/TPSaveGame.h"
#include "UI/TPPlayerHUD.h"
#include "UI/TPPlayerHUDWidget.h"

ATPGameModeBase::ATPGameModeBase()
{
    DefaultPawnClass = ATPCharacter::StaticClass();
    PlayerControllerClass = ATPPlayerController::StaticClass();
    HUDClass = ATPPlayerHUD::StaticClass();
}

void ATPGameModeBase::BeginPlay()
{
    Super::BeginPlay();
    UGameplayStatics::GetAllActorsOfClass(GetWorld(), ATPHealthPickup::StaticClass(),
                                          HealthPickups);
    HealthPickupsRespawn();

    APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), NULL);
    check(PlayerController);
    ATPCharacter* Player = Cast<ATPCharacter>(PlayerController->GetCharacter());
    check(Player);
    UTPHealthComponent* HealthComponent =
        Cast<UTPHealthComponent>(Player->GetComponentByClass(UTPHealthComponent::StaticClass()));
    check(HealthComponent);
    HealthComponent->PlayerDead.AddDynamic(this, &ATPGameModeBase::FinishGame);

    ATPPlayerHUD* HUD = Cast<ATPPlayerHUD>(PlayerController->GetHUD());
    UpdateGameTimeDelegate.AddDynamic(HUD, &ATPPlayerHUD::UpdateGameTime);
}

void ATPGameModeBase::HealthPickupsRespawn()
{
    if (IsAnyHealthPickupReachable())
    {
        return;
    }

    int32 RandomNum = FMath::RandRange(0, 4);
    static int32 PreviousNum = RandomNum;
    while (true)
    {
        RandomNum = FMath::RandRange(0, 4);

        if (RandomNum != PreviousNum)
        {
            PreviousNum = RandomNum;
            break;
        }
    }

    ATPHealthPickup* HealthPickup = Cast<ATPHealthPickup>(HealthPickups[RandomNum]);
    if (HealthPickup)
    {
        HealthPickup->PickupRespawn();
    }
}

void ATPGameModeBase::SetupPlayerLifeTimer()
{
    GetWorld()->GetTimerManager().SetTimer(PlayerLifeTimer, this, &ATPGameModeBase::UpdateGameTime,
                                           TimerRate, true);
}

void ATPGameModeBase::DestroyPlayerLifeTimer()
{
    GetWorld()->GetTimerManager().ClearTimer(PlayerLifeTimer);
}

bool ATPGameModeBase::IsAnyHealthPickupReachable()
{
    for (AActor* HealthPickup : HealthPickups)
    {
        if (Cast<ATPHealthPickup>(HealthPickup)->IsPickupReachable())
        {
            return true;
        }
    }
    return false;
}

void ATPGameModeBase::UpdateGameTime()
{
    TimerRemaining += TimerRate;
    UpdateGameTimeDelegate.Broadcast(TimerRemaining);
}

void ATPGameModeBase::FinishGame()
{
    DestroyPlayerLifeTimer();
}
