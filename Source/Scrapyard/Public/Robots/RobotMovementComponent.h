// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Robots/RobotCharacter.h"
#include "RobotMovementComponent.generated.h"

USTRUCT()
struct FNewTuneParams
{
  GENERATED_BODY()

  float GroundFriction;
  float BoostHoldThresholdTime;
};
/**
 * 
 */
UCLASS()
class SCRAPYARD_API URobotMovementComponent : public UCharacterMovementComponent
{
  GENERATED_BODY()
  
public:

  virtual void BeginPlay() override;

  URobotMovementComponent();

  virtual void UpdateFromCompressedFlags(uint8 Flags) override;

  virtual class FNetworkPredictionData_Client* GetPredictionData_Client() const override;
  
  virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) override;

// for compressed flags
  uint8 bBoostInput : 1;
  uint8 bPrevBoostInput : 1;

  bool bBoosting;
  bool bWasBoosting;

  virtual void SetBoostInput(uint8 bNewBoostInput);
  virtual void CheckBoostInput();
  virtual void ClearBoostInput();

  virtual void StartBoosting();
  virtual void StopBoosting();

  virtual void HandleBoosting();

  float BoostSpeedMultiplier;
  float BoostAccelerationMultiplier;
  
  float BoostHoldThresholdTime;

  virtual float GetMaxSpeed() const override;
  virtual float GetMaxAcceleration() const override;

  FTimerHandle BoostHoldTimerHandle;

  UFUNCTION()
  void BoostHoldTimerExpired();
  
  enum ScrapyardMovementModes
  {
    MOVE_GroundBoost   = 0x01,
    MOVE_AirBoost      = 0x02,
    MOVE_GroundDash    = 0x04,
    MOVE_AirDash       = 0x08,
  };

protected:

  friend class URobotTunerWidget;
  
  ARobotCharacter* RobotChar;

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

    uint8 bSavedBoostInput : 1; 

};

class FNetworkPredictionData_Client_Robot : public FNetworkPredictionData_Client_Character
{
  public:

    FNetworkPredictionData_Client_Robot(const UCharacterMovementComponent& ClientMovement);

    typedef FNetworkPredictionData_Client_Character Super;

    virtual FSavedMovePtr AllocateNewMove() override;
};
