// Fill out your copyright notice in the Description page of Project Settings.


#include "ConeTargetingComponent.h"

UConeTargetingComponent::UConeTargetingComponent()
{
  ConeHeight = 2000;
  ConeAngle = 3.1415.0f/16.0f;
}

bool UConeTargetingComponent::IsTargetable(AActor* OtherActor)
{
  return false;
}


