// Fill out your copyright notice in the Description page of Project Settings.


#include "RobotAnimInstance.h"
#include "Robots/RobotCharacter.h"
#include "Robots/RobotMovementComponent.h"
#include "Math/Rotator.h"

void URobotAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
//  UE_LOG(LogTemp, Warning, TEXT("%s::NativeUpdateAnimation"), *GetName());
  Super::NativeUpdateAnimation(DeltaSeconds);

  UpdateMovementState(DeltaSeconds);
//  UE_LOG(LogTemp, Warning, TEXT("Movement State: %i"), MovementState);
//
  UpdateBodyRotation(DeltaSeconds);
  
}

void URobotAnimInstance::UpdateMovementState(float DeltaSeconds)
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

void URobotAnimInstance::UpdateBodyRotation(float DeltaSeconds)
{
  FRotator NewRotation = FRotator::ZeroRotator;

  if (ARobotCharacter* Owner = Cast<ARobotCharacter>(TryGetPawnOwner()))
  {
//TODO: client only
// 
    float RelativeYaw = Owner->GetActorRotation().UnrotateVector(Owner->GetVelocity()).Rotation().Yaw; 
    float IntermediateYaw = FMath::FInterpTo(BodyRotation.Yaw,RelativeYaw,DeltaSeconds,5);
//    NewRotation = NewRotation + FRotator(0.0f, IntermediateYaw, 0.0f);

    FRotator RelAccelRotation  = Owner->GetActorRotation().UnrotateVector(Owner->GetCharacterMovement()->GetCurrentAcceleration()).Rotation();

    FVector Accel = Owner->GetCharacterMovement()->GetCurrentAcceleration();

    FVector RelAccel = Owner->GetActorRotation().UnrotateVector(Accel);

    float TiltMax = 8.0f;

    float TargetPitch = FMath::Clamp(RelAccel.X/50.0f,-TiltMax,TiltMax);
    float TargetRoll = FMath::Clamp(RelAccel.Y/50.0f,-TiltMax,TiltMax);

//TODO: why are pitch and roll seemingly reversed?
    float IntermediatePitch = FMath::FInterpTo(BodyRotation.Roll, TargetPitch, DeltaSeconds, 3);
    float IntermediateRoll = FMath::FInterpTo(BodyRotation.Pitch, TargetRoll, DeltaSeconds, 3);

    NewRotation = FRotator(IntermediateRoll, IntermediateYaw, IntermediatePitch);

//    UE_LOG(LogTemp, Warning, TEXT("RelAccel: %s"), *RelAccel.ToString());
//    UE_LOG(LogTemp, Warning, TEXT("New Body Rotation: %s"), *NewRotation.ToString());

  }
  BodyRotation = NewRotation;
}

void URobotAnimInstance::NativePostEvaluateAnimation()
{
  if (ARobotCharacter* Owner = Cast<ARobotCharacter>(TryGetPawnOwner()))
  {
//    Owner->RobotBodyComponent->AddRelativeRotation(BodyRotation - RobotBodyComponent->RelativeRotation);
    Owner->RobotBodyComponent->SetRelativeRotation(BodyRotation + FRotator(0.0f,-90.0f,0.0f));
  }
}
