// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Parts/BodyPart.h"
#include "ArmsPart.generated.h"

class UPartAssignment;
/**
 * 
 */
UCLASS()
class SCRAPYARD_API UArmsPart : public UBodyPart
{
  GENERATED_BODY()

public:

  static UArmsPart* NewArms(uint32 NewPartID, FText NewPartName, UManufacturer* NewManufacturer, URarity* NewRarity, uint32 NewMass, uint32 NewHitPoints, uint32 NewPowerDrain, uint32 NewKineticDefense, uint32 NewElectricDefense, TSubclassOf<AScrapyardAbility> NewAbilityClass, TSoftObjectPtr<USkeletalMesh> NewSkeletalMesh, TSoftObjectPtr<UMaterial> NewMajorMaterial);

  UArmsPart();

  UPROPERTY()
  uint32 MaxWeight;
  UPROPERTY()
  uint32 RecoilControl;
  UPROPERTY() 
  uint32 WeaponDexterity;

  void Assign(UPartAssignment* PartAssignment) override;

  virtual bool IsAssignedTo(UPartAssignment* PartAssignment) override;

  virtual void Draft(UDraftBase* CurrentDraft) override;

  UTexture2D* GetPartTypeIcon() const override;

  TArray<FStatText> GetStatsText() const override;

};
