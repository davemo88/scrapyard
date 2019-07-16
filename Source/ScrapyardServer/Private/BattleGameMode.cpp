// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleGameMode.h"
#include "Game/BattleGameState.h"
#include "Robots/RobotCharacter.h"
#include "Player/RobotPlayerController.h"
#include "Player/RobotPlayerState.h"

ABattleGameMode::ABattleGameMode()
{
  GameStateClass = ABattleGameState::StaticClass();

  MinPlayers = 2;
  BattleTime = 10;
  EndCooldownTime = 5;

//  bReadyToStartMatch = false;
  bReadyToEndMatch = false;
}

void ABattleGameMode::BeginPlay()
{
  UE_LOG(LogGameMode, Log, TEXT("%s::BeginPlay"), *GetName());
  Super::BeginPlay();
  ABattleGameState* BattleGS = GetGameState<ABattleGameState>();
//TODO: update this to use specific resolution functions for when certain timers end
  BattleGS->OnMatchTimerExpiredDelegate.AddDynamic(this, &ABattleGameMode::OnMatchTimerExpired);
}

void ABattleGameMode::PostLogin(APlayerController* NewPlayer)
{
  UE_LOG(LogGameMode, Log, TEXT("%s::PostLogin"), *GetName());
  Super::PostLogin(NewPlayer);

  ARobotPlayerController* RobotPC = Cast<ARobotPlayerController>(NewPlayer);
  RobotPC->ClientGetPartAssignmentIDs();

  ARobotPlayerState* PlayerState = RobotPC->GetPlayerState<ARobotPlayerState>(); 
//TODO: need to set teams more intelligently
  PlayerState->SetTeam(GetNumPlayers());
}

void ABattleGameMode::Logout(AController* Exiting)
{
  UE_LOG(LogGameMode, Log, TEXT("%s::Logout"), *GetName());
  Super::Logout(Exiting);

  if (ARobotPlayerController* RobotPC = Cast<ARobotPlayerController>(Exiting))
  {
    UE_LOG(LogGameMode, Log, TEXT("Logout: UnregisterWithGamestate"));
    if (RobotPC->GetRobotCharacter())
    RobotPC->GetRobotCharacter()->TargetableComponent->UnregisterWithGamestate();
  }
  
  if (GetNumPlayers() < MinPlayers)
  {
    bReadyToEndMatch = true;
  }
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
//  UE_LOG(LogGameMode, Log, TEXT("%s::ReadyToStartMatch_Implementation"), *GetName());
  ABattleGameState* BattleGS = GetGameState<ABattleGameState>();
  if (GetNumPlayers() >= MinPlayers)
  {
// NOTE: everything might not be replicated at this point (e.g. gamestate)
    if (!BattleGS->IsMatchTimerActive() && IsGameStateReplicatedToAllClients() && !BattleGS->IsMatchTimerExpired())
    {
// if a client's gamestate hasn't finished replicating yet, then this rpc won't be executed on that client
      BattleGS->MulticastStartMatchTimer(5);
// this is a little weird
      BattleGS->MulticastReadyToStartMatch(true);
    }
    else if (BattleGS->IsMatchTimerExpired())
    {
      bReadyToStartMatch = true;
    }
  }
// somebody left since the countdown started
  else if (BattleGS->IsMatchTimerActive())
  {
    BattleGS->MulticastReadyToStartMatch(false);
    BattleGS->MulticastStopMatchTimer();
    bReadyToEndMatch = false;
  }

  return bReadyToStartMatch;
}

bool ABattleGameMode::ReadyToEndMatch_Implementation()
{
  return bReadyToEndMatch;
}

void ABattleGameMode::StartMatch()
{
  UE_LOG(LogGameMode, Log, TEXT("%s::StartMatch"), *GetName());
  Super::StartMatch();
}

void ABattleGameMode::RestartPlayer(AController* NewPlayer)
{
  UE_LOG(LogGameMode, Log, TEXT("%s::RestartPlayer"), *GetName());
  Super::RestartPlayer(NewPlayer);
  if (ARobotCharacter* RobotChar = Cast<ARobotCharacter>(NewPlayer->GetPawn()))
  {
    UE_LOG(LogGameMode, Log, TEXT("%s::RestartPlayer - RobotChar OK"), *GetName());
    RobotChar->ZeroHitPointsDelegate.AddDynamic(this, &ABattleGameMode::OnZeroHitPoints);
  }
}


void ABattleGameMode::OnZeroHitPoints()
{
  bReadyToEndMatch = true;
}

void ABattleGameMode::OnMatchTimerExpired()
{
  if (ABattleGameState* BattleGS = GetGameState<ABattleGameState>())
  {
    BattleGS->MulticastStopMatchTimer();
  }
}

void ABattleGameMode::HandleMatchIsWaitingToStart()
{
  Super::HandleMatchIsWaitingToStart();
  UE_LOG(LogGameMode, Log, TEXT("HandleMatchIsWaitingToStart"));
}

void ABattleGameMode::HandleMatchHasStarted()
{
  Super::HandleMatchHasStarted();
  UE_LOG(LogGameMode, Log, TEXT("%s::HandleMatchHasStarted"), *GetName());
  if (ABattleGameState* BattleGS = GetGameState<ABattleGameState>())
  {
    BattleGS->MulticastStartMatchTimer(BattleTime);
    BattleGS->OnMatchTimerExpiredDelegate.AddDynamic(this, &ABattleGameMode::OnBattleTimeExpired);
  }

}

void ABattleGameMode::HandleMatchAborted()
{
  UE_LOG(LogGameMode, Log, TEXT("%s::HandleMatchAborted"), *GetName());
}

void ABattleGameMode::HandleMatchHasEnded()
{
  UE_LOG(LogGameMode, Log, TEXT("%s::HandleMatchHasEnded"), *GetName());
  if (ABattleGameState* BattleGS = GetGameState<ABattleGameState>())
  {
    BattleGS->MulticastStartMatchTimer(EndCooldownTime);
    BattleGS->OnMatchTimerExpiredDelegate.AddDynamic(this, &ABattleGameMode::OnEndCooldownTimeExpired);
  }

}

void ABattleGameMode::HandleLeavingMap()
{
  UE_LOG(LogGameMode, Log, TEXT("%s::HandleLeavingMap"), *GetName());
}

void ABattleGameMode::HandleStartingNewPlayer_Implementation(APlayerController* NewPlayer)
{
//  Super::HandleStartingNewPlayer_Implementation();
  UE_LOG(LogGameMode, Log, TEXT("HandleStartingNewPlayer"));
}

void ABattleGameMode::OnBattleTimeExpired()
{
  UE_LOG(LogGameMode, Log, TEXT("%s::OnBattleTimeExpired"), *GetName());
  if (ABattleGameState* BattleGS = GetGameState<ABattleGameState>())
  {
    BattleGS->OnMatchTimerExpiredDelegate.RemoveDynamic(this, &ABattleGameMode::OnBattleTimeExpired);
  }
  bReadyToEndMatch = true;
}

void ABattleGameMode::OnEndCooldownTimeExpired()
{
  UE_LOG(LogGameMode, Log, TEXT("%s::OnEndCooldownTimeExpired"), *GetName());
  if (ABattleGameState* BattleGS = GetGameState<ABattleGameState>())
  {
    BattleGS->OnMatchTimerExpiredDelegate.RemoveDynamic(this, &ABattleGameMode::OnEndCooldownTimeExpired);
//    BattleGS->MulticastBroadcastLeavingMap();
  }
  RestartGame();
}
