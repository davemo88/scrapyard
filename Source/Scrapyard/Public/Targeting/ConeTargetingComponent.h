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
  
protected:

  uint32 ConeHeight;

  float ConeAngle;

  virtual bool IsTargetable(AActor* OtherActor) override;
  
};
