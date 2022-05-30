// Slava Ukraine

#include "UI/TPPlayerHUD.h"
#include "Blueprint/UserWidget.h"
#include "Kismet/GameplayStatics.h"
#include "STUCoreTypes.h"
#include "TPGameModeBase.h"
#include "UI/TPPlayerHUDWidget.h"
#include "UI/TPPlayerDeadWidget.h"

void ATPPlayerHUD::BeginPlay()
{
    Super::BeginPlay();

    GameState = EGameState::PlayerIsAlive;

    PlayerHUDWidget = CreateWidget<UUserWidget>(GetWorld(), PlayerHUDWidgetClass);
    if (PlayerHUDWidget)
    {
        PlayerHUDWidget->AddToViewport();
    }

    PlayerDeadWidget = CreateWidget<UUserWidget>(GetWorld(), PlayerDeadWidgetClass);

    ATPGameModeBase* GameMode = CastChecked<ATPGameModeBase>(GetWorld()->GetAuthGameMode());
    GameMode->OnChangeGameState.AddDynamic(this, &ATPPlayerHUD::ChangeWidget);
}

void ATPPlayerHUD::UpdateGameTime(float Time)
{
    Cast<UTPPlayerHUDWidget>(PlayerHUDWidget)->SetTimeSinceGameStart(Time);
}

void ATPPlayerHUD::ChangeWidget(EGameState GameStateParam)
{
    APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);

    ATPGameModeBase* GameMode = CastChecked<ATPGameModeBase>(GetWorld()->GetAuthGameMode());

    switch (GameStateParam)
    {
    case EGameState::PlayerIsDead:
        if (PlayerController)
        {
            PlayerController->bShowMouseCursor = PlayerController->bEnableClickEvents =
                PlayerController->bEnableMouseOverEvents = true;
        }

        PlayerHUDWidget->RemoveFromViewport();
        PlayerDeadWidget->AddToViewport();

        break;
    case EGameState::PlayerIsAlive:
        PlayerDeadWidget->RemoveFromViewport();
        PlayerHUDWidget->AddToViewport();
        break;
    default:
        break;
    }
}