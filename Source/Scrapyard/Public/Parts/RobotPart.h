// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/SkeletalMesh.h"
#include "Abilities/ScrapyardAbility.h"
#include "Parts/RobotPartAssets.h"
#include "Parts/RobotPartAssignment.h"
#include "Parts/Manufacturer.h"
#include "RobotPart.generated.h"

class URarity;
class USoloDraft;
class URobotPartAssignment;
class URobotPartAssets;
//class AScrapyardAbility;
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

  static URobotPartAssets* RobotPartAssetsBP;

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

  virtual void Draft(USoloDraft* SoloDraft) {};

  virtual void Assign(URobotPartAssignment* RobotPartAssignment) {};

};

