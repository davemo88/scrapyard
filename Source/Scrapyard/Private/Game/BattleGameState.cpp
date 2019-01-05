// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleGameState.h"
#include "Engine/World.h"

ABattleGameState::ABattleGameState()
{

}

void ABattleGameState::MulticastShowTimer_Implementation(float TimerLength)
{
//TODO: add timer widget to screen
  UWorld* World = GetWorld();  
  APlayerController* PC = World->GetFirstPlayerController();
// i guess this should never fail?
  if (PC != nullptr && PC->IsLocalController())
  {
    World->GetTimerManager().SetTimer(StartMatchTimerHandle, 1.0f, true);  
  }
}

