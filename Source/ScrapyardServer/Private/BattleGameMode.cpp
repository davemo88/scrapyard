// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleGameMode.h"
#include "BattleGameState.h"
#include "Robots/RobotCharacter.h"
#include "Robots/RobotPlayerController.h"
#include "Player/ScrapyardPlayerController.h"

ABattleGameMode::ABattleGameMode()
{
  bDelayedStart = true;
  DefaultPawnClass = ARobotCharacter::StaticClass();
  PlayerControllerClass = AScrapyardPlayerController::StaticClass();
  GameStateClass = ABattleGameState::StaticClass();
}

void ABattleGameMode::PostLogin(APlayerController* NewPlayer)
{
  Super::PostLogin(NewPlayer);
  UE_LOG(LogTemp, Warning, TEXT("Battle Game Mode Post Login"));
  UE_LOG(LogTemp, Warning, TEXT("bDelayedStart: %s"), (this->bDelayedStart ? TEXT("True") : TEXT("False")));
  UE_LOG(LogTemp, Warning, TEXT("Num Players: %d"), GetNumPlayers());

  if (GetNumPlayers() > 1)
  {
    StartMatch();
  }
  
}

void ABattleGameMode::HandleMatchIsWaitingToStart()
{
  Super::HandleMatchIsWaitingToStart();
  UE_LOG(LogTemp, Warning, TEXT("HandleMatchIsWaitingToStart"));
}

void ABattleGameMode::HandleMatchHasStarted()
{
  Super::HandleMatchHasStarted();
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
//  Super::HandleStartingNewPlayer_Implementation();
  UE_LOG(LogTemp, Warning, TEXT("HandleStartingNewPlayer"));
}
