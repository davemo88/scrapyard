// Fill out your copyright notice in the Description page of Project Settings.


#include "ConeTargetingComponent.h"
#include "Robots/RobotCharacter.h"
#include "Player/RobotPlayerController.h"
#include "Math/UnrealMathVectorConstants.h"

UConeTargetingComponent::UConeTargetingComponent()
{
  ConeLength = 2000;
  ConeAngle = 3.1415f/16.0f;

//  FaceCenter = FVector(ConeLength,0,0);
//  FaceRadius = FMath::Tan(ConeAngle) * ConeLength;

  TargetingWidget = UTargetingWidget::StaticClass();
}

bool UConeTargetingComponent::IsTargeted(AActor* OtherActor)
{
//TODO: should be relative to camera
  ARobotCharacter* OwnerChar = Cast<ARobotCharacter>(GetOwner());
  FVector OwnerLocation = OwnerChar->GetActorLocation();
  FRotator ViewRotation = OwnerChar->GetViewRotation();
  FVector TargetingOffset = FVector(-350, 0, 130);
  FVector RotatedTargetingOffset = ViewRotation.RotateVector(TargetingOffset);
  FRotator InverseViewRotation = ViewRotation.GetInverse();
  FVector OtherRelativeLocation = InverseViewRotation.RotateVector(OtherActor->GetActorLocation()-(OwnerLocation + RotatedTargetingOffset));


  if (Cast<ARobotPlayerController>(OwnerChar->GetController()))
  {
    UE_LOG(LogTemp, Warning, TEXT("%s"), *OtherRelativeLocation.ToString());
//    UE_LOG(LogTemp, Warning, TEXT("%s: View Rotation - %s"), *OwnerChar->GetName(), *ViewRotation.ToString());
  }

//  if (OtherRelativeLocation.X > ConeLength || OtherRelativeLocation.X < 0)
  if (OtherRelativeLocation.X > ConeLength || OtherRelativeLocation.X < -TargetingOffset.X)
  {
//    UE_LOG(LogTemp, Warning, TEXT("Out of Range - X = %f"), OtherRelativeLocation.X);
    return false;
  }

  float ConeRadius = GetConeRadius(FMath::Abs(OtherRelativeLocation.X));
  float OtherRadius = FVector::Dist(FVector(OtherRelativeLocation.X,0,0), OtherRelativeLocation); 

  if (Cast<ARobotPlayerController>(OwnerChar->GetController()))
  {
    UE_LOG(LogTemp, Warning, TEXT("%s: X = %f, ConeRadius = %f, OtherRadius = %f"), *OwnerChar->GetName(), OtherRelativeLocation.X, ConeRadius, OtherRadius);
  }

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
//    UE_LOG(LogTemp, Warning, TEXT("Next Vert %f - %s"), i*RotationIncrement, *NextVert.ToString());
    FaceVerts.Add(NextVert);
  }
  return FaceVerts;
}
