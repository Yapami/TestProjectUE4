// Slava Ukraine

#include "Dev/TPPainCausingVolume.h"
#include "Character/TPCharacter.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"
#include "TPGameModeBase.h"

ATPPainCausingVolume::ATPPainCausingVolume()
{
    PrimaryActorTick.bCanEverTick = false;

    SceneComponent = CreateDefaultSubobject<USceneComponent>("SceneComponent");
    check(SceneComponent);
    SetRootComponent(SceneComponent);

    CollisionComponent = CreateDefaultSubobject<UBoxComponent>("CollisionComponent");
    check(CollisionComponent);
    CollisionComponent->SetupAttachment(GetRootComponent());
}

void ATPPainCausingVolume::BeginPlay()
{
    Super::BeginPlay();

    ATPGameModeBase* GameMode = Cast<ATPGameModeBase>(GetWorld()->GetAuthGameMode());
    if (!GameMode)
    {
        return;
    }
    GameMode->OnChangeGameState.AddDynamic(this, &ATPPainCausingVolume::ApplyDamageSwitcher);

    ApplyPainVolume();
}

void ATPPainCausingVolume::ApplyPainVolume()
{
    FTimerDelegate DamageTick;
    DamageTick.BindLambda([&] {
        static float TimeElapsed = 0;
        TimeElapsed += DamageTimerFrequancy / TimerTicksPerSecond;
        if (FMath::IsNearlyEqual(TimeElapsed, IncreaseDamageFrequancy, 0.001f))
        {
            TimeElapsed = 0;
            DamagePerSec *= DamageMultiplier;
        }

        APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
        check(PlayerController);
        ACharacter* Player = PlayerController->GetCharacter();
        check(Player);

        UGameplayStatics::ApplyDamage(Player, DamagePerSec / TimerTicksPerSecond, nullptr, this,
                                      UDamageType::StaticClass());
    });

    GetWorld()->GetTimerManager().SetTimer(ApplyDamageEverySecondTimer, DamageTick,
                                           DamageTimerFrequancy / TimerTicksPerSecond, true);
}

void ATPPainCausingVolume::ApplyDamageSwitcher(EGameState GameState)
{
    switch (GameState)
    {
    case EGameState::PlayerIsDead:
        GetWorld()->GetTimerManager().ClearTimer(ApplyDamageEverySecondTimer);
        break;
    case EGameState::PlayerIsAlive:
        ApplyPainVolume();
        break;
    default:
        break;
    }
}
