// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Game/RobotGameMode.h"
#include "BattleGameMode.generated.h"

/**
 * 
 */
UCLASS()
class SCRAPYARDSERVER_API ABattleGameMode : public ARobotGameMode
{
  GENERATED_BODY()

public:

  ABattleGameMode();

  virtual void BeginPlay() override;

  virtual void PostLogin(APlayerController* NewPlayer) override;
  virtual void Logout(AController* Exiting) override;
  
  virtual void StartMatch() override;

  virtual void RestartPlayer(AController* NewPlayer) override;

protected:

  uint32 MinPlayers;

  uint32 StartCountdownTime;
  uint32 BattleTime;
  uint32 EndCooldownTime;

  UFUNCTION()
  virtual void OnZeroHitPoints();

  bool bReadyToStartMatch;
  bool bReadyToEndMatch;

  bool IsGameStateReplicatedToAllClients();

  virtual bool ReadyToStartMatch_Implementation() override;

  virtual bool ReadyToEndMatch_Implementation() override;
    
  void HandleMatchIsWaitingToStart() override;
  void HandleMatchHasStarted() override;
  void HandleMatchHasEnded() override;
  void HandleMatchAborted() override;
  void HandleLeavingMap() override;
  void HandleStartingNewPlayer_Implementation(APlayerController* NewPlayer) override;

  FTimerHandle StartMatchTimerHandle;

  UFUNCTION()
  void OnBattleTimeExpired();

//  UFUNCTION()
//  void OnStartCountdownTimeExpired();

//  UFUNCTION()
//  void OnStartCountdownTimeExpired();

  UFUNCTION()
  void OnEndCooldownTimeExpired();

  UFUNCTION()
  void OnMatchTimerExpired();

};
