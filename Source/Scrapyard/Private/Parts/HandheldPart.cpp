// Fill out your copyright notice in the Description page of Project Settings.

#include "HandheldPart.h"
#include "Game/ScrapyardGameInstance.h"
#include "Game/ScrapyardAssets.h"
#include "Abilities/ScrapyardAbility.h"
#include "Abilities/HitscanAbility.h"
#include "SoloDraft.h"

UHandheldPart* UHandheldPart::NewHandheld(uint32 NewPartID, FText NewPartName, UManufacturer* NewManufacturer, URarity* NewRarity, uint32 NewMass, uint32 NewPowerDrain, uint32 NewAttack, float NewCooldown, TSubclassOf<AScrapyardAbility> NewAbilityClass, TSoftObjectPtr<USkeletalMesh> NewSkeletalMesh, TSoftObjectPtr<UMaterial> NewMajorMaterial)
{
  UHandheldPart* NewPart = NewObject<UHandheldPart>();
  NewPart->PartID = NewPartID;
  NewPart->PartName = NewPartName; 
  NewPart->Manufacturer = NewManufacturer;
  NewPart->Rarity = NewRarity;
  NewPart->Mass = NewMass;
  NewPart->PowerDrain = NewPowerDrain;
  NewPart->Attack = NewAttack;
  NewPart->Cooldown = NewCooldown;
  NewPart->AbilityClass = NewAbilityClass;
  NewPart->SkeletalMesh = NewSkeletalMesh;
  NewPart->MajorMaterial = NewMajorMaterial;

  return NewPart;
}

void UHandheldPart::Draft(USoloDraft* SoloDraft)
{
  SoloDraft->DraftedHandhelds.AddUnique(this);
}

//TODO: handle right vs left
void UHandheldPart::Assign(UPartAssignment* PartAssignment)
{
  PartAssignment->SetRightHandheld(this);
}

UTexture2D* UHandheldPart::GetPartTypeIcon() const
{
  return (UScrapyardGameInstance::AssetsBP != NULL) ? 
    UScrapyardGameInstance::AssetsBP->GetAsset<UTexture2D>(UScrapyardGameInstance::AssetsBP->PartAssetsBP->HandheldCardIcon) 
    : nullptr;
}


