// Fill out your copyright notice in the Description page of Project Settings.


#include "RobotAnimInstance.h"
#include "Robots/RobotCharacter.h"

void URobotAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
  UE_LOG(LogTemp, Warning, TEXT("%s::NativeUpdateAnimation"), *GetName());
//  Super::NativeUpdateAnimation(DeltaSeconds);
//  UpdateMovementState();
//  MovementState = ERobotMovementState::MOVE_Walk;
  UE_LOG(LogTemp, Warning, TEXT("Movement State: %i"), MovementState);
  
}

void URobotAnimInstance::UpdateMovementState()
{
  if (ARobotCharacter* RoboChar = Cast<ARobotCharacter>(TryGetPawnOwner()))
  {
    UE_LOG(LogTemp, Warning, TEXT("anim instance char ok"));
    UCharacterMovementComponent* MovementComponent = RoboChar->GetCharacterMovement();
    if (MovementComponent->IsWalking()) 
    {
      float Speed = RoboChar->GetVelocity().Size();
      UE_LOG(LogTemp, Warning, TEXT("anim instance char walking - speed %f"), Speed);
      MovementState = Speed > 0.0f ? ERobotMovementState::MOVE_Walk : ERobotMovementState::MOVE_Idle;
    }
  }
}

