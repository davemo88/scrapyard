// Fill out your copyright notice in the Description page of Project Settings.


#include "BoosterPart.h"
#include "Game/ScrapyardGameInstance.h"
#include "Game/ScrapyardAssets.h"
#include "Parts/PartAssets.h"

UBoosterPart* UBoosterPart::NewBooster(uint32 NewPartID, FText NewPartName, UManufacturer* NewManufacturer, URarity* NewRarity, uint32 NewMass, uint32 NewPowerDrain, uint32 NewThrust, uint32 NewThrustPowerConsumption, TSubclassOf<AScrapyardAbility> NewAbilityClass, TSoftObjectPtr<USkeletalMesh> NewSkeletalMesh, TSoftObjectPtr<UMaterial> NewMajorMaterial)
{
  UBoosterPart* NewPart = NewObject<UBoosterPart>();
  NewPart->PartID = NewPartID;
  NewPart->PartName = NewPartName; 
  NewPart->Manufacturer = NewManufacturer;
  NewPart->Rarity = NewRarity;
  NewPart->Mass = NewMass;
  NewPart->PowerDrain = NewPowerDrain;
  NewPart->Thrust = NewThrust;
  NewPart->ThrustPowerConsumption = NewThrustPowerConsumption;
  NewPart->AbilityClass = NewAbilityClass;
  NewPart->SkeletalMesh = NewSkeletalMesh;
  NewPart->MajorMaterial = NewMajorMaterial;

  return NewPart;
}

void UBoosterPart::Assign(UPartAssignment* PartAssignment)
{
  PartAssignment->SetBooster(this);
}

bool UBoosterPart::IsAssignedTo(UPartAssignment* PartAssignment)
{
  return PartAssignment->GetBooster() == this;
}

UTexture2D* UBoosterPart::GetPartTypeIcon() const
{
  return (UScrapyardGameInstance::AssetsBP != NULL) ? 
    UScrapyardGameInstance::AssetsBP->GetAsset<UTexture2D>(UScrapyardGameInstance::AssetsBP->PartAssetsBP->BoosterCardIcon) 
    : nullptr;
}

TArray<FStatText> UBoosterPart::GetStatsText() const
{
  TArray<FStatText> StatsText = Super::GetStatsText();
  StatsText.Add(FStatText(NSLOCTEXT("SY", "ThrustStatText","Thrust"),FText::AsNumber(Thrust)));
  StatsText.Add(FStatText(NSLOCTEXT("SY", "ThrustPowerDrainStatText","Thrust Power Consumption"),FText::AsNumber(ThrustPowerConsumption)));
  return StatsText;
}

