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

  void PostLogin(APlayerController* NewPlayer) override;
  
//  virtual bool ReadyToStartMatch() override;

protected:
    
  void HandleMatchIsWaitingToStart() override;
  void HandleMatchHasStarted() override;
  void HandleMatchHasEnded() override;
  void HandleMatchAborted() override;
  void HandleLeavingMap() override;
  void HandleStartingNewPlayer_Implementation(APlayerController* NewPlayer) override;

  FTimerHandle StartMatchTimerHandle;

};
