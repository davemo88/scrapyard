// Fill out your copyright notice in the Description page of Project Settings.

#include "ArmsPart.h"
#include "Game/ScrapyardGameInstance.h"
#include "Game/ScrapyardAssets.h"
#include "PartAssignment.h"
#include "Parts/PartAssets.h"
#include "SoloDraft.h"

UArmsPart* UArmsPart::NewArms(uint32 NewPartID, FText NewPartName, UManufacturer* NewManufacturer, URarity* NewRarity, uint32 NewMass, uint32 NewHitPoints, uint32 NewPowerDrain, uint32 NewKineticDefense, uint32 NewElectricDefense, TSubclassOf<AScrapyardAbility> NewAbilityClass, TSoftObjectPtr<USkeletalMesh> NewSkeletalMesh, TSoftObjectPtr<UMaterial> NewMajorMaterial)
{
  UArmsPart* NewPart = NewObject<UArmsPart>();
  NewPart->PartID = NewPartID;
  NewPart->PartName = NewPartName; 
  NewPart->Manufacturer = NewManufacturer;
  NewPart->Rarity = NewRarity;
  NewPart->Mass = NewMass;
  NewPart->HitPoints = NewHitPoints;
  NewPart->PowerDrain = NewPowerDrain;
  NewPart->KineticDefense = NewKineticDefense;
  NewPart->ElectricDefense = NewElectricDefense;
  NewPart->AbilityClass = NewAbilityClass;
  NewPart->SkeletalMesh = NewSkeletalMesh;
  NewPart->MajorMaterial = NewMajorMaterial;

  return NewPart;
}

void UArmsPart::Assign(UPartAssignment* PartAssignment)
{
  PartAssignment->SetArms(this);
}

bool UArmsPart::IsAssignedTo(UPartAssignment* PartAssignment)
{
  return PartAssignment->GetArms() == this;
}

UTexture2D* UArmsPart::GetPartTypeIcon() const
{
  return (UScrapyardGameInstance::AssetsBP != NULL) ? 
    UScrapyardGameInstance::AssetsBP->GetAsset<UTexture2D>(UScrapyardGameInstance::AssetsBP->PartAssetsBP->ArmsCardIcon) 
    : nullptr;
}

TArray<FStatText> UArmsPart::GetStatsText() const
{
  TArray<FStatText> StatsText = Super::GetStatsText();
  StatsText.Add(FStatText(NSLOCTEXT("SY", "WeaponDexterityStatText","Weapon Dexterity"),FText::AsNumber(WeaponDexterity)));
  return StatsText;
}

