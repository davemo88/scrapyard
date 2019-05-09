// Fill out your copyright notice in the Description page of Project Settings.


#include "RobotAnimInstance.h"
#include "Robots/RobotCharacter.h"
#include "Robots/RobotMovementComponent.h"

void URobotAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
//  UE_LOG(LogTemp, Warning, TEXT("%s::NativeUpdateAnimation"), *GetName());
  Super::NativeUpdateAnimation(DeltaSeconds);

  UpdateMovementState();
//  UE_LOG(LogTemp, Warning, TEXT("Movement State: %i"), MovementState);
//
  UpdateBodyRotation();
  
}

void URobotAnimInstance::UpdateMovementState()
{
//TODO: maybe set some refs to these so don't have to cast all the time
  if (ARobotCharacter* RoboChar = Cast<ARobotCharacter>(TryGetPawnOwner()))
  {
    URobotMovementComponent* MovementComponent = Cast<URobotMovementComponent>(RoboChar->GetCharacterMovement());
    if (MovementComponent)
    {
      MovementState = MovementComponent->GetRobotMovementState();
    }
  }
}

void URobotAnimInstance::UpdateBodyRotation()
{
  FRotator NewRotation = FRotator::ZeroRotator;
//  FRotator NewRotation = FRotator(0.0f,90.0f,0.0f);

  if (ARobotCharacter* Owner = Cast<ARobotCharacter>(TryGetPawnOwner()))
  {
//TODO: client only
//
    float RelativeYaw = Owner->GetActorRotation().UnrotateVector(Owner->GetVelocity()).Rotation().Yaw; 
    NewRotation = NewRotation + FRotator(0.0f, RelativeYaw, 0.0f);

    FRotator RelAccelRotation  = Owner->GetActorRotation().UnrotateVector(Owner->GetCharacterMovement()->GetCurrentAcceleration()).Rotation();

    FVector Accel = Owner->GetCharacterMovement()->GetCurrentAcceleration();
    FVector RelAccel = Owner->GetActorRotation().UnrotateVector(Owner->GetCharacterMovement()->GetCurrentAcceleration());

//    UE_LOG(LogTemp, Warning, TEXT("Char Accel: %s RelAccel: %s"), *Accel.ToString(), *RelAccel.ToString());

    NewRotation = NewRotation + FRotator(FMath::Clamp(-RelAccel.Y/204.8f, -10.0f, 10.0f), 0.0, FMath::Clamp(RelAccel.X/204.8f, -10.0f, 10.f));
  }

  BodyRotation = NewRotation;
}

