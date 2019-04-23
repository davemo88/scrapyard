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
struct FManufacturers
{
  GENERATED_BODY()

  UPROPERTY()
  UManufacturer* DefaultManufacturer;
  UPROPERTY()
  UManufacturer* RedManufacturer;
  UPROPERTY()
  UManufacturer* BlueManufacturer;
  UPROPERTY()
  UManufacturer* GreenManufacturer;
  UPROPERTY()
  UManufacturer* OrangeManufacturer;
  UPROPERTY()
  UManufacturer* PurpleManufacturer;

//TODO: refactor to allow access to assets blueprints
  FManufacturers()
  {
    DefaultManufacturer = NewObject<UManufacturer>();
    DefaultManufacturer->ManufacturerName = NSLOCTEXT("SY", "DefaultCorpName", "Default Corp");
    DefaultManufacturer->CardBackgroundColor = FLinearColor(0.43f, 0.43f, 43.0f, 1.0f);

    RedManufacturer = NewObject<UManufacturer>();
    RedManufacturer->ManufacturerName = NSLOCTEXT("SY", "RedCorpName", "Red Corp");
    RedManufacturer->CardBackgroundColor = FLinearColor(385.0f, 0.0f, 0.0f, 1.0f);

    BlueManufacturer = NewObject<UManufacturer>();
    BlueManufacturer->ManufacturerName = NSLOCTEXT("SY", "BlueCorpName", "Blue Corp");
    BlueManufacturer->CardBackgroundColor = FLinearColor(0.0f, 0.0f, 500.0f, 1.0f);

    GreenManufacturer = NewObject<UManufacturer>();
    GreenManufacturer->ManufacturerName = NSLOCTEXT("SY", "GreenCorpName", "Green Corp");
    GreenManufacturer->CardBackgroundColor = FLinearColor(0.0f, 385.0f, 0.0f, 1.0f);
    
    OrangeManufacturer = NewObject<UManufacturer>();
    OrangeManufacturer->ManufacturerName = NSLOCTEXT("SY", "OrangeCorpName", "Orange Corp");
    OrangeManufacturer->CardBackgroundColor = FLinearColor(1.0f, 0.29f, 0.0f, 1.0f);

    PurpleManufacturer = NewObject<UManufacturer>();
    PurpleManufacturer->ManufacturerName = NSLOCTEXT("SY", "PurpleCorpName", "Purple Corp");
    PurpleManufacturer->CardBackgroundColor = FLinearColor(1.0f, 0.0f, 72.0f, 1.0f);
  };
};

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

USTRUCT()
struct FPartDatabase
{
  GENERATED_BODY()

  void AddPart(URobotPart* NewPart)
  {
    PartMap.Add(NewPart->PartID, NewPart);
  };

  template <class T>
  T* GetPart(uint32 PartID)
  {
    if (PartMap.Find(PartID))
    {
      return Cast<T>(PartMap[PartID]);
    };
    return nullptr;
  };

  URobotPart* GetPart(uint32 PartID)
  {
    return GetPart<URobotPart>(PartID);
  };

protected:

  UPROPERTY()
  TMap<uint32, URobotPart*> PartMap;

};
