// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleGameMode.h"
#include "BattleGameState.h"
#include "Robots/RobotCharacter.h"
#include "Player/RobotPlayerController.h"
#include "Player/RobotPlayerState.h"

ABattleGameMode::ABattleGameMode()
{
  GameStateClass = ABattleGameState::StaticClass();

  MinPlayers = 2;

  bMatchTimerExpired = false;
  bReadyToEndMatch = false;
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
  UE_LOG(LogTemp, Warning, TEXT("%s::PostLogin"), *GetName());
  Super::PostLogin(NewPlayer);

  ARobotPlayerController* RobotPC = Cast<ARobotPlayerController>(NewPlayer);
  RobotPC->ClientGetPartAssignmentIDs();

  ARobotPlayerState* PlayerState = RobotPC->GetPlayerState<ARobotPlayerState>(); 
  PlayerState->SetTeam(GetNumPlayers());
}

void ABattleGameMode::Logout(AController* Exiting)
{
  UE_LOG(LogTemp, Warning, TEXT("%s::Logout"), *GetName());
  Super::Logout(Exiting);
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
      if (RobotPC->IsGameStateReplicated())
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
  if (GetNumPlayers() >= MinPlayers)
  {
    if (!RobotGS->IsMatchTimerActive() && IsGameStateReplicatedToAllClients() && !bMatchTimerExpired)
    {
// TODO: everything might not be replicated at this point (e.g. gamestate) so we need to either:
// 1. wait for an event from each client to confirm everything is ready
// 2. just wait a bit and hope
// if a client's gamestate hasn't finished replicating yet, then this rpc won't be executed on that client
      RobotGS->MulticastStartMatchTimer(5);
    }
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

bool ABattleGameMode::ReadyToEndMatch_Implementation()
{
  return bReadyToEndMatch;
}

void ABattleGameMode::StartMatch()
{
  UE_LOG(LogTemp, Warning, TEXT("%s::StartMatch"), *GetName());
  Super::StartMatch();
}

void ABattleGameMode::RestartPlayer(AController* NewPlayer)
{
  UE_LOG(LogTemp, Warning, TEXT("%s::RestartPlayer"), *GetName());
  Super::RestartPlayer(NewPlayer);
  if (ARobotCharacter* RobotChar = Cast<ARobotCharacter>(NewPlayer->GetPawn()))
  {
    UE_LOG(LogTemp, Warning, TEXT("%s::RestartPlayer - RobotChar OK"), *GetName());
    RobotChar->ZeroHitPointsDelegate.AddDynamic(this, &ABattleGameMode::OnZeroHitPoints);
  }
}


void ABattleGameMode::OnZeroHitPoints()
{
  bReadyToEndMatch = true;
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
  
// free for all. add all other players to each player's opponent list
//  if (ABattleGameState* GameState = GetGameState<ABattleGameState>())
//  {
//    for (uint8 i = 0; i < GameState->PlayerArray.Num(); i++)
//    {
//      if (ARobotPlayerState* RobotPlayerState = Cast<ARobotPlayerState>(GameState->PlayerArray[i])) 
//      {
//        for (uint8 j = 0; j < GameState->PlayerArray.Num(); j++)  
//          if (i != j)
//          {
//            RobotPlayerState->AddOpponent(GameState->PlayerArray[j]);
//          }
//      }
//    }
//  }
}

void ABattleGameMode::HandleMatchAborted()
{
  UE_LOG(LogTemp, Warning, TEXT("HandleMatchAborted"));
}

void ABattleGameMode::HandleMatchHasEnded()
{
  UE_LOG(LogTemp, Warning, TEXT("HandleMatchHasEnded"));
//TODO: timer
  RestartGame();
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
