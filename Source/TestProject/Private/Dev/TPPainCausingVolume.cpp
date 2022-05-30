// Slava Ukraine

#include "Dev/TPPainCausingVolume.h"
#include "Character/TPCharacter.h"
#include "Components/BoxComponent.h"
#include "Components/TPHealthComponent.h"
#include "Kismet/GameplayStatics.h"

ATPPainCausingVolume::ATPPainCausingVolume()
{
    PrimaryActorTick.bCanEverTick = false;

    SceneComponent = CreateDefaultSubobject<USceneComponent>("SceneComponent");
    RootComponent = SceneComponent;

    CollisionComponent = CreateDefaultSubobject<UBoxComponent>("CollisionComponent");
    CollisionComponent->SetupAttachment(SceneComponent);
}

void ATPPainCausingVolume::BeginPlay()
{
    Super::BeginPlay();

    APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
    check(PlayerController);
    ACharacter* Player = PlayerController->GetCharacter();
    check(Player);

    UTPHealthComponent* HealthComponent = CastChecked<UTPHealthComponent>(
        Player->GetComponentByClass(UTPHealthComponent::StaticClass()));
    HealthComponent->PlayerDead.AddDynamic(this, &ATPPainCausingVolume::FinishTimers);

    ApplyPainVolume();
}

void ATPPainCausingVolume::ApplyPainVolume()
{
    FTimerDelegate TimerCallback;
    TimerCallback.BindLambda([&] { DamagePerSec *= 1.1f; });

    FTimerDelegate DamageTick;
    DamageTick.BindLambda([&] {
        UGameplayStatics::ApplyDamage(
            UGameplayStatics::GetPlayerController(GetWorld(), 0)->GetCharacter(),
            DamagePerSec / 10,
            nullptr, this, UDamageType::StaticClass());
    });

    GetWorld()->GetTimerManager().SetTimer(IncreaseDamage, TimerCallback, 5.f, true);

    GetWorld()->GetTimerManager().SetTimer(TimeSinceGameStart, DamageTick, 1.f / 10, true);
}

void ATPPainCausingVolume::FinishTimers()
{
    GetWorld()->GetTimerManager().ClearTimer(IncreaseDamage);
    GetWorld()->GetTimerManager().ClearTimer(TimeSinceGameStart);
}
