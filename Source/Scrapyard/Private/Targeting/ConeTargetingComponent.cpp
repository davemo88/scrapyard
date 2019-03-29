// Fill out your copyright notice in the Description page of Project Settings.


#include "ConeTargetingComponent.h"
#include "Math/UnrealMathVectorConstants.h"

UConeTargetingComponent::UConeTargetingComponent()
{
  ConeLength = 2000;
  ConeAngle = 3.1415f/16.0f;

//  FaceCenter = FVector(ConeLength,0,0);
//  FaceRadius = FMath::Tan(ConeAngle) * ConeLength;

  TargetingWidget = UTargetingWidget::StaticClass();
}

bool UConeTargetingComponent::IsTargetable(AActor* OtherActor)
{
//TODO: should be relative to camera
  FVector OtherRelativeLocation = OtherActor->GetActorLocation()-(GetOwner()->GetActorLocation() + FVector(-350,0,130));

  if (OtherRelativeLocation.X > ConeLength || OtherRelativeLocation.X < 0)
  {
    UE_LOG(LogTemp, Warning, TEXT("Out of Range - X = %f"), OtherRelativeLocation.X);
    return false;
  }

  float ConeRadius = GetConeRadius(OtherRelativeLocation.X);
  float OtherRadius = FVector::Dist(FVector(OtherRelativeLocation.X,0,0), OtherRelativeLocation); 

  UE_LOG(LogTemp, Warning, TEXT("X = %f, ConeRadius = %f, OtherRadius = %f"), OtherRelativeLocation.X, ConeRadius, OtherRadius);

  return OtherRadius < ConeRadius;

}

float UConeTargetingComponent::GetRange()
{
  return ConeLength;
}

float UConeTargetingComponent::GetConeRadius(float Distance)
{
  return FMath::Tan(ConeAngle) * Distance;
}

TArray<FVector> UConeTargetingComponent::InitFaceVerts()
{
  UE_LOG(LogTemp, Warning, TEXT("%s::InitFaceVerts"), *GetName());
  TArray<FVector> FaceVerts;
  float FaceRadius = GetConeRadius(GetRange());
// 12 points around the circular face of the cone
  uint NumPoints = 16;
//  float RotationIncrement = (2 * GlobalVectorConstants::Pi[0]) / NumPoints;
  float RotationIncrement = 360.f / NumPoints;
  FVector NextVert;
  for (uint i = 0; i < NumPoints; i++)
  {
    NextVert = FRotator(0, 0, i*RotationIncrement).RotateVector(FVector(GetRange(),0,FaceRadius));
    UE_LOG(LogTemp, Warning, TEXT("Next Vert %f - %s"), i*RotationIncrement, *NextVert.ToString());
    FaceVerts.Add(NextVert);
  }
  return FaceVerts;
}
