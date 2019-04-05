// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Targeting/TargetingProfile.h"
#include "ConeTargetingProfile.generated.h"

/**
 * 
 */
UCLASS()
class SCRAPYARD_API UConeTargetingProfile : public UTargetingProfile
{
  GENERATED_BODY()

public:

  UConeTargetingProfile();

  UPROPERTY(EditAnywhere)
  float ConeAngle; 

protected:

  virtual bool IsTargeted(FVector OtherRelativeLocation) override;

  virtual TArray<FVector> InitFaceVerts() override;

  virtual float GetConeRadius(float Distance);
	
};
