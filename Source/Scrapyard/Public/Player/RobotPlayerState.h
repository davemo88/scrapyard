// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "RobotPlayerState.generated.h"

/**
 * 
 */
UCLASS()
class SCRAPYARD_API ARobotPlayerState : public APlayerState
{
  GENERATED_BODY()
  
public:
  
  void AddOpponent(APlayerState* PlayerState);

  UPROPERTY()
  TArray<APlayerState*> Opponents;

protected:

  UFUNCTION(Client, Reliable)
  void ClientAddOpponent(APlayerState* PlayerState);
  
};
