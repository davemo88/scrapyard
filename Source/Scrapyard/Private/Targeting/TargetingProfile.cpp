// Fill out your copyright notice in the Description page of Project Settings.


#include "TargetingProfile.h"
#include "Robots/RobotCharacter.h"
#include "Player/RobotPlayerController.h"

FVector UTargetingProfile::GetTargetingOffset(ARobotCharacter* Robot) const
{
//NOTE: perhaps update this to use camera position, e.g. if it's bumping up against something
  return Robot->CameraBoom->SocketOffset + FVector(-Robot->CameraBoom->TargetArmLength,0,0);
}

bool UTargetingProfile::IsTargeted(ARobotCharacter* Robot, AActor* Target)
{
  return false;
}

FVector UTargetingProfile::GetTargetRelativeLocation(FVector TargetingLocation, FRotator TargetingRotation, FVector TargetLocation) const
{
  return TargetingRotation.UnrotateVector(TargetLocation-TargetingLocation);
}

FVector UTargetingProfile::GetLocationRelativeToView(ARobotCharacter* Robot, AActor* Target) const
{
  return Robot->GetViewRotation().UnrotateVector(Target->GetActorLocation() - Robot->GetActorLocation());
}

FVector UTargetingProfile::GetTargetingLocation(ARobotCharacter* Robot) const
{
  return Robot->GetActorLocation() + GetTargetingRotation(Robot).RotateVector(GetTargetingOffset(Robot));
}

FRotator UTargetingProfile::GetTargetingRotation(ARobotCharacter* Robot) const
{
  return Robot->GetViewRotation();
}

bool UTargetingProfile::IsInRange(FVector TargetRelativeLocation, FVector TargetingOffset) const
{
  UE_LOG(LogTemp, Warning, TEXT("%s::IsInRange - Distance to Target: %f"), *GetName(), TargetRelativeLocation.X);
  return (TargetRelativeLocation.X < Range && TargetRelativeLocation.X > -TargetingOffset.X);
}

bool UTargetingProfile::IsInRange(ARobotCharacter* Robot, AActor* Target) const
{
  FVector LocationRelativeToView = GetLocationRelativeToView(Robot, Target);
//  UE_LOG(LogTemp, Warning, TEXT("%s::IsInRange - Distance to Target: %f"), *GetName(), LocationRelativeToView.Size());
  return (LocationRelativeToView.Size() < Range && LocationRelativeToView.X > GetTargetingOffset(Robot).X);
}

