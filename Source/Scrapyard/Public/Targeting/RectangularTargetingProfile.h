// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Targeting/TargetingProfile.h"
#include "RectangularTargetingProfile.generated.h"

/**
 * 
 */
UCLASS()
class SCRAPYARD_API URectangularTargetingProfile : public UTargetingProfile
{
  GENERATED_BODY()

public:

  URectangularTargetingProfile();

protected:

  float VerticalAngle;
  float HorizontalAngle;

  virtual bool IsTargeted(FVector OtherRelativeLocation);

  virtual TArray<FVector> InitFaceVerts();
	
};
