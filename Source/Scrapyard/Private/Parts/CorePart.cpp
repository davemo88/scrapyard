// Fill out your copyright notice in the Description page of Project Settings.

#include "CorePart.h"
#include "Game/ScrapyardGameInstance.h"
#include "Game/ScrapyardAssets.h"
#include "Parts/PartAssignment.h"
#include "SoloDraft.h"

UCorePart* UCorePart::NewCore(uint32 NewPartID, FText NewPartName, UManufacturer* NewManufacturer, URarity* NewRarity, uint32 NewMass, uint32 NewHitPoints, uint32 NewPowerDrain, uint32 NewKineticDefense, uint32 NewElectricDefense, TSubclassOf<AScrapyardAbility> NewAbilityClass, TSoftObjectPtr<USkeletalMesh> NewSkeletalMesh, TSoftObjectPtr<UMaterial> NewMajorMaterial, uint32 NewMaxWeight, uint32 NewPowerSupply)
{
  UCorePart* NewPart = NewObject<UCorePart>();
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
  NewPart->MaxWeight = NewMaxWeight;
  NewPart->PowerSupply = NewPowerSupply;

  return NewPart;

}

UCorePart::UCorePart()
{
  PartType = ERobotPartType::Core;
}

void UCorePart::Assign(UPartAssignment* PartAssignment)
{
  PartAssignment->SetCore(this);
}

bool UCorePart::IsAssignedTo(UPartAssignment* PartAssignment)
{
  return PartAssignment->GetCore() == this;
}

void UCorePart::Draft(UDraftBase* CurrentDraft)
{
  CurrentDraft->DraftedCores.Add(this);
}

UTexture2D* UCorePart::GetPartTypeIcon() const
{
  return (UScrapyardGameInstance::AssetsBP != NULL) ? 
    UScrapyardGameInstance::AssetsBP->GetAsset<UTexture2D>(UScrapyardGameInstance::AssetsBP->PartAssetsBP->CoreCardIcon) 
    : nullptr;
}

TArray<FStatText> UCorePart::GetStatsText() const
{
  TArray<FStatText> StatsText = Super::GetStatsText();
  StatsText.Add(FStatText(NSLOCTEXT("SY", "PowerSupplyStatText","Power Supply"),FText::AsNumber(PowerSupply)));
  return StatsText;
}
