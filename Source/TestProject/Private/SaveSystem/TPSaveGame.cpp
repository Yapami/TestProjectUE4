// Slava Ukraine

#include "SaveSystem/TPSaveGame.h"

void UTPSaveGame::AddTimeResult(int32 TimeResult)
{
    UE_LOG(LogTemp, Error, TEXT("LOG 300: Array elements: 0)%i, 1)%i, 2)%i, 3)%i, 4)%i"),
           TimeResults[0], TimeResults[1], TimeResults[2], TimeResults[3], TimeResults[4]);

    TArray<int32> Temp{0, 0, 0, 0, 0};

    for (size_t i = 0; i < 5; i++)
    {
        Temp[i] = TimeResults[i];
    }

    Temp.Add(TimeResult);

    //Temp.Sort();
    for (size_t i = 0; i < 6; i++)
    {
        for (size_t j = i+1; j < 6; j++)
        {
            if (Temp[i] < Temp[j])
            {
                Swap(Temp[i], Temp[j]);
            }
        }
    }

    UE_LOG(LogTemp, Error,
           TEXT("LOG 200: Array elements: 0)%i, 1)%i, 2)%i, 3)%i, 4)%i, TimeResult: %i"), Temp[0],
           Temp[1], Temp[2], Temp[3], Temp[4],
           TimeResult);

    for (size_t i = 0; i < 5; i++)
    {
        TimeResults[i] = Temp[i];
    }

    UE_LOG(LogTemp, Error, TEXT("LOG 100: Array elements: 0)%i, 1)%i, 2)%i, 3)%i, 4)%i"),
           TimeResults[0], TimeResults[1], TimeResults[2], TimeResults[3], TimeResults[4]);
}

TArray<int32>& UTPSaveGame::GetTimeResults()
{
    return TimeResults;
}
