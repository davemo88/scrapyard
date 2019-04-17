// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "AbilityState.generated.h"

class ARobotCharacter;

/**
 * the Within specifier will generate some functions such as GetOuterAScrapyardAbility()
 */
UCLASS(Within=ScrapyardAbility)
class SCRAPYARD_API UAbilityState : public UObject
{
  GENERATED_BODY()

public:

  ARobotCharacter* GetRobotOwner() const;

  UWorld* GetWorld() const override;
  
  virtual void BeginState(const UAbilityState* PrevState) {};

  virtual void EndState() {};

  virtual bool BeginFiringSequence(uint8 FireModeNum, bool bClientFired) {
    return false;
  }
  virtual void EndFiringSequence(uint8 FireModeNum) {};

  virtual bool WillSpawnShot(float DeltaTime)
  {
    return false;
  }

  virtual bool IsFiring() const
  {
    return false;
  }

//  virtual void Tick(float DeltaTime) {};
  
};
