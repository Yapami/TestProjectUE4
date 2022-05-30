// Slava Ukraine

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "TPSaveGame.generated.h"

/**
 *
 */
UCLASS()
class TESTPROJECT_API UTPSaveGame : public USaveGame
{
    GENERATED_BODY()
public:
    void AddTimeResult(int32 TimeResult);
    TArray<int32>& GetTimeResults();

private:
    TArray<int32> TimeResults{0, 0, 0, 0, 0};
};
