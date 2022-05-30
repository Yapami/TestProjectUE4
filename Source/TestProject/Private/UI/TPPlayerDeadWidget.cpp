// Slava Ukraine

#include "UI/TPPlayerDeadWidget.h"
#include "GenericPlatform/GenericPlatformMisc.h"
#include "Kismet/GameplayStatics.h"

void UTPPlayerDeadWidget::ExitGame()
{
    FGenericPlatformMisc::RequestExit(false);
}

void UTPPlayerDeadWidget::RestartGame()
{
    UGameplayStatics::OpenLevel(this, FName(*GetWorld()->GetName()), false);
}

FString UTPPlayerDeadWidget::GetGameTimeResults(int32 Index) const
{
    return "0" + FString::FromInt(GameTimeResults[Index] / 60) + ":" +
           ((GameTimeResults[Index] % 60) < 10 ? "0" : "") +
           FString::FromInt(GameTimeResults[Index] % 60);
}

void UTPPlayerDeadWidget::SetTimeResultsArray(TArray<int32> TimeResults)
{
    GameTimeResults = TimeResults;
}