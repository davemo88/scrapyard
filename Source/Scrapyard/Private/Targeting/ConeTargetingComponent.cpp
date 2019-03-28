// Fill out your copyright notice in the Description page of Project Settings.


#include "ConeTargetingComponent.h"

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
  FVector OtherRelativeLocation = OtherActor->GetActorLocation()-GetOwner()->GetActorLocation();

  if (OtherRelativeLocation.X > ConeLength || OtherRelativeLocation.X < 0)
  {
    return false;
  }

  float ConeRadius = FMath::Tan(ConeAngle) * OtherRelativeLocation.X;
  float OtherRadius = FVector::Dist(FVector(OtherRelativeLocation.X,0,0),OtherRelativeLocation); 

  return OtherRadius < ConeRadius;

}

float UConeTargetingComponent::GetRange()
{
  return ConeLength;
}

