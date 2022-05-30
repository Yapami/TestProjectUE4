// Slava Ukraine

#pragma once

#include "Blueprint/UserWidget.h"
#include "CoreMinimal.h"
#include "TPPlayerHUDWidget.generated.h"

/**
 *
 */
UCLASS()
class TESTPROJECT_API UTPPlayerHUDWidget : public UUserWidget
{
    GENERATED_BODY()
protected:
    UFUNCTION(BlueprintCallable, Category = "UI")
    float GetHealthPercent() const;

    UFUNCTION(BlueprintCallable, Category = "UI")
    FString GetTimeSinceStartGame() const;

    int32 TimeSinceGameStart = 0;

public:
    void SetTimeSinceGameStart(float Time);
};
