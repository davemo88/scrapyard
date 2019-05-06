// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "RobotAnimInstance.generated.h"

UENUM(BlueprintType)
enum class ERobotMovementState : uint8
{
  MOVE_Idle     UMETA(DisplayName="Idle"),
  MOVE_Walk     UMETA(DisplayName="Walk"),
  MOVE_Fly      UMETA(DisplayName="Fly"),
  MOVE_Fall     UMETA(DisplayName="Fall"),
  MOVE_Land     UMETA(DisplayName="Land")
};

/**
 * 
 */
UCLASS(Transient, Blueprintable)
class SCRAPYARD_API URobotAnimInstance : public UAnimInstance
{
  GENERATED_BODY()

public:

  virtual void NativeUpdateAnimation(float DeltaSeconds) override;

protected:

  UFUNCTION(BlueprintCallable)
  void UpdateMovementState();

  UPROPERTY(BlueprintReadWrite)
  ERobotMovementState MovementState;
	
};
