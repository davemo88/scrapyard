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
struct FRobotPartTest {
  GENERATED_BODY()

// all parts
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
  uint32 EnergyDrain;

  UPROPERTY()
  TSubclassOf<AScrapyardAbility> AbilityClass;

  UPROPERTY()
  TSoftObjectPtr<USkeletalMesh> SkeletalMesh;
  UPROPERTY()
  TSoftObjectPtr<UMaterial> MajorMaterial;

// head, core, arms, legs
  UPROPERTY()
  uint32 HitPoints;
  UPROPERTY()
  uint32 KineticDefense;
  UPROPERTY()
  uint32 ElectricDefense;

  FRobotPartTest();

  FRobotPartTest(uint32 NewPartID, FText NewPartName, UManufacturer* NewManufacturer, URarity* NewRarity, uint32 NewMass, uint32 NewEnergyDrain, TSubclassOf<AScrapyardAbility> NewAbilityClass, TSoftObjectPtr<USkeletalMesh> NewSkeletalMesh, TSoftObjectPtr<UMaterial> NewMajorMaterial)
  {
    PartID = NewPartID;
    PartName = NewPartName; 
    Manufacturer = NewManufacturer;
    Rarity = NewRarity;
    Mass = NewMass;
    EnergyDrain = NewEnergyDrain;
    AbilityClass = NewAbilityClass;
    SkeletalMesh = NewSkeletalMesh;
    MajorMaterial = NewMajorMaterial;
  }

  virtual void Draft(USoloDraft* SoloDraft) { };

  virtual void Assign(URobotPartAssignment* PartAssignment) { };

  virtual TSoftObjectPtr<UTexture2D> GetPartTypeIcon() { return nullptr; }

  virtual TArray<FStatText> GetStatsText() const
  {
    UE_LOG(LogTemp, Warning, TEXT("%s::GetStatsText"), *GetName());

    TArray<FStatText> StatsText;
    StatsText.Add(FStatText(NSLOCTEXT("SY", "MassStatText", "Mass"),FText::AsNumber(Mass)));
    StatsText.Add(FStatText(NSLOCTEXT("SY", "HitPointsStatText", "Hit Points"),FText::AsNumber(Mass)));
    StatsText.Add(FStatText(NSLOCTEXT("SY", "PowerDrainStatText", "Power Drain"),FText::AsNumber(PowerDrain)));
    StatsText.Add(FStatText(NSLOCTEXT("SY", "PhysicalDefenseStatText", "Physical Defense"),FText::AsNumber(PhysicalDefense)));
    StatsText.Add(FStatText(NSLOCTEXT("SY", "EnergyDefenseStatText", "Energy Defense"),FText::AsNumber(EnergyDefense)));

    return StatsText;
  }
 
};

USTRUCT()
struct FHeadPartTest : public FRobotPartTest {
  GENERATED_BODY();

// TODO: something more complex?
  UPROPERTY()
  uint32 TargetingAbility;
  UPROPERTY()
  uint32 ChipSlots;

  FHeadPartTest();

  FHeadPartTest(uint32 NewPartID, FText NewPartName, UManufacturer* NewManufacturer, URarity* NewRarity, uint32 NewMass, uint32 NewEnergyDrain, TSubclassOf<AScrapyardAbility> NewAbilityClass, TSoftObjectPtr<USkeletalMesh> NewSkeletalMesh, TSoftObjectPtr<UMaterial> NewMajorMaterial, uint32 NewTargetingAbility, uint32 NewChipSlots)
  {
    PartID = NewPartID;
    PartName = NewPartName; 
    Manufacturer = NewManufacturer;
    Rarity = NewRarity;
    Mass = NewMass;
    EnergyDrain = NewEnergyDrain;
    AbilityClass = NewAbilityClass;
    SkeletalMesh = NewSkeletalMesh;
    MajorMaterial = NewMajorMaterial;
    TargetingAbility = NewTargetingAbility;
    ChipSlots = NewChipSlots;
  }

  void Draft(USoloDraft* SoloDraft) override { SoloDraft->DraftedHeads.AddUnique(this); };

  void Assign(URobotPartAssignment* PartAssignment) override { PartAssignment->SetHead(this); };

};

USTRUCT()
struct FCorePartTest : public FRobotPartTest {
  GENERATED_BODY();

  UPROPERTY()
  uint32 MaxWeight;
  UPROPERTY()
  uint32 PowerGeneration;
  UPROPERTY()
  uint32 BoosterThrust;
  UPROPERTY()
  uint32 BoosterPowerDrain;

  FCorePartTest();

  FCorePartTest(uint32 NewPartID, FText NewPartName, UManufacturer* NewManufacturer, URarity* NewRarity, uint32 NewMass, uint32 NewEnergyDrain, TSubclassOf<AScrapyardAbility> NewAbilityClass, TSoftObjectPtr<USkeletalMesh> NewSkeletalMesh, TSoftObjectPtr<UMaterial> NewMajorMaterial, uint32 NewMaxWeight, uint32 NewPowerGeneration, uint32 NewBoosterThrust, uint32 NewBoosterPowerDrain)
  {
    PartID = NewPartID;
    PartName = NewPartName; 
    Manufacturer = NewManufacturer;
    Rarity = NewRarity;
    Mass = NewMass;
    EnergyDrain = NewEnergyDrain;
    AbilityClass = NewAbilityClass;
    SkeletalMesh = NewSkeletalMesh;
    MajorMaterial = NewMajorMaterial;
    MaxWeight = NewMaxWeight;
    PowerGeneration = NewPowerGeneration;
    BoosterThrust = NewBoosterThrust;
    BoosterPowerDrain = NewBoosterPowerDrain;
  }

//  void Draft(USoloDraft* SoloDraft) override { SoloDraft->DraftedCores.AddUnique(this); }; 
//
//  void Assign(URobotPartAssignment* PartAssignment) override { PartAssignment->SetCore(this); };
};

USTRUCT()
struct FArmsPartTest : public FRobotPartTest {
  GENERATED_BODY();

// TODO: something more complex?
  UPROPERTY()
  uint32 TargetingAbility;
  UPROPERTY()
  uint32 ChipSlots;

  FArmsPartTest();

  FArmsPartTest(uint32 NewPartID, FText NewPartName, UManufacturer* NewManufacturer, URarity* NewRarity, uint32 NewMass, uint32 NewEnergyDrain, TSubclassOf<AScrapyardAbility> NewAbilityClass, TSoftObjectPtr<USkeletalMesh> NewSkeletalMesh, TSoftObjectPtr<UMaterial> NewMajorMaterial, uint32 NewTargetingAbility, uint32 NewChipSlots)
  {
    PartID = NewPartID;
    PartName = NewPartName; 
    Manufacturer = NewManufacturer;
    Rarity = NewRarity;
    Mass = NewMass;
    EnergyDrain = NewEnergyDrain;
    AbilityClass = NewAbilityClass;
    SkeletalMesh = NewSkeletalMesh;
    MajorMaterial = NewMajorMaterial;
    TargetingAbility = NewTargetingAbility;
    ChipSlots = NewChipSlots;
  }

//  void Draft(USoloDraft* SoloDraft) override { SoloDraft->DraftedArmss.AddUnique(this); }; 
//
//  void Assign(URobotPartAssignment* PartAssignment) override { PartAssignment->SetArms(this); };

};

USTRUCT()
struct FLegsPartTest : public FRobotPartTest {
  GENERATED_BODY();

// TODO: something more complex?
  UPROPERTY()
  uint32 TargetingAbility;
  UPROPERTY()
  uint32 ChipSlots;

  FLegsPartTest();

  FLegsPartTest(uint32 NewPartID, FText NewPartName, UManufacturer* NewManufacturer, URarity* NewRarity, uint32 NewMass, uint32 NewEnergyDrain, TSubclassOf<AScrapyardAbility> NewAbilityClass, TSoftObjectPtr<USkeletalMesh> NewSkeletalMesh, TSoftObjectPtr<UMaterial> NewMajorMaterial, uint32 NewTargetingAbility, uint32 NewChipSlots)
  {
    PartID = NewPartID;
    PartName = NewPartName; 
    Manufacturer = NewManufacturer;
    Rarity = NewRarity;
    Mass = NewMass;
    EnergyDrain = NewEnergyDrain;
    AbilityClass = NewAbilityClass;
    SkeletalMesh = NewSkeletalMesh;
    MajorMaterial = NewMajorMaterial;
    TargetingAbility = NewTargetingAbility;
    ChipSlots = NewChipSlots;
  }

//  void Draft(USoloDraft* SoloDraft) override { SoloDraft->DraftedLegss.AddUnique(this); }; 
//
//  void Assign(URobotPartAssignment* PartAssignment) override { PartAssignment->SetLegs(this); };

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

  URobotPart();

  virtual void PostInitProperties() override;

  static const uint32 PartID;

  virtual uint32 GetPartID()
  {
    return PartID;
  };

  static URobotPartAssets* RobotPartAssetsBP;

//  static TMap<FString, UManufacturer*> Manufacturers;

  static UManufacturer* GetManufacturer(FString ManufacturerNick);

  static TMap<FString, UManufacturer*> InitManufacturers();
  
  UPROPERTY(BlueprintReadOnly)
  FText PartName;
  UPROPERTY(BlueprintReadOnly)
  UManufacturer* Manufacturer;
  UPROPERTY(BlueprintReadOnly)
  URarity* Rarity;
  UPROPERTY(BlueprintReadOnly)
  UTexture2D* CardIcon;

// this integer type because only
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

  virtual TArray<FStatText> GetStatsText() const;

//  FSkeletalMeshLoadedDelegate SkeletalMeshLoadedDelegate;
//  FMajorMaterialLoadedDelegate MajorMaterialLoadedDelegate;
//  FManufacturerLoadedDelegate ManufacturerLoadedDelegate;
//  FCardIconLoadedDelegate CardIconLoadedDelegate;

protected: 

  virtual TSoftObjectPtr<USkeletalMesh> GetSkeletalMeshAssetPtr() { return nullptr; };

  virtual TSoftObjectPtr<UMaterial> GetMajorMaterialAssetPtr() { return nullptr; };

  virtual TSoftObjectPtr<UTexture2D> GetCardIconAssetPtr() { return nullptr; };

};
