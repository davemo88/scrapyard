// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "ScrapyardAbility.generated.h"

//class UAbilityState;
//class UAbilityStateActive;
//class UAbilityStateInactive;
//class UAbilityStateFiring;
class ARobotCharacter;

/**
 * 
 */
UCLASS()
class SCRAPYARD_API UScrapyardAbility : public UObject
{
  GENERATED_BODY()

public:

  friend class UAbilityState;
  friend class UAbilityStateActive;
  friend class UAbilityStateInactive;
  friend class UAbilityStateFiring;

  UFUNCTION()
  virtual void StartFire(uint8 FireModeNum);
  UFUNCTION()
  virtual void StopFire(uint8 FireModeNum);

protected:
   
  UPROPERTY()
  ARobotCharacter* RobotOwner;

  UPROPERTY()
  UAbilityState* CurrentState;

  UPROPERTY()
  uint8 CurrentFireMode;
  
  UPROPERTY()
  UAbilityState* ActiveState;
  UPROPERTY()
  UAbilityState* InactiveState;
  UPROPERTY()
  TArray<class UAbilityStateFiring*> FiringState;
  UPROPERTY()
  TArray<float> FireInterval;

public:

  inline ARobotCharacter* GetRobotOwner() const 
  {
    return RobotOwner;
  }

  inline uint8 GetCurrentFireMode()
  {
    return CurrentFireMode;
  }

////  virtual void GotoState(class UAbilityState* NewState);
  virtual void GotoState(UAbilityState* NewState);

  virtual void StateChanged() {}

  virtual uint8 GetNumFireModes() const
  {
    return FMath::Min3(255, FiringState.Num(), FireInterval.Num());
  }

  UFUNCTION()
  virtual void GotoFireMode(uint8 NewFireMode);
	
};
