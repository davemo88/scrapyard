// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Parts/RobotPart.h"
#include "BoosterPart.generated.h"

/**
 * 
 */
UCLASS()
class SCRAPYARD_API UBoosterPart : public URobotPart
{
  GENERATED_BODY()

public:
  
  static UBoosterPart* NewBooster(uint32 NewPartID, FText NewPartName, UManufacturer* NewManufacturer, URarity* NewRarity, uint32 NewMass, uint32 NewPowerDrain, uint32 NewThrust, uint32 NewThrustPowerConsumption, TSubclassOf<AScrapyardAbility> NewAbilityClass, TSoftObjectPtr<USkeletalMesh> NewSkeletalMesh, TSoftObjectPtr<UMaterial> NewMajorMaterial);

  UBoosterPart();

  UPROPERTY()
  uint32 Thrust;
  UPROPERTY()
  uint32 ThrustPowerConsumption;

  void Assign(UPartAssignment* PartAssignment) override;

  virtual bool IsAssignedTo(UPartAssignment* PartAssignment) override;

  virtual void Draft(UDraftBase* CurrentDraft) override;

  UTexture2D* GetPartTypeIcon() const override;

  TArray<FStatText> GetStatsText() const override;

};
