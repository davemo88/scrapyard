// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/SkeletalMesh.h"
#include "Abilities/ScrapyardAbility.h"
#include "Parts/RobotPartAssets.h"
#include "Parts/RobotPartAssignment.h"
#include "RobotPart.generated.h"

class UManufacturer;
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

  static URobotPart* GetPart(uint32 PartID);

  UPROPERTY()
  uint32 PartID;
  UPROPERTY(BlueprintReadOnly)
  FText PartName;
  UPROPERTY(BlueprintReadOnly)
  UManufacturer* Manufacturer;
  UPROPERTY(BlueprintReadOnly)
  URarity* Rarity;
  UPROPERTY(BlueprintReadOnly)
  int32 Mass;
  UPROPERTY(BlueprintReadOnly)
  int32 PowerDrain;
  UPROPERTY(BlueprintReadOnly)
  int32 HitPoints;
  UPROPERTY(BlueprintReadOnly)
  int32 KineticDefense;
  UPROPERTY(BlueprintReadOnly)
  int32 ElectricDefense;
  UPROPERTY(BlueprintReadOnly)
  TSubclassOf<AScrapyardAbility> AbilityClass;

  UFUNCTION()
  USkeletalMesh* GetSkeletalMesh();
  UFUNCTION()
  UMaterial* GetMajorMaterial();

  virtual TSoftObjectPtr<UTexture2D> GetPartTypeIcon() { return nullptr; } const;

  virtual TArray<FStatText> GetStatsText() const;

  virtual void Draft(USoloDraft* SoloDraft) {} const;

  virtual void Assign(URobotPartAssignment* RobotPartAssignment) {} const;

protected:

  TArray<uint32, URobotPart*> InitPartDB;

  UPROPERTY()
  TSoftObjectPtr<USkeletalMesh> SkeletalMesh;
  UPROPERTY()
  TSoftObjectPtr<UMaterial> MajorMaterial;


};
