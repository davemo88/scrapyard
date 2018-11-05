// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Parts/RobotPart.h"
#include "HeadPart.generated.h"

/**
 * 
 */
UCLASS()
class SCRAPYARD_API UHeadPart : public URobotPart
{
  GENERATED_BODY()
  
public:

  UPROPERTY()
  int32 TargetingAbility;
  UPROPERTY()
  int32 ChipSlots;

  void Draft(USoloDraft* SoloDraft) override;

  void Assign(URobotPartAssignment* PartAssignment) override;

  TSoftObjectPtr<UTexture2D> GetCardIconAssetPtr();

  virtual TArray<FStatText> GetStatsText();
};
