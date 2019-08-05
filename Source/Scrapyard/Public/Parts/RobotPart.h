// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/SkeletalMesh.h"
#include "Parts/PartAssets.h"
#include "Parts/PartAssignment.h"
#include "Parts/Manufacturer.h"
#include "Abilities/ScrapyardAbility.h"
#include "RobotPart.generated.h"

class URarity;
class USoloDraft;
class UPartAssignment;
class UPartAssets;
class UTexture2D;
class UMaterial;

USTRUCT()
struct FStatText {
  GENERATED_BODY()

  FText StatName;
  FText StatValue;

  FStatText(FText InStatName = FText(), FText InStatValue = FText()) : StatName(InStatName), StatValue(InStatValue) {};
};

/**
 * 
 */
UCLASS()
class SCRAPYARD_API URobotPart : public UObject
{
  GENERATED_BODY()

public:

  UPROPERTY()
  uint32 PartID;
  UPROPERTY()
  FText PartName;
  UPROPERTY()
  UManufacturer* Manufacturer;
  UPROPERTY()
  URarity* Rarity;
  UPROPERTY()
  uint32 Mass;
  UPROPERTY()
  uint32 PowerDrain;
  UPROPERTY()
  uint32 HitPoints;
  UPROPERTY()
  uint32 KineticDefense;
  UPROPERTY()
  uint32 ElectricDefense;
  UPROPERTY()
  TSubclassOf<AScrapyardAbility> AbilityClass;
  UPROPERTY()
  TSoftObjectPtr<USkeletalMesh> SkeletalMesh;
  UPROPERTY()
  TSoftObjectPtr<UMaterial> MajorMaterial;

  virtual UTexture2D* GetPartTypeIcon() const { return nullptr; };

  virtual TArray<FStatText> GetStatsText() const;

  virtual void Assign(UPartAssignment* PartAssignment) {};

  virtual bool IsAssignedTo(UPartAssignment* PartAssignment) { return false; };

  bool IsDefaultPart();

};

