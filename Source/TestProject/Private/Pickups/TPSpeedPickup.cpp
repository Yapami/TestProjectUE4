// Slava Ukraine

#include "Pickups/TPSpeedPickup.h"
#include "Character/TPCharacter.h"
#include "Components/TextRenderComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "TimerManager.h"

ATPSpeedPickup::ATPSpeedPickup()
{
    SpeedPickup = CreateDefaultSubobject<UStaticMeshComponent>("SpeedPickup");
    SpeedPickup->SetupAttachment(GetRootComponent());

    TextComponent = CreateDefaultSubobject<UTextRenderComponent>("TextComponent");
    TextComponent->SetupAttachment(GetRootComponent());
    TextComponent->SetVisibility(false);
}

void ATPSpeedPickup::ShowTimeToRespawn()
{
    int32 Seconds = 16 - GetWorld()->GetTimerManager().GetTimerElapsed(RespawnTimer);
    TextComponent->SetText(
        FText::FromString((Seconds < 10 ? "0" : "") + FString::FromInt(Seconds)));
}

void ATPSpeedPickup::Tick(float DeltaTime)
{
    APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
    check(PlayerController);

    FRotator PlayerViewPoint;
    FVector Vector;
    PlayerController->GetPlayerViewPoint(Vector, PlayerViewPoint);

    TextComponent->SetWorldRotation(
        FRotator(-PlayerViewPoint.Pitch, PlayerViewPoint.Yaw + 180.f, PlayerViewPoint.Roll));
}

void ATPSpeedPickup::NotifyActorBeginOverlap(AActor* OtherActor)
{
    Super::NotifyActorBeginOverlap(OtherActor);

    ATPCharacter* Player = Cast<ATPCharacter>(OtherActor);
    if (!Player)
    {
        return;
    }
    float& MaxWalkSpeed = Player->GetCharacterMovement()->MaxWalkSpeed;

    FTimerHandle SetNormalSpeedTimer;
    FTimerDelegate SetNormalSpeedCallback;
    SetNormalSpeedCallback.BindLambda([&MaxWalkSpeed]() { MaxWalkSpeed = 800; });

    MaxWalkSpeed *= 1.5;
    GetWorld()->GetTimerManager().SetTimer(SetNormalSpeedTimer, SetNormalSpeedCallback, 5.f, false);

    FTimerDelegate RespawnCallback;
    RespawnCallback.BindLambda([&]() {
        SpeedPickup->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);
        SpeedPickup->SetVisibility(true, true);

        GetWorld()->GetTimerManager().ClearTimer(RespawnTimeTimer);

        TextComponent->SetVisibility(false);
    });

    SpeedPickup->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
    SpeedPickup->SetVisibility(false, true);

    GetWorld()->GetTimerManager().SetTimer(RespawnTimer, RespawnCallback, 15.f, false);

    TextComponent->SetText(FString::FromInt(15));
    TextComponent->SetVisibility(true);
    GetWorld()->GetTimerManager().SetTimer(RespawnTimeTimer, this,
                                           &ATPSpeedPickup::ShowTimeToRespawn, 1.0f, true);
}
