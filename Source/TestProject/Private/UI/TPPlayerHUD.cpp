// Slava Ukraine

#include "UI/TPPlayerHUD.h"
#include "Blueprint/UserWidget.h"
#include "Kismet/GameplayStatics.h"
#include "STUCoreTypes.h"
#include "TPGameModeBase.h"
#include "UI/TPPlayerDeadWidget.h"
#include "UI/TPPlayerHUDWidget.h"

void ATPPlayerHUD::BeginPlay()
{
    Super::BeginPlay();

    PlayerAliveHUDWidget = CreateWidget<UUserWidget>(GetWorld(), PlayerHUDWidgetClass);
    check(PlayerAliveHUDWidget);

    PlayerDeadHUDWidget = CreateWidget<UUserWidget>(GetWorld(), PlayerDeadWidgetClass);
    check(PlayerAliveHUDWidget);

    ATPGameModeBase* GameMode = Cast<ATPGameModeBase>(GetWorld()->GetAuthGameMode());
    check(GameMode);
    GameMode->OnChangeGameState.AddDynamic(this, &ATPPlayerHUD::ChangeGameState);
}

void ATPPlayerHUD::UpdateGameTime(float Time)
{
    Cast<UTPPlayerHUDWidget>(PlayerAliveHUDWidget)->SetTimeSinceGameStart(Time);
}

void ATPPlayerHUD::ChangeGameState(EGameState State)
{
    APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);

    ATPGameModeBase* GameMode = CastChecked<ATPGameModeBase>(GetWorld()->GetAuthGameMode());

    switch (State)
    {
    case EGameState::PlayerIsDead:

        if (PlayerController)
        {
            PlayerController->bShowMouseCursor = true;
            PlayerController->bEnableClickEvents = true;
            PlayerController->bEnableMouseOverEvents = true;
            PlayerController->SetInputMode(FInputModeUIOnly());
        }

        PlayerAliveHUDWidget->RemoveFromViewport();
        PlayerDeadHUDWidget->AddToViewport();

        break;
    case EGameState::PlayerIsAlive:

        if (PlayerController)
        {
            PlayerController->bShowMouseCursor = false;
            PlayerController->bEnableClickEvents = false;
            PlayerController->bEnableMouseOverEvents = false;
            PlayerController->SetInputMode(FInputModeGameOnly());
        }

        PlayerDeadHUDWidget->RemoveFromViewport();
        PlayerAliveHUDWidget->AddToViewport();

        break;
    default:
        break;
    }
}