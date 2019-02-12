// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Ability/AbilityState.h"
#include "Ability/ScrapyardAbility.h"
#include "Robots/RobotCharacter.h"
#include "Runtime/Engine/Classes/Engine/EngineTypes.h"
#include "AbilityStateFiring.generated.h"

/**
 * 
 */
UCLASS()
class SCRAPYARD_API UAbilityStateFiring : public UAbilityState
{
  GENERATED_BODY()

  virtual void BeginState(const UAbilityState* PrevState) override;
  virtual void EndState() override;
  virtual bool BeginFiringSequence(uint8 FireModeNum, bool bClientFired) override;

  virtual void FireShot();

  virtual bool WillSpawnShot(float DeltaTime);

  virtual void RefireCheckTimer();

  FTimerHandle RefireCheckHandle;

// bFinishedCooldown = true;

//  bool bNetDelayedShot;

public:
  virtual void PendingFireStarted() {}
  virtual void PendingFireStopped() {}
};

