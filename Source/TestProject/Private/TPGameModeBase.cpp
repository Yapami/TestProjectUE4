// Fill out your copyright notice in the Description page of Project Settings.


#include "TPGameModeBase.h"
#include "Character/TPCharacter.h"
#include "Character/TPPlayerController.h"

ATPGameModeBase::ATPGameModeBase()
{
    DefaultPawnClass = ATPCharacter::StaticClass();
    PlayerControllerClass = ATPPlayerController::StaticClass();
}
