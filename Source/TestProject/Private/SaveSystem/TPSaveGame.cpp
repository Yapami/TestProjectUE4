// Slava Ukraine

#include "SaveSystem/TPSaveGame.h"

void UTPSaveGame::AddNewResult(int32 Result)
{
    if (GameResults.Num() < LidearBoardSize)
    {
        GameResults.Add(Result);
    }
    else if (GameResults.Num() == LidearBoardSize)
    {
        if (Result >= GameResults[LidearBoardSize - 1])
        {
            GameResults[LidearBoardSize - 1] = Result;
        }
    }

    GameResults.Sort([](int32 First, int32 Second) { return First > Second; });
}

TArray<int32> UTPSaveGame::GetGameResults() const
{
    return GameResults;
}
