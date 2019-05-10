// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "Robots/RobotMovementComponent.h"
#include "RobotAnimInstance.generated.h"

/**
 * 
 */
UCLASS(Transient, Blueprintable)
class SCRAPYARD_API URobotAnimInstance : public UAnimInstance
{
  GENERATED_BODY()

public:

  virtual void NativeUpdateAnimation(float DeltaSeconds) override;
  
  virtual void NativePostEvaluateAnimation() override;

protected:

  void UpdateMovementState(float DeltaSeconds);
  void UpdateBodyRotation(float DeltaSeconds);

  UPROPERTY(BlueprintReadOnly)
  ERobotMovementState MovementState;

  UPROPERTY(BlueprintReadOnly)
  FRotator BodyRotation;

};
