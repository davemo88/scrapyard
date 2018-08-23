// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleGameMode.h"
#include "Robots/RobotCharacter.h"
#include "Robots/RobotPlayerController.h"

void ABattleGameMode::PostLogin(APlayerController* NewPlayer)
{
  Super::PostLogin(NewPlayer);
}

void ABattleGameMode::HandleMatchIsWaitingToStart()
{
  UE_LOG(LogTemp, Warning, TEXT("HandleMatchIsWaitingToStart"));
}

void ABattleGameMode::HandleMatchHasStarted()
{
  UE_LOG(LogTemp, Warning, TEXT("HandleMatchHasStarted"));
}

void ABattleGameMode::HandleMatchAborted()
{
  UE_LOG(LogTemp, Warning, TEXT("HandleMatchAborted"));
}

void ABattleGameMode::HandleMatchHasEnded()
{
  UE_LOG(LogTemp, Warning, TEXT("HandleMatchHasEnded"));
}

void ABattleGameMode::HandleLeavingMap()
{
  UE_LOG(LogTemp, Warning, TEXT("HandleLeavingMap"));
}

void ABattleGameMode::HandleStartingNewPlayer_Implementation(APlayerController* NewPlayer)
{
  UE_LOG(LogTemp, Warning, TEXT("HandleStartingNewPlayer"));
}
