// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleGameState.h"
#include "Robots/RobotPlayerController.h"

ABattleGameState::ABattleGameState()
{

}

void ABattleGameState::BeginPlay()
{
  UE_LOG(LogTemp, Warning, TEXT("%s::BeginPlay"), *GetName());
  Super::BeginPlay();

  if (!HasAuthority())
  {
    UWorld* World = GetWorld();
    ARobotPlayerController* RobotPC = World->GetFirstPlayerController<ARobotPlayerController>();
    if (RobotPC)
    {
      RobotPC->ServerNotifyGameStateReplicated();
    }
  }
}

