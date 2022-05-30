// Slava Ukraine

#pragma once

#include "Blueprint/UserWidget.h"
#include "CoreMinimal.h"
#include "TPPlayerDeadWidget.generated.h"

/**
 *
 */
UCLASS()
class TESTPROJECT_API UTPPlayerDeadWidget : public UUserWidget
{
    GENERATED_BODY()

protected:
    UFUNCTION(BlueprintCallable)
    void ExitGame();

    UFUNCTION(BlueprintCallable)
    void RestartGame();

    UFUNCTION(BlueprintCallable, Category = "UI")
    FString GetGameTimeResults(int32 Index) const;

private:
    TArray<int32> GameTimeResults;

public:
    void SetTimeResultsArray(TArray<int32> TimeResults);
};
