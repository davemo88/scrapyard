// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Parts/BodyPart.h"
#include "LegsPart.generated.h"

/**
 * 
 */
UCLASS()
class SCRAPYARD_API ULegsPart : public UBodyPart
{
  GENERATED_BODY()

public:

  static ULegsPart* NewLegs(uint32 NewPartID, FText NewPartName, UManufacturer* NewManufacturer, URarity* NewRarity, uint32 NewMass, uint32 NewHitPoints, uint32 NewPowerDrain, uint32 NewArmor, uint32 NewEMShield, TSubclassOf<AScrapyardAbility> NewAbilityClass, TSoftObjectPtr<USkeletalMesh> NewSkeletalMesh, TSoftObjectPtr<UMaterial> NewMajorMaterial, uint32 NewMaxWeight, uint32 NewMovementSpeed, uint32 NewStability, uint32 NewTurningSpeed);

  ULegsPart();

  UPROPERTY()
  uint32 MaxWeight;
  UPROPERTY()
  uint32 MovementSpeed;
  UPROPERTY()
  uint32 Stability;
  UPROPERTY()
  uint32 TurningSpeed;

  void Assign(UPartAssignment* PartAssignment) override;

  virtual bool IsAssignedTo(UPartAssignment* PartAssignment) override;

  virtual TArray<FStatText> GetStatsText() const override;

  UTexture2D* GetPartTypeIcon() const override;
};
