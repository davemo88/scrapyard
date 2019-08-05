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

  static UHeadPart* NewHead(uint32 NewPartID, FText NewPartName, UManufacturer* NewManufacturer, URarity* NewRarity, uint32 NewMass, uint32 NewHitPoints, uint32 NewPowerDrain, uint32 NewKineticDefense, uint32 NewElectricDefense, TSubclassOf<AScrapyardAbility> NewAbilityClass, TSoftObjectPtr<USkeletalMesh> NewSkeletalMesh, TSoftObjectPtr<UMaterial> NewMajorMaterial, uint32 NewTargetingAbility, uint32 NewChipSlots);

  UPROPERTY()
  uint32 TargetingAbility;
  UPROPERTY()
  uint32 ChipSlots;

  void Assign(UPartAssignment* PartAssignment) override;

  virtual bool IsAssignedTo(UPartAssignment* PartAssignment) override;

  UTexture2D* GetPartTypeIcon() const override;

  virtual TArray<FStatText> GetStatsText() const override;
};
