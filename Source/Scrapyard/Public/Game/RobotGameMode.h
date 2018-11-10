// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "RobotGameMode.generated.h"

class AGameSession;

/**
 * 
 */
UCLASS()
class SCRAPYARD_API ARobotGameMode : public AGameMode
{
  GENERATED_BODY()

public:

  ARobotGameMode();

  void PostLogin(APlayerController* NewPlayer) override;
  
  virtual TSubclassOf<AGameSession> GetGameSessionClass() const override;  
  
};
