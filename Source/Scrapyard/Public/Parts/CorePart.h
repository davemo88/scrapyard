// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Parts/RobotPart.h"
#include "CorePart.generated.h"

/**
 * 
 */
UCLASS()
class SCRAPYARD_API UCorePart : public URobotPart
{
  GENERATED_BODY()

public:
  
  static UCorePart* NewCore(uint32 NewPartID, FText NewPartName, UManufacturer* NewManufacturer, URarity* NewRarity, uint32 NewMass, uint32 NewHitPoints, uint32 NewPowerDrain, uint32 NewKineticDefense, uint32 NewElectricDefense, TSubclassOf<AScrapyardAbility> NewAbilityClass, TSoftObjectPtr<USkeletalMesh> NewSkeletalMesh, TSoftObjectPtr<UMaterial> NewMajorMaterial, uint32 NewMaxWeight, uint32 NewPowerSupply, uint32 NewBoosterThrust, uint32 NewBoosterPowerDrain);

  UPROPERTY()
  uint32 MaxWeight;
  UPROPERTY()
  uint32 PowerSupply;
  UPROPERTY()
  uint32 BoosterThrust;
  UPROPERTY()
  uint32 BoosterPowerDrain;

  void Assign(UPartAssignment* PartAssignment) override;

  UTexture2D* GetPartTypeIcon() const override;

  virtual TArray<FStatText> GetStatsText() const override;
};
