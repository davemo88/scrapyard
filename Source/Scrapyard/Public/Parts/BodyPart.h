// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Parts/RobotPart.h"
#include "BodyPart.generated.h"

/**
 * 
 */
UCLASS()
class SCRAPYARD_API UBodyPart : public URobotPart
{
  GENERATED_BODY()

public:
  
  UPROPERTY()
  uint32 HitPoints;
//  UPROPERTY()
//  uint32 PowerDrain;
  UPROPERTY()
  uint32 Armor;
  UPROPERTY()
  uint32 EMShield;

  virtual TArray<FStatText> GetStatsText() const override;
};
