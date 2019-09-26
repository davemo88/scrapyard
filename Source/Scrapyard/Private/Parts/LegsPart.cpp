// Fill out your copyright notice in the Description page of Project Settings.

#include "LegsPart.h"
#include "Game/ScrapyardGameInstance.h"
#include "Game/ScrapyardAssets.h"
#include "Parts/PartAssignment.h"
#include "SoloDraft.h"

ULegsPart* ULegsPart::NewLegs(uint32 NewPartID, FText NewPartName, UManufacturer* NewManufacturer, URarity* NewRarity, uint32 NewMass, uint32 NewHitPoints, uint32 NewPowerDrain, uint32 NewArmor, uint32 NewEMShield, TSubclassOf<AScrapyardAbility> NewAbilityClass, TSoftObjectPtr<USkeletalMesh> NewSkeletalMesh, TSoftObjectPtr<UMaterial> NewMajorMaterial, uint32 NewMaxWeight, uint32 NewMovementSpeed, uint32 NewStability, uint32 NewTurningSpeed)
{
  ULegsPart* NewPart = NewObject<ULegsPart>();
  NewPart->PartID = NewPartID;
  NewPart->PartName = NewPartName; 
  NewPart->Manufacturer = NewManufacturer;
  NewPart->Rarity = NewRarity;
  NewPart->Mass = NewMass;
  NewPart->HitPoints = NewHitPoints;
  NewPart->PowerDrain = NewPowerDrain;
  NewPart->Armor = NewArmor;
  NewPart->EMShield = NewEMShield;
  NewPart->AbilityClass = NewAbilityClass;
  NewPart->SkeletalMesh = NewSkeletalMesh;
  NewPart->MajorMaterial = NewMajorMaterial;
  NewPart->MaxWeight = NewMaxWeight;
  NewPart->MovementSpeed = NewMovementSpeed;
  NewPart->Stability = NewStability;
  NewPart->TurningSpeed = NewTurningSpeed;

  return NewPart;

}

ULegsPart::ULegsPart()
{
  PartType = ERobotPartType::Legs;
}

void ULegsPart::Assign(UPartAssignment* PartAssignment)
{
  PartAssignment->SetLegs(this);
}

bool ULegsPart::IsAssignedTo(UPartAssignment* PartAssignment)
{
  return PartAssignment->GetLegs() == this;
}

UTexture2D* ULegsPart::GetPartTypeIcon() const
{
  return (UScrapyardGameInstance::AssetsBP != NULL) ? 
    UScrapyardGameInstance::AssetsBP->GetAsset<UTexture2D>(UScrapyardGameInstance::AssetsBP->PartAssetsBP->LegsCardIcon) 
    : nullptr;
}

TArray<FStatText> ULegsPart::GetStatsText() const
{
  TArray<FStatText> StatsText = Super::GetStatsText();
  StatsText.Add(FStatText(NSLOCTEXT("SY", "MovementSpeedStatText","Movement Speed"),FText::AsNumber(MovementSpeed)));
  return StatsText;
}
