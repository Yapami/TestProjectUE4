// Fill out your copyright notice in the Description page of Project Settings.

#include "TPGameModeBase.h"
#include "Character/TPCharacter.h"
#include "Components/TPHealthComponent.h"
#include "Kismet/GameplayStatics.h"
#include "SaveSystem/TPSaveGame.h"
#include "UI/TPPlayerHUD.h"

ATPGameModeBase::ATPGameModeBase()
{
    DefaultPawnClass = ATPCharacter::StaticClass();
    HUDClass = ATPPlayerHUD::StaticClass();
}

void ATPGameModeBase::BeginPlay()
{
    Super::BeginPlay();
    UGameplayStatics::GetAllActorsOfClass(GetWorld(), ATPHealthPickup::StaticClass(),
                                          HealthPickups);
    HealthPickupsRespawn();

    ATPGameModeBase* GameMode = Cast<ATPGameModeBase>(GetWorld()->GetAuthGameMode());
    if (!GameMode)
    {
        return;
    }
    GameMode->OnChangeGameState.AddDynamic(this, &ATPGameModeBase::ChangeGameState);

    APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), NULL);
    check(PlayerController);
    ATPPlayerHUD* HUD = Cast<ATPPlayerHUD>(PlayerController->GetHUD());
    check(HUD);
    UpdateGameTimeDelegate.AddDynamic(HUD, &ATPPlayerHUD::UpdateGameTime);
}

void ATPGameModeBase::HealthPickupsRespawn()
{
    if (IsAnyHealthPickupReachable())
    {
        return;
    }

    const int32 HealthPickupsAmount = HealthPickups.Num() - 1;

    static int32 PreviousNum = FMath::RandRange(0, HealthPickupsAmount);
    int32 RandomNum;
    while (true)
    {
        RandomNum = FMath::RandRange(0, HealthPickupsAmount);

        if (RandomNum != PreviousNum)
        {
            PreviousNum = RandomNum;
            break;
        }
    }

    ATPHealthPickup* HealthPickup = Cast<ATPHealthPickup>(HealthPickups[RandomNum]);
    if (!HealthPickup)
    {
        return;
    }
    HealthPickup->MakePickupReachable();
}

void ATPGameModeBase::SetupGameStatePlayerAlive()
{
    OnChangeGameState.Broadcast(EGameState::PlayerIsAlive);
    GetWorld()->GetTimerManager().SetTimer(PlayerLifeTimer, this, &ATPGameModeBase::UpdateGameTime,
                                           TimerRate, true);
}

void ATPGameModeBase::DestroyPlayerLifeTimer()
{
    SaveResult();
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

void ATPGameModeBase::SaveResult()
{
    UTPSaveGame* SaveGameInstance = nullptr;
    if (UGameplayStatics::DoesSaveGameExist("TPSaves", 0))
    {
        SaveGameInstance = Cast<UTPSaveGame>(UGameplayStatics::LoadGameFromSlot("TPSaves", 0));
    }
    else
    {
        SaveGameInstance =
            Cast<UTPSaveGame>(UGameplayStatics::CreateSaveGameObject(UTPSaveGame::StaticClass()));
    }

    SaveGameInstance->AddNewResult(TimerRemaining);

    UGameplayStatics::SaveGameToSlot(SaveGameInstance, TEXT("TPSaves"), 0);
}

void ATPGameModeBase::ChangeGameState(EGameState State)
{
    if (State == EGameState::PlayerIsDead)
    {
        DestroyPlayerLifeTimer();
    }
}