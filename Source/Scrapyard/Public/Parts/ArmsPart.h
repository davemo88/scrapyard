// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Parts/RobotPart.h"
#include "ArmsPart.generated.h"

class UPartAssignment;
/**
 * 
 */
UCLASS()
class SCRAPYARD_API UArmsPart : public URobotPart
{
  GENERATED_BODY()

public:

  static UArmsPart* NewArms(uint32 NewPartID, FText NewPartName, UManufacturer* NewManufacturer, URarity* NewRarity, uint32 NewMass, uint32 NewHitPoints, uint32 NewPowerDrain, TSubclassOf<AScrapyardAbility> NewAbilityClass, TSoftObjectPtr<USkeletalMesh> NewSkeletalMesh, TSoftObjectPtr<UMaterial> NewMajorMaterial);

  UPROPERTY()
  uint32 MaxWeight;
  UPROPERTY()
  uint32 RecoilControl;
  UPROPERTY() 
  uint32 WeaponDexterity;

  void Draft(USoloDraft* SoloDraft) override;

  void Assign(UPartAssignment* PartAssignment) override;

  UTexture2D* GetPartTypeIcon() const override;

  TArray<FStatText> GetStatsText() const override;

};
