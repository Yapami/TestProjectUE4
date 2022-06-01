// Slava Ukraine

#include "UI/TPPlayerDeadWidget.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"
#include "SaveSystem/TPSaveGame.h"
#include "TPUtils.h"

void UTPPlayerDeadWidget::ExitGame()
{
    UWorld* World = GetWorld();
    if (!World)
    {
        return;
    }
    APlayerController* PlayerController = UGameplayStatics::GetPlayerController(World, 0);
    if (!PlayerController)
    {
        return;
    }
    UKismetSystemLibrary::QuitGame(GetWorld(), PlayerController, EQuitPreference::Quit, true);
}

void UTPPlayerDeadWidget::RestartGame()
{
    UGameplayStatics::OpenLevel(this, FName(*GetWorld()->GetName()), false);
}

FString UTPPlayerDeadWidget::GetGameResultByIndex(int32 Index) const
{
    UTPSaveGame* SaveGameInstance =
        Cast<UTPSaveGame>(UGameplayStatics::LoadGameFromSlot("TPSaves", 0));

    if ((Index < 0) || (Index > SaveGameInstance->GetGameResults().Num()) ||
        !SaveGameInstance->GetGameResults().IsValidIndex(Index) ||
        SaveGameInstance->GetGameResults().Num() == 0)
    {
        return "---";
    }
    return TPUtils::IntToTime(SaveGameInstance->GetGameResults()[Index]);
}