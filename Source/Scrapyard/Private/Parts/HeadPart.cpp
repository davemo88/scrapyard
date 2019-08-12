// Fill out your copyright notice in the Description page of Project Settings.

#include "HeadPart.h"
#include "Game/ScrapyardGameInstance.h"
#include "Game/ScrapyardAssets.h"
#include "Parts/PartAssignment.h"
#include "SoloDraft.h"

UHeadPart* UHeadPart::NewHead(uint32 NewPartID, FText NewPartName, UManufacturer* NewManufacturer, URarity* NewRarity, uint32 NewMass, uint32 NewHitPoints, uint32 NewPowerDrain, uint32 NewKineticDefense, uint32 NewElectricDefense, TSubclassOf<AScrapyardAbility> NewAbilityClass, TSoftObjectPtr<USkeletalMesh> NewSkeletalMesh, TSoftObjectPtr<UMaterial> NewMajorMaterial, uint32 NewTargetingAbility, uint32 NewChipSlots)
{
  UHeadPart* NewPart = NewObject<UHeadPart>();
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
  NewPart->TargetingAbility = NewTargetingAbility;
  NewPart->ChipSlots = NewChipSlots;

  return NewPart;
}

UHeadPart::UHeadPart()
{
  PartType = ERobotPartType::Head;
}

void UHeadPart::Assign(UPartAssignment* PartAssignment)
{
  PartAssignment->SetHead(this);
}

bool UHeadPart::IsAssignedTo(UPartAssignment* PartAssignment)
{
  return PartAssignment->GetHead() == this;
}

void UHeadPart::Draft(UDraftBase* CurrentDraft)
{
  CurrentDraft->DraftedHeads.Add(this);
}

UTexture2D* UHeadPart::GetPartTypeIcon() const
{
  return (UScrapyardGameInstance::AssetsBP != NULL) ? 
    UScrapyardGameInstance::AssetsBP->GetAsset<UTexture2D>(UScrapyardGameInstance::AssetsBP->PartAssetsBP->HeadCardIcon) 
    : nullptr;
}

TArray<FStatText> UHeadPart::GetStatsText() const
{
  TArray<FStatText> StatsText = Super::GetStatsText();
  StatsText.Add(FStatText(NSLOCTEXT("SY", "TargetingAbilityStatText","Targeting Ability"),FText::AsNumber(TargetingAbility)));
  StatsText.Add(FStatText(NSLOCTEXT("SY", "ChipSlots","Chip Slots"),FText::AsNumber(ChipSlots)));
  return StatsText;
}
