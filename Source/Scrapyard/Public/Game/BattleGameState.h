// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Game/RobotGameState.h"
#include "BattleGameState.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnLeavingMapDelegate);

/**
 * 
 */
UCLASS()
class SCRAPYARD_API ABattleGameState : public ARobotGameState
{
  GENERATED_BODY()
      
public:

  FOnLeavingMapDelegate OnLeavingMapDelegate;

  UFUNCTION(NetMulticast, Reliable)
  void MulticastBroadcastLeavingMap();

  ABattleGameState();

  virtual void BeginPlay() override;

protected:

  virtual void HandleMatchIsWaitingToStart() override;
  virtual void HandleMatchHasStarted() override;
  virtual void HandleMatchHasEnded() override;
  virtual void HandleLeavingMap() override;

};
