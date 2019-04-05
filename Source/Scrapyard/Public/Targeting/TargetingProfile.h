// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "TargetingProfile.generated.h"

/**
 * 
 */
UCLASS()
class SCRAPYARD_API UTargetingProfile : public UObject
{
  GENERATED_BODY()

  friend class URobotTargetingComponent;
  
protected:

  float Range;

//TODO: set somewhere authoritatively
  FVector TargetingOffset;

//  TSubclassOf<UTargetingWidget> TargetingWidget;

  virtual bool IsTargeted(FVector OtherRelativeLocation) { return false; };

  virtual TArray<FVector> InitFaceVerts() { TArray<FVector> it; return it; };
  
};
