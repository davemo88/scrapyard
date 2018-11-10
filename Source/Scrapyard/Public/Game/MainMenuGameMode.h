// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "MainMenuGameMode.generated.h"

/**
 * 
 */
UCLASS()
class SCRAPYARD_API AMainMenuGameMode : public AGameModeBase
{
  GENERATED_BODY()

public:

  AMainMenuGameMode();

  virtual void RestartPlayer(class AController* NewPlayer) override;

  virtual TSubclassOf<AGameSession> GetGameSessionClass() const override;

protected:

  void BeginSession();

  void ShowLoadingScreen();
};
