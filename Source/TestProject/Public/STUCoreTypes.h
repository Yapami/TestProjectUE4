#pragma once

#include "STUCoreTypes.generated.h"

UENUM()
enum class EGameState : uint8
{
    PlayerIsDead,
    PlayerIsAlive
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FGameStateSignature, EGameState, GameState);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FUpdateGameTimeSignature, float, Time);