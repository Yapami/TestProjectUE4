// Slava Ukraine

#include "Pickups/TPSpeedPickup.h"
#include "Character/TPCharacter.h"
#include "Components/TextRenderComponent.h"
#include "Kismet/GameplayStatics.h"
#include "TPGameModeBase.h"
#include "TPUtils.h"
#include "TimerManager.h"

ATPSpeedPickup::ATPSpeedPickup()
{
    PrimaryActorTick.bCanEverTick = true;

    TextComponent = CreateDefaultSubobject<UTextRenderComponent>("TextComponent");
    TextComponent->SetupAttachment(GetRootComponent());
    TextComponent->SetVisibility(false);
}

void ATPSpeedPickup::BeginPlay()
{
    Super::BeginPlay();

    ATPGameModeBase* GameMode = Cast<ATPGameModeBase>(GetWorld()->GetAuthGameMode());
    if (!GameMode)
    {
        return;
    }
    GameMode->OnChangeGameState.AddDynamic(this, &ATPSpeedPickup::ChangeGameState);
}

void ATPSpeedPickup::ShowTimeToRespawn()
{
    FTimerDelegate UpdateRespawnTime;
    UpdateRespawnTime.BindLambda([&]() {
        int32 Seconds =
            static_cast<int32>((TimeToSpeedPickupRespawn + 1) -
                               GetWorld()->GetTimerManager().GetTimerElapsed(RespawnTimer));
        TextComponent->SetText(TPUtils::IntToTime(Seconds));
    });

    TextComponent->SetText(TPUtils::IntToTime(static_cast<int32>(TimeToSpeedPickupRespawn)));
    TextComponent->SetVisibility(true);

    float TimeUpdateFrequency = 1.0;
    GetWorld()->GetTimerManager().SetTimer(RespawnTimeTimer, UpdateRespawnTime, TimeUpdateFrequency,
                                           true);
}

void ATPSpeedPickup::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
    if (!PlayerController)
    {
        return;
    }

    FRotator RotationPlayerViewPoint;
    FVector Vector; // Unusable variable
    PlayerController->GetPlayerViewPoint(Vector, RotationPlayerViewPoint);

    const float TurnCompensationPitch = -1;
    const float TurnCompensationYaw = 180.0f;
    TextComponent->SetWorldRotation(FRotator(TurnCompensationPitch * RotationPlayerViewPoint.Pitch,
                                             RotationPlayerViewPoint.Yaw + TurnCompensationYaw,
                                             RotationPlayerViewPoint.Roll));
}

void ATPSpeedPickup::PickupRespawnTimerStart()
{
    FTimerDelegate RespawnCallback;
    RespawnCallback.BindLambda([&]() {
        MakePickupReachable();

        GetWorld()->GetTimerManager().ClearTimer(RespawnTimeTimer);
        TextComponent->SetVisibility(false);
    });

    MakePickupUnreachable();

    GetWorld()->GetTimerManager().SetTimer(RespawnTimer, RespawnCallback, TimeToSpeedPickupRespawn,
                                           false);
}

void ATPSpeedPickup::ChangePlayerSpeed(AActor* Actor)
{
    ATPCharacter* Player = Cast<ATPCharacter>(Actor);
    if (!Player)
    {
        return;
    }

    FTimerDelegate SetNormalSpeedCallback;
    SetNormalSpeedCallback.BindLambda(
        [Player]() { Player->SetMaxWalkSpeed(Player->GetNormalSpeed()); });

    Player->SetMaxWalkSpeed(Player->GetNormalSpeed() * SpeedMultiplier);
    GetWorld()->GetTimerManager().SetTimer(SetNormalSpeedTimer, SetNormalSpeedCallback,
                                           HighSpeedDuration, false);
}

void ATPSpeedPickup::NotifyActorBeginOverlap(AActor* OtherActor)
{
    Super::NotifyActorBeginOverlap(OtherActor);

    ChangePlayerSpeed(OtherActor);

    PickupRespawnTimerStart();

    ShowTimeToRespawn();
}

void ATPSpeedPickup::ChangeGameState(EGameState GameState)
{
    if (GameState == EGameState::PlayerIsDead)
    {
        FinishAllTimers();
    }
}

void ATPSpeedPickup::FinishAllTimers()
{
    GetWorld()->GetTimerManager().ClearTimer(RespawnTimer);
    GetWorld()->GetTimerManager().ClearTimer(RespawnTimeTimer);
    GetWorld()->GetTimerManager().ClearTimer(SetNormalSpeedTimer);
}
