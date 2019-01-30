// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleGameMode.h"
#include "BattleGameState.h"
#include "Robots/RobotCharacter.h"
#include "Robots/RobotPlayerController.h"

ABattleGameMode::ABattleGameMode()
{
//  bDelayedStart = true;
//  DefaultPawnClass = ARobotCharacter::StaticClass();
//  PlayerControllerClass = ARobotPlayerController::StaticClass();
  GameStateClass = ABattleGameState::StaticClass();

  bMatchTimerExpired = false;
}

void ABattleGameMode::BeginPlay()
{
  UE_LOG(LogTemp, Warning, TEXT("%s::BeginPlay"), *GetName());
  Super::BeginPlay();
  ARobotGameState* RobotGS = GetGameState<ARobotGameState>();
  RobotGS->OnMatchTimerExpiredDelegate.AddDynamic(this, &ABattleGameMode::OnMatchTimerExpired);
}

void ABattleGameMode::PostLogin(APlayerController* NewPlayer)
{
  Super::PostLogin(NewPlayer);
  UE_LOG(LogTemp, Warning, TEXT("Battle Game Mode Post Login"));
  UE_LOG(LogTemp, Warning, TEXT("bDelayedStart: %s"), (this->bDelayedStart ? TEXT("True") : TEXT("False")));
  UE_LOG(LogTemp, Warning, TEXT("Num Players: %d"), GetNumPlayers());

  ARobotPlayerController* RobotPC = Cast<ARobotPlayerController>(NewPlayer);
  RobotPC->ClientGetPartAssignmentIDs();

//  if (GetNumPlayers() > 1)
//  {
//    ARobotGameState* RobotGS = GetGameState<ARobotGameState>();
//    RobotGS->OnMatchTimerExpiredDelegate.AddDynamic(this, &ABattleGameMode::StartMatch);
//    RobotGS->MulticastStartMatchTimer(5);
//  }
  
}

bool ABattleGameMode::IsGameStateReplicatedToAllClients()
{
  int32 NumPlayers = GetNumPlayers();
  int32 NumReplicatedGameStates = 0;
  for (FConstPlayerControllerIterator Iterator = GetWorld()->GetPlayerControllerIterator(); Iterator; ++Iterator)
  {
    ARobotPlayerController* RobotPC = Cast<ARobotPlayerController>(*Iterator);
    if (RobotPC)
    {
      if (RobotPC->GameStateReplicated)
      {
        NumReplicatedGameStates++;
      }

    }
  }
  return NumPlayers == NumReplicatedGameStates;
}

bool ABattleGameMode::ReadyToStartMatch_Implementation()
{
//  UE_LOG(LogTemp, Warning, TEXT("%s::ReadyToStartMatch_Implementation"), *GetName());
  ARobotGameState* RobotGS = GetGameState<ARobotGameState>();
  bool Ready = false;
  if (GetNumPlayers() > 1)
  {
    if (!RobotGS->IsMatchTimerActive() && IsGameStateReplicatedToAllClients() && !bMatchTimerExpired)
    {
// TODO: everything might not be replicated at this point (e.g. gamestate) so we need to either:
// 1. wait for an event from each client to confirm everything is ready
// 2. just wait a bit and hope
// if a client's gamestate hasn't finished replicating yet, then this rpc won't be executed on that client
      RobotGS->MulticastStartMatchTimer(5);
    }
//    else if (RobotGS->IsMatchTimerActive() && RobotGS->GetMatchTimerSecondsRemaining() == 0)
    else if (bMatchTimerExpired)
    {
      Ready = true;
    }
  }
  else
  {
//TODO: should stop the timer here if somebody left
  }

  return Ready;
}

void ABattleGameMode::StartMatch()
{
  UE_LOG(LogTemp, Warning, TEXT("%s::StartMatch"), *GetName());
  Super::StartMatch();
}

void ABattleGameMode::OnMatchTimerExpired()
{
  bMatchTimerExpired = true;
}

void ABattleGameMode::HandleMatchIsWaitingToStart()
{
  Super::HandleMatchIsWaitingToStart();
  UE_LOG(LogTemp, Warning, TEXT("HandleMatchIsWaitingToStart"));
}

void ABattleGameMode::HandleMatchHasStarted()
{
  Super::HandleMatchHasStarted();
  UE_LOG(LogTemp, Warning, TEXT("%s::HandleMatchHasStarted"), *GetName());
  bMatchTimerExpired = false;
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
