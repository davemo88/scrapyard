// Fill out your copyright notice in the Description page of Project Settings.


#include "TargetingProfile.h"
#include "Robots/RobotCharacter.h"
#include "Player/RobotPlayerController.h"

FVector UTargetingProfile::GetTargetingOffset(ARobotCharacter* Robot) const
{
//  UE_LOG(LogTemp, Warning, TEXT("%s::GetTargetingOffset"), *GetName());
  if (AScrapyardPlayerController* Controller = Robot->GetController<ARobotPlayerController>())
  {
    FVector TargetingOffset = Controller->PlayerCameraManager->GetCameraLocation() - Robot->GetActorLocation(); 
    UE_LOG(LogTemp, Warning, TEXT("GetTargetingOffset - Robot Location %s"), *Robot->GetActorLocation().ToString());
    UE_LOG(LogTemp, Warning, TEXT("GetTargetingOffset - Camera Location %s"), *Controller->PlayerCameraManager->GetCameraLocation().ToString());
    UE_LOG(LogTemp, Warning, TEXT("GetTargetingOffset - Targeting Offset %s"), *TargetingOffset.ToString());
  }
  return FVector::ZeroVector;
}

bool UTargetingProfile::IsTargeted(ARobotCharacter* Robot, AActor* Target)
{
//  UE_LOG(LogTemp, Warning, TEXT("%s::IsTargeted"), *GetName());
  return false;
}

FVector UTargetingProfile::GetTargetRelativeLocation(FVector TargetingLocation, FRotator TargetingRotation, FVector TargetLocation) const
{
  return TargetingRotation.GetInverse().RotateVector(TargetLocation-TargetingLocation);
}

FVector UTargetingProfile::GetTargetingLocation(ARobotCharacter* Robot) const
{
  return Robot->GetActorLocation() + GetTargetingOffset(Robot);
}

FRotator UTargetingProfile::GetTargetingRotation(ARobotCharacter* Robot) const
{
  return Robot->GetViewRotation();
}

bool UTargetingProfile::IsInRange(FVector TargetRelativeLocation, FVector TargetingOffset) const
{
  if (TargetRelativeLocation.X < Range && TargetRelativeLocation.X > FMath::Abs(TargetingOffset.X))
  {
    return true;
  }
  else
  {
    return false;
  }
}

