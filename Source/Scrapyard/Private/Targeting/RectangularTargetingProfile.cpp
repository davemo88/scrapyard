// Fill out your copyright notice in the Description page of Project Settings.


#include "RectangularTargetingProfile.h"

URectangularTargetingProfile::URectangularTargetingProfile()
{
  Range = 3000.0f;
  VerticalAngle = 3.1415f/16.0f;
  HorizontalAngle = 3.1415f/12.0f;

}

bool URectangularTargetingProfile::IsTargeted(ARobotCharacter* Robot, AActor* Target)
{
//  UE_LOG(LogTemp, Warning, TEXT("%s::IsTargeted"), *GetName());
  FVector TargetRelativeLocation = GetTargetRelativeLocation(GetTargetingLocation(Robot), GetTargetingRotation(Robot), Target->GetActorLocation());

  if (!IsInRange(Robot, Target))
  {
    return false;
  }

  float HorizontalTargetingRange = FMath::Tan(HorizontalAngle) * TargetRelativeLocation.X;
  float VerticalTargetingRange = FMath::Tan(VerticalAngle) * TargetRelativeLocation.X;

  return FMath::Abs(TargetRelativeLocation.Y) < HorizontalTargetingRange && FMath::Abs(TargetRelativeLocation.Z) < VerticalTargetingRange;

}

TArray<FVector> URectangularTargetingProfile::InitFaceVerts()
{
  TArray<FVector> FaceVerts;

  float HorizontalOffset = FMath::Tan(HorizontalAngle) * Range;
  float VerticalOffset = FMath::Tan(VerticalAngle) * Range;

  FaceVerts.Add(FVector(Range, HorizontalOffset, VerticalOffset));
  FaceVerts.Add(FVector(Range, HorizontalOffset, -VerticalOffset));
  FaceVerts.Add(FVector(Range, -HorizontalOffset, -VerticalOffset));
  FaceVerts.Add(FVector(Range, -HorizontalOffset, VerticalOffset));

  return FaceVerts;
}

