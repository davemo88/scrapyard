// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "ScrapyardAbility.generated.h"

class UAbilityState;
class UAbilityStateActive;
class UAbilityStateInactive;
class UAbilityStateFiring;
class ARobotCharacter;

USTRUCT()
struct FPendingFireEvent
{
  GENERATED_BODY()

  UPROPERTY()
  bool bIsStartFire;
  UPROPERTY()
  uint8 FireModeNum;
  UPROPERTY()
  uint8 FireEventIndex;
  UPROPERTY()
  uint8 ZOffset;
  UPROPERTY()
  bool bClientFired;

  FPendingFireEvent()
    : bIsStartFire(false), FireModeNum(0), FireEventIndex(0), ZOffset(0), bClientFired(false) 
  {}
};

/**
 * 
 */
UCLASS()
class SCRAPYARD_API UScrapyardAbility : public UObject
{
  GENERATED_BODY()

public:

  UScrapyardAbility();

  UPROPERTY()
  ARobotCharacter* RobotOwner;

  friend class UAbilityState;
  friend class UAbilityStateActive;
  friend class UAbilityStateInactive;
  friend class UAbilityStateFiring;

  FString AbilityName;

  UFUNCTION()
  virtual void StartFire(uint8 FireModeNum);
  UFUNCTION()
  virtual void StopFire(uint8 FireModeNum);

  virtual bool BeginFiringSequence(uint8 FireModeNum, bool bClientFired);

  virtual void EndFiringSequence(uint8 FireModeNum);

  virtual bool WillSpawnShot(float DeltaTime);

  virtual bool CanFireAgain();

  virtual void FireShot();

  UFUNCTION()
  bool IsFiring() const;

  UFUNCTION()
  virtual float GetRefireTime(uint8 FireModeNum);

protected:
   
  UPROPERTY()
  UAbilityState* CurrentState;

  UPROPERTY()
  uint8 CurrentFireMode;
  
  UPROPERTY()
  UAbilityStateActive* ActiveState;
  UPROPERTY()
  UAbilityStateInactive* InactiveState;
  UPROPERTY()
  TArray<class UAbilityStateFiring*> FiringState;
  UPROPERTY()
  TArray<float> FireInterval;

  UPROPERTY()
  uint8 FireEventIndex;

public:

  inline ARobotCharacter* GetRobotOwner() const 
  {
    return RobotOwner;
  }

  inline uint8 GetCurrentFireMode()
  {
    return CurrentFireMode;
  }

  virtual void GotoState(UAbilityState* NewState);

  virtual void GotoActiveState();

  virtual void StateChanged() {}

  virtual uint8 GetNumFireModes() const
  {
    return FMath::Min3(255, FiringState.Num(), FireInterval.Num());
  }

  UFUNCTION()
  virtual void GotoFireMode(uint8 NewFireMode);

  UFUNCTION(Server, unreliable, WithValidation)
  virtual void ServerStartFire(uint8 FireModeNum, uint8 InFireEventIndex, bool bClientFired);

  UFUNCTION(Server, unreliable, WithValidation)
  virtual void ServerStopFire(uint8 FireModeNum, uint8 InFireEventIndex);
	
};
