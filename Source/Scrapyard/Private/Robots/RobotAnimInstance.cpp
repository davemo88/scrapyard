// Fill out your copyright notice in the Description page of Project Settings.


#include "RobotAnimInstance.h"
#include "Robots/RobotCharacter.h"
#include "Robots/RobotMovementComponent.h"

void URobotAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
  UE_LOG(LogTemp, Warning, TEXT("%s::NativeUpdateAnimation"), *GetName());
  Super::NativeUpdateAnimation(DeltaSeconds);
  UpdateMovementState();
//  MovementState = ERobotMovementState::MOVE_Walk;
  UE_LOG(LogTemp, Warning, TEXT("Movement State: %i"), MovementState);
  
}

void URobotAnimInstance::UpdateMovementState()
{
//TODO: maybe set some refs to these so don't have to cast all the time
  if (ARobotCharacter* RoboChar = Cast<ARobotCharacter>(TryGetPawnOwner()))
  {
    URobotMovementComponent* MovementComponent = Cast<URobotMovementComponent>(RoboChar->GetCharacterMovement());
    if (MovementComponent)
    {
      MovementState = MovementComponent->GetMovementState();
    }
  }
}

