// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Parts/BodyPart.h"
#include "CorePart.generated.h"

/**
 * 
 */
UCLASS()
class SCRAPYARD_API UCorePart : public UBodyPart
{
  GENERATED_BODY()

public:
  
  static UCorePart* NewCore(uint32 NewPartID, FText NewPartName, UManufacturer* NewManufacturer, URarity* NewRarity, uint32 NewMass, uint32 NewHitPoints, uint32 NewPowerDrain, uint32 NewArmor, uint32 NewEMShield, TSubclassOf<AScrapyardAbility> NewAbilityClass, TSoftObjectPtr<USkeletalMesh> NewSkeletalMesh, TSoftObjectPtr<UMaterial> NewMajorMaterial, uint32 NewMaxWeight, uint32 NewPowerSupply);

  UCorePart();

  UPROPERTY()
  uint32 MaxWeight;
  UPROPERTY()
  uint32 PowerSupply;

  void Assign(UPartAssignment* PartAssignment) override;

  virtual bool IsAssignedTo(UPartAssignment* PartAssignment) override;

  UTexture2D* GetPartTypeIcon() const override;

  virtual TArray<FStatText> GetStatsText() const override;
};
