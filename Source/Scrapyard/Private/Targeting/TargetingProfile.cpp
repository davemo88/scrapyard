// Fill out your copyright notice in the Description page of Project Settings.


#include "TargetingProfile.h"
#include "Robots/RobotCharacter.h"
#include "Abilities/ProjectileAbility.h"
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
  UE_LOG(LogTargeting, Log, TEXT("%s::IsInRange - Distance to Target: %f"), *GetName(), TargetRelativeLocation.X);
  return (TargetRelativeLocation.X < Range && TargetRelativeLocation.X > -TargetingOffset.X);
}

bool UTargetingProfile::IsInRange(ARobotCharacter* Robot, AActor* Target) const
{
  FVector LocationRelativeToView = GetLocationRelativeToView(Robot, Target);
//  UE_LOG(LogTargeting, Log, TEXT("%s::IsInRange - Distance to Target: %f"), *GetName(), LocationRelativeToView.Size());
  return (LocationRelativeToView.Size() < Range && LocationRelativeToView.X > GetTargetingOffset(Robot).X);
}

FVector UTargetingProfile::GetPredictedTargetLocation(AActor* Target, float DeltaTime)
{
  return Target->GetActorLocation() + DeltaTime * Target->GetVelocity();
}

FVector UTargetingProfile::GetPredictedTargetLocation(AActor* Source, AActor* Target, AProjectileAbility* ProjectileAbility)
{
  FVector ToTarget = Target->GetActorLocation() - Source->GetActorLocation();
  FVector TargetVelocity = Target->GetVelocity();

  float ProjectileSpeed = ProjectileAbility->GetProjectileSpeed(); 

// for quadratic formula
  float a = FVector::DotProduct(TargetVelocity, TargetVelocity) - FMath::Square(ProjectileSpeed);
  float b = 2.0f * FVector::DotProduct(TargetVelocity, ToTarget);
  float c = FVector::DotProduct(ToTarget, ToTarget);

// time at which sphere emanating from source at ProjectileSpeed will intersect with Target moving at TargetVelocity
  float t = 0.0f;

// discriminant
  float d = FMath::Square(b) - 4.0f * a * c;
// if there's a valid solution
  if (d >= 0)
  {
    t = (-b + FMath::Sqrt(d))/(2.0f * a);
  }

  return Target->GetActorLocation() + t * TargetVelocity;
  
}
