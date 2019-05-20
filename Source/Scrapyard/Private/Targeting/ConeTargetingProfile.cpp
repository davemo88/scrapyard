// Fill out your copyright notice in the Description page of Project Settings.


#include "ConeTargetingProfile.h"

UConeTargetingProfile::UConeTargetingProfile()
{
//TODO: set from weapon
  Range = 2000;
  ConeAngle = 3.1415f/16.0f;
}

bool UConeTargetingProfile::IsTargeted(ARobotCharacter* Robot, AActor* Target)
{

  FVector TargetRelativeLocation = GetTargetRelativeLocation(GetTargetingLocation(Robot), GetTargetingRotation(Robot), Target->GetActorLocation());

  if (!IsInRange(TargetRelativeLocation, GetTargetingOffset(Robot)))
  {
    return false;
  }

  float ConeRadius = GetConeRadius(FMath::Abs(TargetRelativeLocation.X));
  float OtherRadius = FVector::Dist(FVector(TargetRelativeLocation.X,0,0), TargetRelativeLocation); 

  return OtherRadius < ConeRadius;

}

float UConeTargetingProfile::GetConeRadius(float Distance)
{
  return FMath::Tan(ConeAngle) * Distance;
}

TArray<FVector> UConeTargetingProfile::InitFaceVerts()
{
  UE_LOG(LogTemp, Warning, TEXT("%s::InitFaceVerts"), *GetName());
  TArray<FVector> FaceVerts;
  float FaceRadius = GetConeRadius(Range);
// 12 points around the circular face of the cone
  uint NumPoints = 16;
//  float RotationIncrement = (2 * GlobalVectorConstants::Pi[0]) / NumPoints;
  float RotationIncrement = 360.f / NumPoints;
  FVector NextVert;
  for (uint i = 0; i < NumPoints; i++)
  {
    NextVert = FRotator(0, 0, i*RotationIncrement).RotateVector(FVector(Range,0,FaceRadius));
//    UE_LOG(LogTemp, Warning, TEXT("Next Vert %f - %s"), i*RotationIncrement, *NextVert.ToString());
    FaceVerts.Add(NextVert);
  }
  return FaceVerts;
}

