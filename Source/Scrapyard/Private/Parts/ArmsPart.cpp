// Fill out your copyright notice in the Description page of Project Settings.

#include "ArmsPart.h"
#include "RobotPartAssignment.h"
#include "Parts/RobotPartAssets.h"
#include "SoloDraft.h"

void UArmsPart::Draft(USoloDraft* SoloDraft)
{
//  SoloDraft->DraftedArms.AddUnique(this);
//  UE_LOG(LogTemp, Warning, TEXT("Drafted %s"), *PartName);
  SoloDraft->DraftedArms.AddUnique(this);
}

void UArmsPart::Assign(URobotPartAssignment* PartAssignment)
{
  UE_LOG(LogTemp, Warning, TEXT("%s::Assign"), *GetName());
  PartAssignment->SetArms(this);
}

TSoftObjectPtr<UTexture2D> UArmsPart::GetCardIconAssetPtr()
{
  return (RobotPartAssetsBP != NULL) ? RobotPartAssetsBP->ArmsCardIcon: nullptr;
}

TArray<FStatText> UArmsPart::GetStatsText() const
{
  TArray<FStatText> StatsText = Super::GetStatsText();
  StatsText.Add(FStatText(NSLOCTEXT("SY", "WeaponDexterityStatText","Weapon Dexterity"),FText::AsNumber(WeaponDexterity)));
  return StatsText;
}

UArmsPart* UArmsPart::NewArms(uint32 NewPartID, FText NewPartName, UManufacturer* NewManufacturer, URarity* NewRarity, uint32 NewMass, uint32 NewEnergyDrain, TSubclassOf<AScrapyardAbility> NewAbilityClass, TSoftObjectPtr<USkeletalMesh> NewSkeletalMesh, TSoftObjectPtr<UMaterial> NewMajorMaterial, uint32 NewTargetingAbility, uint32 NewChipSlots)
{
  UArmsPart* NewPart = NewObject<UArmsPart>();
  NewPart->PartID = NewPartID;
  NewPart->PartName = NewPartName; 
  NewPart->Manufacturer = NewManufacturer;
  NewPart->Rarity = NewRarity;
  NewPart->Mass = NewMass;
  NewPart->EnergyDrain = NewEnergyDrain;
  NewPart->AbilityClass = NewAbilityClass;
  NewPart->SkeletalMesh = NewSkeletalMesh;
  NewPart->MajorMaterial = NewMajorMaterial;

  return NewPart;
}
