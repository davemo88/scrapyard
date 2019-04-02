// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Targeting/RobotTargetingComponent.h"
#include "ConeTargetingComponent.generated.h"

/**
 * 
 */
UCLASS()
class SCRAPYARD_API UConeTargetingComponent : public URobotTargetingComponent
{
  GENERATED_BODY()

public:

  UConeTargetingComponent();

  virtual float GetRange() override;
  
protected:

  uint32 ConeLength;

// radians
  float ConeAngle; 

  virtual bool IsTargeted(AActor* OtherActor) override;

  virtual TArray<FVector> InitFaceVerts() override;

  virtual float GetConeRadius(float Distance);
  
};
