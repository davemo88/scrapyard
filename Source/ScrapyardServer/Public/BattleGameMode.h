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

          void PostLogin(APlayerController* NewPlayer);

    protected:
          
          void HandleMatchIsWaitingToStart();
          void HandleMatchHasStarted();
          void HandleMatchHasEnded();
          void HandleMatchAborted();
          void HandleLeavingMap();
          void HandleStartingNewPlayer_Implementation(APlayerController* NewPlayer);
};
