// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Parts/RobotPart.h"
#include "LegsPart.generated.h"

/**
 * 
 */
UCLASS()
class SCRAPYARD_API ULegsPart : public URobotPart
{
  GENERATED_BODY()

public:

  static ULegsPart* NewLegs(uint32 NewPartID, FText NewPartName, UManufacturer* NewManufacturer, URarity* NewRarity, uint32 NewMass, uint32 NewHitPoints, uint32 NewPowerDrain, TSubclassOf<AScrapyardAbility> NewAbilityClass, TSoftObjectPtr<USkeletalMesh> NewSkeletalMesh, TSoftObjectPtr<UMaterial> NewMajorMaterial, uint32 NewMaxWeight, uint32 NewMovementSpeed, uint32 NewStability);

  UPROPERTY()
  uint32 MaxWeight;
  UPROPERTY()
  uint32 MovementSpeed;
  UPROPERTY()
  uint32 Stability;

  void Draft(USoloDraft* SoloDraft) override;

  void Assign(UPartAssignment* PartAssignment) override;

  virtual TArray<FStatText> GetStatsText() const override;

  UTexture2D* GetPartTypeIcon() const override;
};
