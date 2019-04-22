// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Parts/RobotPart.h"
#include "ArmsPart.generated.h"

class URobotPartAssignment;
/**
 * 
 */
UCLASS()
class SCRAPYARD_API UArmsPart : public URobotPart
{
  GENERATED_BODY()

public:

  static UArmsParts* NewArms(uint32 NewPartID, FText NewPartName, UManufacturer* NewManufacturer, URarity* NewRarity, uint32 NewMass, uint32 NewEnergyDrain, TSubclassOf<AScrapyardAbility> NewAbilityClass, TSoftObjectPtr<USkeletalMesh> NewSkeletalMesh, TSoftObjectPtr<UMaterial> NewMajorMaterial);

  UPROPERTY()
  int32 MaxWeight;
  UPROPERTY()
  int32 RecoilControl;
  UPROPERTY() 
  int32 WeaponDexterity;

  void Draft(USoloDraft* SoloDraft) const override;

  void Assign(URobotPartAssignment* PartAssignment) const override;

  TSoftObjectPtr<UTexture2D> GetPartTypeIcon() const override;

  virtual TArray<FStatText> GetStatsText() const override;

};
