// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/AbilityState.h"
#include "AbilityStateActive.generated.h"

/**
 * 
 */
UCLASS()
class SCRAPYARD_API UAbilityStateActive : public UAbilityState
{
  GENERATED_BODY()

  virtual void BeginState(const UAbilityState* PrevState) override;
  virtual bool BeginFiringSequence(uint8 FireModeNum, bool bClientFire) override;
  virtual bool WillSpawnShot(float DeltaTime) override;

};
