// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "TargetingProfile.generated.h"

class ARobotCharacter;

/**
 * 
 */
UCLASS()
class SCRAPYARD_API UTargetingProfile : public UObject
{
  GENERATED_BODY()

  friend class URobotTargetingComponent;

public:

protected:

//  TSubclassOf<UTargetingWidget> TargetingWidget;

  float Range;

  virtual bool IsTargeted(ARobotCharacter* Robot, AActor* Target); 

  virtual TArray<FVector> InitFaceVerts() { TArray<FVector> it; return it; };

  virtual FVector GetTargetingOffset(ARobotCharacter* Robot) const;

  virtual FVector GetTargetingLocation(ARobotCharacter* Robot) const;

  virtual FRotator GetTargetingRotation(ARobotCharacter* Robot) const;

  FVector GetTargetRelativeLocation(FVector TargetingLocation, FRotator TargetingRotation, FVector TargetLocation) const;

  FVector GetLocationRelativeToView(ARobotCharacter* Robot, AActor* Target) const;

  bool IsInRange(FVector TargetRelativeLocation, FVector TargetingOffset) const;
  bool IsInRange(ARobotCharacter* Robot, AActor* Target) const;

  FVector GetPredictedTargetLocation(AActor* Target, float DeltaTime);
  
};
