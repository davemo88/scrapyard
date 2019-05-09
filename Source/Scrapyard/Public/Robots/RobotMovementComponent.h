// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Robots/RobotCharacter.h"
#include "Robots/RobotStats.h"
#include "RobotMovementComponent.generated.h"

UENUM(BlueprintType)
enum class ERobotMovementState : uint8
{
  MOVE_Idle     UMETA(DisplayName="Idle"),
  MOVE_Walk     UMETA(DisplayName="Walk"),
  MOVE_Boost    UMETA(DisplayName="Boost"),
  MOVE_Fly      UMETA(DisplayName="Fly"),
  MOVE_Fall     UMETA(DisplayName="Fall"),
  MOVE_Land     UMETA(DisplayName="Land")
};

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

  URobotMovementComponent();

  virtual void BeginPlay() override;

  virtual void UpdateFromCompressedFlags(uint8 Flags) override;

  virtual class FNetworkPredictionData_Client* GetPredictionData_Client() const override;
  
  virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) override;

  void SetRobotChar(ARobotCharacter* NewRobotChar);

  void UpdateFromRobotStats();

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

  ERobotMovementState GetRobotMovementState();

  void SetRobotMovementState(ERobotMovementState NewRobotMovementState);
  
protected:

  virtual void OnMovementModeChanged(EMovementMode PreviousMovementMode, uint8 PreviousCustomMode) override;

  UPROPERTY(Replicated)
  ERobotMovementState RobotMovementState;

  void UpdateRobotMovementState();

//NOTE: want this to be const
  UPROPERTY(EditAnywhere)
  float MassNormalizer;

  ARobotCharacter* RobotChar;

  FTimerHandle LandingTimerHandle;

  void OnLandingTimerExpired();

  friend class URobotTunerWidget;
  

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
