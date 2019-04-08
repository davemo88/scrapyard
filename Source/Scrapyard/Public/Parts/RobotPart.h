// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/SkeletalMesh.h"
#include "Abilities/ScrapyardAbility.h"
#include "RobotPart.generated.h"

class UManufacturer;
class URarity;
class USoloDraft;
class URobotPartAssignment;
class URobotPartAssets;
//class AScrapyardAbility;
class UTexture2D;
class UMaterial;

// DECLARE_DYNAMIC_MULTICAST_DELEGATE(FSkeletalMeshLoadedDelegate);
// DECLARE_DYNAMIC_MULTICAST_DELEGATE(FMajorMaterialLoadedDelegate);
// DECLARE_DYNAMIC_MULTICAST_DELEGATE(FManufacturerlLoadedDelegate);
// DECLARE_DYNAMIC_MULTICAST_DELEGATE(FCardIconLoadedDelegate);

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

  static const uint32 PartID;

  virtual uint32 GetPartID()
  {
    return PartID;
  };

  static URobotPartAssets* RobotPartAssetsBP;

//  static TMap<FString, UManufacturer*> Manufacturers;

  static UManufacturer* GetManufacturer(FString ManufacturerNick);

  static TMap<FString, UManufacturer*> InitManufacturers();

  URobotPart();

  virtual void PostInitProperties() override;
  
  UPROPERTY(BlueprintReadOnly)
  FText PartName;
  UPROPERTY(BlueprintReadOnly)
  UManufacturer* Manufacturer;
  UPROPERTY(BlueprintReadOnly)
  URarity* Rarity;
  UPROPERTY(BlueprintReadOnly)
  UTexture2D* CardIcon;

// this integer type because only uint8 and int32 are supported by blueprints
  UPROPERTY(BlueprintReadOnly)
  int32 Mass;
// TODO: cores don't have power drain :(
  UPROPERTY(BlueprintReadOnly)
  int32 PowerDrain;
  UPROPERTY(BlueprintReadOnly)
  int32 HitPoints;
//  UPROPERTY(BlueprintReadOnly)
//  int32 Durability;
  UPROPERTY(BlueprintReadOnly)
  int32 PhysicalDefense;
  UPROPERTY(BlueprintReadOnly)
  int32 EnergyDefense;

  UPROPERTY(BlueprintReadOnly)
  TSubclassOf<AScrapyardAbility> AbilityClass;

// skeletal mesh 
// maybe this should be a TAssetPtr, but I think just the thing on the asset blueprint needs to be a TAssetPtr ? ? 
  UPROPERTY(BlueprintReadOnly)
  USkeletalMesh* SkeletalMesh;

  UPROPERTY(BlueprintReadOnly)
  UMaterial* MajorMaterial;
  UPROPERTY(BlueprintReadOnly)
  UMaterial* MinorMaterial;
  UPROPERTY(BlueprintReadOnly)
  UMaterial* AccentMaterial;

  void SetSkeletalMesh();

  USkeletalMesh* GetSkeletalMesh();

  void OnSkeletalMeshLoaded();

  UMaterial* GetMajorMaterial();

  void OnMajorMaterialLoaded();

  virtual void Draft(USoloDraft* SoloDraft) {};

  virtual void Assign(URobotPartAssignment* RobotPartAssignment) {};

  UTexture2D* GetCardIcon();

  void OnCardIconLoaded();

  virtual TArray<FStatText> GetStatsText();

//  FSkeletalMeshLoadedDelegate SkeletalMeshLoadedDelegate;
//  FMajorMaterialLoadedDelegate MajorMaterialLoadedDelegate;
//  FManufacturerLoadedDelegate ManufacturerLoadedDelegate;
//  FCardIconLoadedDelegate CardIconLoadedDelegate;

protected: 

  virtual TSoftObjectPtr<USkeletalMesh> GetSkeletalMeshAssetPtr() { return nullptr; };

  virtual TSoftObjectPtr<UMaterial> GetMajorMaterialAssetPtr() { return nullptr; };

  virtual TSoftObjectPtr<UTexture2D> GetCardIconAssetPtr() { return nullptr; };

};
