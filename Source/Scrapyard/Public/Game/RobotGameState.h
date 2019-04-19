// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameState.h"
#include "RobotGameState.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnMatchTimerStartedDelegate);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnMatchTimerUpdatedDelegate);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnMatchTimerExpiredDelegate);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnMatchTimerStoppedDelegate);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnTargetableAddedDelegate, AActor*, Targetable);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnTargetableRemovedDelegate, AActor*, Targetable);

/**
 * 
 */
UCLASS()
class SCRAPYARD_API ARobotGameState : public AGameState
{
  GENERATED_BODY()

public:

  UFUNCTION(NetMulticast, Reliable)
  void MulticastStartMatchTimer(uint32 Seconds);

  UFUNCTION(NetMulticast, Reliable)
  void MulticastStopMatchTimer();

  uint32 GetMatchTimerSecondsRemaining() const;

  bool IsMatchTimerActive() const;

  FOnMatchTimerStartedDelegate OnMatchTimerStartedDelegate;
  FOnMatchTimerUpdatedDelegate OnMatchTimerUpdatedDelegate;
  FOnMatchTimerExpiredDelegate OnMatchTimerExpiredDelegate;
  FOnMatchTimerStoppedDelegate OnMatchTimerStoppedDelegate;

  FOnTargetableAddedDelegate OnTargetableAddedDelegate;
  FOnTargetableRemovedDelegate OnTargetableRemovedDelegate;

  UFUNCTION(NetMulticast, Reliable)
  void MulticastAddTargetable(AActor* Actor);

  UFUNCTION(NetMulticast, Reliable)
  void MulticastRemoveTargetable(AActor* Actor);

  void AddTargetable(AActor* Actor);
  void RemoveTargetable(AActor* Actor);

  UPROPERTY()
  TArray<AActor*> TargetableActors;

protected:
  FTimerHandle MatchTimerHandle;

  uint32 MatchTimerSecondsRemaining;

  bool MatchTimerExpired;

  UFUNCTION()
  void MatchTimer();

};
