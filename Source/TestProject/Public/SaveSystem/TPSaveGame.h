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
    void AddNewResult(int32 Result);

    TArray<int32> GetGameResults() const;

protected:
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "LeaderBoard")
    int32 LidearBoardSize = 5;

private:
    UPROPERTY(VisibleAnywhere)
    TArray<int32> GameResults;
};
