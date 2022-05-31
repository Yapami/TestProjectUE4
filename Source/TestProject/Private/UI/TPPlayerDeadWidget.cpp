// Slava Ukraine

#include "UI/TPPlayerDeadWidget.h"
#include "GenericPlatform/GenericPlatformMisc.h"
#include "Kismet/GameplayStatics.h"
#include "SaveSystem/TPSaveGame.h"
#include "TPUtils.h"

void UTPPlayerDeadWidget::ExitGame()
{
    FGenericPlatformMisc::RequestExit(false);
}

void UTPPlayerDeadWidget::RestartGame()
{
    UGameplayStatics::OpenLevel(this, FName(*GetWorld()->GetName()), false);
}

FString UTPPlayerDeadWidget::GetGameResultByIndex(int32 Index) const
{
    UTPSaveGame* SaveGameInstance =
        Cast<UTPSaveGame>(UGameplayStatics::LoadGameFromSlot("TPSaves", 0));

    if ((Index < 0) && (Index > SaveGameInstance->GetGameResults().Num()) &&
        !SaveGameInstance->GetGameResults().IsValidIndex(Index))
    {
        return "---";
    }
    return TPUtils::IntToTime(SaveGameInstance->GetGameResults()[Index]);
}