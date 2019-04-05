// Fill out your copyright notice in the Description page of Project Settings.


#include "RectangularTargetingProfile.h"

URectangularTargetingProfile::URectangularTargetingProfile()
{
  Range = 2000.0f;
  VerticalAngle = 3.1415f/16.0f;
  HorizontalAngle = 3.1415f/12.0f;

}

bool URectangularTargetingProfile::IsTargeted(FVector OtherRelativeLocation)
{
//  UE_LOG(LogTemp, Warning, TEXT("%s::IsTargeted"), *GetName());
  if (OtherRelativeLocation.X > Range || OtherRelativeLocation.X < -TargetingOffset.X)
  {
    return false;
  }

  float HorizontalTargetingRange = FMath::Tan(HorizontalAngle) * OtherRelativeLocation.X;
  float VerticalTargetingRange = FMath::Tan(VerticalAngle) * OtherRelativeLocation.X;

  return FMath::Abs(OtherRelativeLocation.Y) < HorizontalTargetingRange && FMath::Abs(OtherRelativeLocation.Z) < VerticalTargetingRange;

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

