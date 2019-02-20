// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "RobotMovementComponent.generated.h"

/**
 * 
 */
UCLASS()
class SCRAPYARD_API URobotMovementComponent : public UCharacterMovementComponent
{
  GENERATED_BODY()
  
public:

  URobotMovementComponent();

  virtual void UpdateFromCompressedFlags(uint8 Flags) override;

  virtual class FNetworkPredictionData_Client* GetPredictionData_Client() const override;
  
  virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) override;

// for compressed flags
  uint8 bWantsToBoost : 1;

  bool bWasBoosting;

  virtual void SetBoosting(uint8 bBoosting);
  virtual void CheckBoostingInput();
  virtual void ClearBoostingInput();

  float BoostSpeedMultiplier;
  float BoostAccelerationMultiplier;
  
  float BoostHoldThresholdTime;

  virtual float GetMaxSpeed() const override;
  virtual float GetMaxAcceleration() const override;

  FTimerHandle BoostHoldTimerHandle;

  UFUNCTION()
  void BoostHoldTimerExpired();


};


class FSavedMove_Robot : public FSavedMove_Character
{
  public:
    typedef FSavedMove_Character Super;

    virtual void Clear() override;

    virtual uint8 GetCompressedFlags() const override;

    virtual bool CanCombineWith(const FSavedMovePtr& NewMove, ACharacter* Character, float MaxDelta) const override;

    virtual void SetMoveFor(ACharacter* Character, float InDeltaTime, FVector const& NewAccel, class FNetworkPredictionData_Client_Character& ClientData) override;

    virtual void PrepMoveFor(class ACharacter* Character) override;

    uint8 bSavedWantsToBoost : 1; 

};

class FNetworkPredictionData_Client_Robot : public FNetworkPredictionData_Client_Character
{
  public:

    FNetworkPredictionData_Client_Robot(const UCharacterMovementComponent& ClientMovement);

    typedef FNetworkPredictionData_Client_Character Super;

    virtual FSavedMovePtr AllocateNewMove() override;
};
