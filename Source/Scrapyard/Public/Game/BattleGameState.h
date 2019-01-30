// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Game/RobotGameState.h"
#include "BattleGameState.generated.h"


/**
 * 
 */
UCLASS()
class SCRAPYARD_API ABattleGameState : public ARobotGameState
{
  GENERATED_BODY()
      
public:

  ABattleGameState();

  virtual void BeginPlay() override;

};
