// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "UObject/NoExportTypes.h"
#include "Game/ScrapyardDamageType.h"
#include "ScrapyardAbility.generated.h"

class UAbilityState;
class UAbilityStateActive;
class UAbilityStateInactive;
class UAbilityStateFiring;
class ARobotCharacter;

USTRUCT()
struct FInstantHitDamageInfo
{
  GENERATED_BODY()

  UPROPERTY()
  int32 Damage = 100;
  UPROPERTY()
  TSubclassOf<UDamageType> DamageType = UScrapyardDamageType::StaticClass();
  UPROPERTY()
  float Momentum = 0.0f;
  UPROPERTY()
  float TraceRange = 10000.0f;
  UPROPERTY()
  float TraceHalfSize = 0.0f;
  UPROPERTY()
  float ConeDotAngle = 0.0f;

};

USTRUCT()
struct FPendingFireEvent
{
  GENERATED_BODY()

  UPROPERTY()
  bool bIsStartFire = false;
  UPROPERTY()
  uint8 FireModeNum = 0;
  UPROPERTY()
  uint8 FireEventIndex = 0;
  UPROPERTY()
  uint8 ZOffset = 0;
  UPROPERTY()
  bool bClientFired = false;

};

/**
 * 
 */
UCLASS()
class SCRAPYARD_API AScrapyardAbility : public AActor
//class SCRAPYARD_API AScrapyardAbility : public UObject
{
  GENERATED_BODY()

public:

  AScrapyardAbility();

  UPROPERTY(Replicated)
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

  virtual void FireInstantHit(bool bDealDamage = true, FHitResult* OutHit = NULL);

  UFUNCTION()
  virtual FVector GetFireStartLoc(uint8 FireMode = 255);

  UFUNCTION()
  virtual FRotator GetBaseFireRotation();

  UPROPERTY()
  TArray<FInstantHitDamageInfo> InstantHitInfo;

//  UFUNCTION()
//  virtual FRotator GetAdjustedAim(FVector StartFireLoc);
  
  virtual void HitScanTrace(const FVector& StartLocation, const FVector& EndTrace, float TraceRadius, FHitResult& Hit, float PredictionTime);

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

  UFUNCTION(Server, Reliable, WithValidation)
  virtual void ServerStartFire(uint8 FireModeNum, uint8 InFireEventIndex, bool bClientFired);

  UFUNCTION(Server, Reliable, WithValidation)
  virtual void ServerStopFire(uint8 FireModeNum, uint8 InFireEventIndex);

  UPROPERTY()
  bool bTrackHitScanReplication;

  UPROPERTY()
  ARobotCharacter* HitScanHitChar;

  UPROPERTY()
  FVector_NetQuantize HitScanCharLoc;
	
  UPROPERTY()
  FVector_NetQuantize HitScanStart;

  UPROPERTY()
  FVector_NetQuantize HitScanEnd;

  UPROPERTY()
  float HitScanHeight;

  UPROPERTY()
  uint8 HitScanIndex;

  UPROPERTY()
  float HitScanTime;

  UPROPERTY()
  ARobotCharacter* ReceivedHitScanHitChar;
 
  UPROPERTY()
  uint8 ReceivedHitScanIndex;
 
  UFUNCTION(Server, Unreliable, WithValidation)
  void ServerHitScanHit(ARobotCharacter* HitScanChar, uint8 HitScanEventIndex);
 
  UFUNCTION (Client, Unreliable)
  void ClientMissedHitScan(FVector_NetQuantize MissedHitScanStart, FVector_NetQuantize MissedHitScanEnd, FVector_NetQuantize MissedHitScanLoc, float MissedHitScanTime, uint8 MissedHitScanIndex);

};
