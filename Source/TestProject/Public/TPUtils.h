#pragma once

class TPUtils
{
public:
    static FString IntToTime(int32 Seconds)
    {
        const int32 SecondsInMinute = 60;
        const int32 SecondsInTenMinutes = 600;

        return FString::FromInt(Seconds / SecondsInTenMinutes) +
               FString::FromInt(Seconds / SecondsInMinute) + ":" +
               ((Seconds % SecondsInMinute) < 10 ? "0" : "") +
               FString::FromInt(Seconds % SecondsInMinute);
    }
};